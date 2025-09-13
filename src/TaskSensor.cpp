#include <Arduino.h>
#include <TaskSensor.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include "HX711.h"

Adafruit_ADS1115 ads1;     /* Use this for the 12-bit version */
Adafruit_ADS1115 ads2;     /* Use this for the 12-bit version */

#define pin_DIN1  36
#define pin_DIN2  39
#define pin_DIN3  34
#define pin_DIN4  14

const int LOADCELL1_DOUT_PIN = 19;
const int LOADCELL1_SCK_PIN = 18;
const int LOADCELL2_DOUT_PIN = 23;
const int LOADCELL2_SCK_PIN = 5;
bool is_ads1_init_ok=0;
bool is_ads2_init_ok=0;
bool is_hx7111_init_ok=0;
bool is_hx7112_init_ok=0;
bool is_rom_init_ok=0;
HX711 scale1;
HX711 scale2;
extern uint8_t Canphu;

extern bool ADS_Type;
int16_t adc1, adc2, adc3, adc4, adc5, adc6, adc7, adc8;
float volts1, volts2, volts3, volts4, volts5, volts6, volts7, volts8;
uint16_t addr=0;
long long timesensor=0;

void Task_Sensor_code( void * pvParameters )
{
  pinMode(pin_DIN1,INPUT);
  pinMode(pin_DIN2,INPUT);
  pinMode(pin_DIN3,INPUT);
  pinMode(pin_DIN4,INPUT_PULLUP);

  scale1.begin(LOADCELL1_DOUT_PIN, LOADCELL1_SCK_PIN);
  scale2.begin(LOADCELL2_DOUT_PIN, LOADCELL2_SCK_PIN);

  Wire.setPins(21,22);
  Wire.begin(21, 22, 400000);   // 400 kHz để tăng throughput
  Wire.setClock(400000);        // đảm bảo clock

  if (ads1.begin(0x48)) {
    ads1.setGain(GAIN_ONE);
    ads1.setDataRate(RATE_ADS1115_128SPS);  // 128SPS hoặc 250SPS
    is_ads1_init_ok = 1;
  } else {
    is_ads1_init_ok = 0;
  }

  // if (ads2.begin(0x49)) 
  // {
  //   ads2.setGain(GAIN_ONE);
  //   ads2.setDataRate(RATE_ADS1115_8SPS);
  //   is_ads2_init_ok=1;
  // }
  // else
  // {
  //   is_ads2_init_ok=0;
  // }

  for(;;)
  {
    ReadLoadcell1();
    ReadLoadcell2();
    ReadInput();
    ReadADS1();
    // ReadADS2();

    // In log mỗi ~3000 ms an toàn rollover
    if ((uint32_t)(millis() - (uint32_t)timesensor) > 3000U)
    {
      Serial.print("\t| Loadcell 1 Raw:\t");    Serial.println(Loadcell1_raw);
      Serial.print("\t| Loadcell 1 Value:\t");  Serial.println(Loadcell1_value);

      Serial.print("\t| Loadcell 2 Raw:\t");    Serial.println(Loadcell2_raw);
      Serial.print("\t| Loadcell 2 Value:\t");  Serial.println(Loadcell2_value);

      Serial.println("--------------------------------------------");
      Serial.print("Length_raw: ");  Serial.print(Length_raw);  Serial.println(" adc");
      Serial.print("Angle_raw: ");   Serial.print(Angle_raw);   Serial.println(" adc");
      Serial.print("P1_raw: ");      Serial.print(P1_raw);      Serial.println(" mV");
      Serial.print("P2_raw: ");      Serial.print(P2_raw);      Serial.println(" mV");
      Serial.print("Canphu: ");      Serial.println(Canphu);

      timesensor = millis();
    }

    vTaskDelay(pdMS_TO_TICKS(50)); // ~20Hz
  }
}

void ReadADS1()
{
  if (is_ads1_init_ok == 1)
  {
    // Dùng float cho kênh cần mV để tránh mất phần thập phân
    uint16_t tmp1 = ads1.readADC_SingleEnded(0);
    uint16_t tmp2 = ads1.readADC_SingleEnded(1);
    float    tmp3 = ads1.computeVolts(ads1.readADC_SingleEnded(2)) * 1000.0f; // mV
    float    tmp4 = ads1.computeVolts(ads1.readADC_SingleEnded(3)) * 1000.0f; // mV

    // Lọc SMA rất nhẹ (N=4) – không đổi tên biến đầu ra
    static uint32_t l_buf[4], a_buf[4];
    static float    p1_buf[4], p2_buf[4];
    static uint8_t  idx = 0;

    l_buf[idx]  = tmp1;
    a_buf[idx]  = tmp2;
    p1_buf[idx] = tmp3;
    p2_buf[idx] = tmp4;

    idx = (uint8_t)((idx + 1) & 0x03); // vòng 0..3

    uint32_t l_sum = 0, a_sum = 0;
    float    p1_sum = 0.0f, p2_sum = 0.0f;
    for (uint8_t i = 0; i < 4; i++) {
      l_sum  += l_buf[i];
      a_sum  += a_buf[i];
      p1_sum += p1_buf[i];
      p2_sum += p2_buf[i];
    }

    Length_raw = (uint16_t)(l_sum >> 2);            // chia 4
    Angle_raw  = (uint16_t)(a_sum >> 2);
    P1_raw     = (uint16_t)(p1_sum * 0.25f);        // mV -> uint16_t
    P2_raw     = (uint16_t)(p2_sum * 0.25f);
  }
  else
  {
    Length_raw = 0xFFFF;
    Angle_raw  = 0xFFFF;
    P1_raw     = 0xFFFF;
    P2_raw     = 0xFFFF;
  }
}

void ReadADS2()
{
  if (is_ads2_init_ok == 1)
  {
    float tmp1 = ads2.computeVolts(ads2.readADC_SingleEnded(0)) * 1000.0f; // mV
    float tmp2 = ads2.computeVolts(ads2.readADC_SingleEnded(1));           // Volt (chủ đích)
    float tmp3 = ads2.computeVolts(ads2.readADC_SingleEnded(2)) * 1000.0f; // mV
    float tmp4 = ads2.computeVolts(ads2.readADC_SingleEnded(3)) * 1000.0f; // mV

    // (Tùy chọn) lọc nhẹ giống trên
    static float p5_buf[4], u_buf[4], p3_buf[4], p4_buf[4];
    static uint8_t idx = 0;
    p5_buf[idx] = tmp1;
    u_buf[idx]  = tmp2;
    p3_buf[idx] = tmp3;
    p4_buf[idx] = tmp4;
    idx = (uint8_t)((idx + 1) & 0x03);

    float p5=0,u=0,p3=0,p4=0;
    for (uint8_t i=0;i<4;i++){ p5+=p5_buf[i]; u+=u_buf[i]; p3+=p3_buf[i]; p4+=p4_buf[i]; }
    p5*=0.25f; u*=0.25f; p3*=0.25f; p4*=0.25f;

    P5_raw    = (uint16_t)p5;   // mV
    uc_Voltage= u;              // V — giữ nguyên “thiết kế” của bạn
    P3_raw    = (uint16_t)p3;   // mV
    P4_raw    = (uint16_t)p4;   // mV
  }
  else
  {
    P3_raw = 0xFFFF;
    P4_raw = 0xFFFF;
    P5_raw = 0xFFFF;
    uc_Voltage = -1;
  }
}

void ReadInput()
{
  // Đọc thô
  bool d1 = !digitalRead(pin_DIN1);
  bool d2 = !digitalRead(pin_DIN2);
  bool d3 = !digitalRead(pin_DIN3);
  bool d4 = !digitalRead(pin_DIN4);

  // Debounce mềm (SMA 4 mẫu)
  static uint8_t b1=0, b2=0, b3=0, b4=0;
  b1 = ((b1 << 1) | (d1 ? 1 : 0)) & 0x0F;
  b2 = ((b2 << 1) | (d2 ? 1 : 0)) & 0x0F;
  b3 = ((b3 << 1) | (d3 ? 1 : 0)) & 0x0F;
  b4 = ((b4 << 1) | (d4 ? 1 : 0)) & 0x0F;

  DigitalInput_1 = (b1 == 0x0F);  // 4 mẫu liên tiếp = 1
  DigitalInput_2 = (b2 == 0x0F);
  DigitalInput_3 = (b3 == 0x0F);
  DigitalInput_4 = (b4 == 0x0F);
}
// Median của 3 số (nhẹ, chống spike rất hiệu quả)
static inline long median3(long a, long b, long c) {
  long m = a;
  if ((a <= b && b <= c) || (c <= b && b <= a)) m = b;
  else if ((b <= c && c <= a) || (a <= c && c <= b)) m = c;
  return m;
}


void ReadLoadcell1()
{
  const float alpha = 0.20f;   // hệ số lọc IIR (0.1–0.3)
  long r1, r2, r3;

  if (scale1.wait_ready_timeout(120)) {   // 10SPS → ~120ms, 80SPS thì giảm còn 25ms
    r1 = scale1.read();
    scale1.wait_ready_timeout(120);
    r2 = scale1.read();
    scale1.wait_ready_timeout(120);
    r3 = scale1.read();

    // Median của 3 mẫu
    long m = (r1 > r2) ? ((r2 > r3) ? r2 : (r1 > r3 ? r3 : r1))
                       : ((r1 > r3) ? r1 : (r2 > r3 ? r3 : r2));

    long raw_offset = 0x800000 + m;

    static float ema = 0; 
    static bool init = false;
    if (!init) { ema = raw_offset; init = true; }
    else { ema = alpha * raw_offset + (1 - alpha) * ema; }

    Loadcell1_raw = (long)ema;
    is_hx7111_init_ok = 1;
  }
  else {
    is_hx7111_init_ok = 0;
  }
}

void ReadLoadcell2()
{
  const float alpha = 0.20f;
  long r1, r2, r3;

  if (scale2.wait_ready_timeout(120)) {
    r1 = scale2.read();
    scale2.wait_ready_timeout(120);
    r2 = scale2.read();
    scale2.wait_ready_timeout(120);
    r3 = scale2.read();

    long m = (r1 > r2) ? ((r2 > r3) ? r2 : (r1 > r3 ? r3 : r1))
                       : ((r1 > r3) ? r1 : (r2 > r3 ? r3 : r2));

    long raw_offset = 0x800000 + m;

    static float ema = 0;
    static bool init = false;
    if (!init) { ema = raw_offset; init = true; }
    else { ema = alpha * raw_offset + (1 - alpha) * ema; }

    Loadcell2_raw = (long)ema;
    is_hx7112_init_ok = 1;
  }
  else {
    is_hx7112_init_ok = 0;
  }
}