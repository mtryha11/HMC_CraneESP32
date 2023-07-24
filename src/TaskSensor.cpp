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

  scale1.begin(LOADCELL1_DOUT_PIN, LOADCELL1_SCK_PIN);
  scale2.begin(LOADCELL2_DOUT_PIN, LOADCELL2_SCK_PIN);

  // if(ADS_Type==1)//Dung
  // {
    // Wire.setPins(21,22);
  // }
  // else
  // {
    Wire.setPins(21,22);
  // }
  
  Wire.setClock(100000);

  if (ads1.begin(0x48)) 
  {
    ads1.setGain(GAIN_ONE);
    ads1.setDataRate(RATE_ADS1115_8SPS);
    is_ads1_init_ok=1;
  }
  else
  {
    is_ads1_init_ok=0;
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
    //Loadcell1_raw=Loadcell2_raw;
    ReadInput();
    ReadADS1();
    // ReadADS2();

    if(millis()-timesensor>30000)
    {
      // Loadcell1_value_calib0=15.0;
      // Loadcell1_raw_calib0=9105576;
      // Loadcell1_value_calib1=22.5;
      // Loadcell1_raw_calib1=11558866;

      // Loadcell2_value_calib0=10.8;
      // Loadcell2_raw_calib0=8679065;
      // Loadcell2_value_calib1=24.95;
      // Loadcell2_raw_calib1=12094591;

      Serial.print("\t| Loadcell 1 Raw:\t");
      Serial.println(Loadcell1_raw);
      Serial.print("\t| Loadcell 1 Value:\t");
      Serial.println(Loadcell1_value);

      Serial.print("\t| Loadcell 2 Raw:\t");
      Serial.println(Loadcell2_raw);
      Serial.print("\t| Loadcell 2 Value:\t");
      Serial.println(Loadcell2_value);

      Serial.println("--------------------------------------------");
      // Serial.print("ADS_Type: ");  Serial.println(ADS_Type);
      Serial.print("Length_raw: ");  Serial.print(Length_raw);  Serial.println("adc");
      Serial.print("Angle_raw: ");   Serial.print(Angle_raw);   Serial.println("adc");
      Serial.print("P1_raw: ");      Serial.print(P1_raw);      Serial.println("mV");
      Serial.print("P2_raw: ");      Serial.print(P2_raw);      Serial.println("mV");
      // Serial.print("P3_raw: ");      Serial.print(P3_raw);      Serial.println("mV");
      // Serial.print("P4_raw: ");      Serial.print(P4_raw);      Serial.println("mV");
      // Serial.print("P5_raw: ");      Serial.print(P5_raw);      Serial.println("mV");
      // Serial.print("uc_Voltage: ");  Serial.print(uc_Voltage);  Serial.println("V");
      timesensor=millis();
    }
    
    // Serial.print("Mem 0: "); Serial.println(eeprom.read_1_byte(0));
    // Serial.print("Mem 1: "); Serial.println(eeprom.read_1_byte(1));
    // Serial.print("Mem 2: "); Serial.println(eeprom.read_1_byte(2));

    vTaskDelay(50);
  }
}

void ReadADS1()
{
  if(is_ads1_init_ok==1)
  {
    uint16_t tmp1,tmp2,tmp3,tmp4;
    tmp1 = ads1.readADC_SingleEnded(0);
    tmp2 = ads1.readADC_SingleEnded(1);
    tmp3 = ads1.computeVolts(ads1.readADC_SingleEnded(2)) * 1000;
    tmp4 = ads1.computeVolts(ads1.readADC_SingleEnded(3)) * 1000;
    // if(tmp1!=0) 
    Length_raw = tmp1;
    // if(tmp2!=0) 
    Angle_raw = tmp2;
    // if(tmp3!=0) 
    P1_raw = tmp3;
    // if(tmp4!=0) 
    P2_raw = tmp4;
  }
  else
  {
    Length_raw = 0xFFFF;
    Angle_raw = 0xFFFF;
    P1_raw = 0xFFFF;
    P2_raw = 0xFFFF;
  }
}

void ReadADS2()
{
  if(is_ads2_init_ok==1)
  {
    uint16_t tmp1,tmp2,tmp3,tmp4;
    tmp1 = ads2.computeVolts(ads2.readADC_SingleEnded(0)) * 1000;
    tmp2 = ads2.computeVolts(ads2.readADC_SingleEnded(1));
    tmp3 = ads2.computeVolts(ads2.readADC_SingleEnded(2)) * 1000;
    tmp4 = ads2.computeVolts(ads2.readADC_SingleEnded(3)) * 1000;
    // if(tmp1!=0) 
    P5_raw = tmp1;
    // if(tmp2!=0) 
    uc_Voltage = tmp2;
    // if(tmp3!=0) 
    P3_raw = tmp3;
    // if(tmp4!=0) 
    P4_raw = tmp4;
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
  DigitalInput_1=digitalRead(pin_DIN1);
  DigitalInput_2=digitalRead(pin_DIN2);
  DigitalInput_3=digitalRead(pin_DIN3);
}

void ReadLoadcell1()
{
  if (scale1.wait_ready_timeout(100)) 
  {
    is_hx7111_init_ok=1;
    Loadcell1_raw = 0x800000 + scale1.read();
  }
  else 
  {
    is_hx7111_init_ok=0;
  }
}

void ReadLoadcell2()
{
  if (scale2.wait_ready_timeout(100)) 
  {
    is_hx7112_init_ok=1;
    Loadcell2_raw = 0x800000 + scale2.read();
  }
  else 
  {
    is_hx7111_init_ok=0;
  }
}