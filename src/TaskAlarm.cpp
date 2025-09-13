#include <Arduino.h>
#include <TaskAlarm.h>
bool Mode_Test_Relay=0;

bool Stt_CabMax=0;
bool Stt_AngleHi=0;
bool Stt_AngleSet=0;
bool Stt_LengthHi=0;
bool Stt_LengthLow=0;
bool Stt_LoadHi=0;
bool Stt_LoadSet=0;

uint8_t Pin_CabMax=32;
uint8_t Pin_AngleHi=33;
uint8_t Pin_AngleSet=25;
uint8_t Pin_LengthHi=26;
uint8_t Pin_LengthLow=27;
uint8_t Pin_LoadHi=12;
uint8_t Pin_LoadSet=13;


void Relay_process(uint8_t Relaypin,bool Status)
{
  if(Status==1)
    {
      digitalWrite(Relaypin,HIGH);
    }
  else
    {
      digitalWrite(Relaypin,LOW);
    }
}

void RelayTestMode()
{
 //if(Mode_Test_Relay==1)
    {
    Relay_process(Pin_CabMax,Stt_CabMax);
    Relay_process(Pin_AngleHi,Stt_AngleHi);
    Relay_process(Pin_AngleSet,Stt_AngleSet);
    Relay_process(Pin_LengthHi,Stt_LengthHi);
    Relay_process(Pin_LengthLow,Stt_LengthLow);
    Relay_process(Pin_LoadHi,Stt_LoadHi);
    Relay_process(Pin_LoadSet,Stt_LoadSet);
    //Mode_Test_Relay=0;
    }
}


void Task_Alarm_code( void * pvParameters )
{
  // 1) Đặt trạng thái phần mềm về OFF ngay từ đầu
  Stt_CabMax   = 0;
  Stt_AngleHi  = 0;
  Stt_AngleSet = 0;
  Stt_LengthHi = 0;
  Stt_LengthLow= 0;
  Stt_LoadHi   = 0;
  Stt_LoadSet  = 0;

  // 2) Chuẩn bị mức LOW trước khi chuyển sang OUTPUT
  //    Với chân strap/nhạy (ví dụ GPIO12), kéo xuống tạm thời để tránh trôi
  pinMode(Pin_CabMax,   INPUT_PULLDOWN); digitalWrite(Pin_CabMax,   LOW); pinMode(Pin_CabMax,   OUTPUT);
  pinMode(Pin_AngleHi,  INPUT_PULLDOWN); digitalWrite(Pin_AngleHi,  LOW); pinMode(Pin_AngleHi,  OUTPUT);
  pinMode(Pin_AngleSet, INPUT_PULLDOWN); digitalWrite(Pin_AngleSet, LOW); pinMode(Pin_AngleSet, OUTPUT);
  pinMode(Pin_LengthHi, INPUT_PULLDOWN); digitalWrite(Pin_LengthHi, LOW); pinMode(Pin_LengthHi, OUTPUT);
  pinMode(Pin_LengthLow,INPUT_PULLDOWN); digitalWrite(Pin_LengthLow,LOW); pinMode(Pin_LengthLow,OUTPUT);
  pinMode(Pin_LoadHi,   INPUT_PULLDOWN); digitalWrite(Pin_LoadHi,   LOW); pinMode(Pin_LoadHi,   OUTPUT);  // GPIO12: strap pin
  pinMode(Pin_LoadSet,  INPUT_PULLDOWN); digitalWrite(Pin_LoadSet,  LOW); pinMode(Pin_LoadSet,  OUTPUT);

  // 3) Khẳng định lại mức LOW (an toàn kép)
  digitalWrite(Pin_CabMax,   LOW);
  digitalWrite(Pin_AngleHi,  LOW);
  digitalWrite(Pin_AngleSet, LOW);
  digitalWrite(Pin_LengthHi, LOW);
  digitalWrite(Pin_LengthLow,LOW);
  digitalWrite(Pin_LoadHi,   LOW);
  digitalWrite(Pin_LoadSet,  LOW);

  // (tuỳ chọn) chờ 10–20ms để module relay ổn định nguồn đầu vào
  vTaskDelay(pdMS_TO_TICKS(20));

  for(;;)
  {
    // Giữ test mode như hiện tại (đang luôn chạy). Nếu muốn chỉ chạy khi Mode_Test_Relay=1,
    // bạn có thể bọc điều kiện nhưng mình không tự ý đổi logic.
    RelayTestMode();

    if(Page_status!=12)
    {
      ///// Process Angle Alarm ///////
      if(Angle_value<Angle_alarm_set) {
        Stt_AngleSet=1; Stt_AngleHi=0;
      } else if(Angle_value<Angle_alarm_max) {
        Stt_AngleSet=0; Stt_AngleHi=0;
      } else {
        Stt_AngleSet=0; Stt_AngleHi=1;
      }

      ///// Process Length Alarm Low ///////
      Stt_LengthLow = (Length_value<Length_alarm_min) ? 1 : 0;

      ///// Process Length Alarm Hi ///////
      Stt_LengthHi  = (Length_value>=Length_alarm_max) ? 1 : 0;

      ///// Process Load Alarm ///////
      if(Loadpercent<Load_alarm_set) {
        Stt_LoadHi=0; Stt_LoadSet=0; Load_stt=0;
      } else if(Loadpercent<(Load_alarm_max-0.1)) {
        Stt_LoadHi=0; Stt_LoadSet=1; Load_stt=1;
      } else {
        Stt_LoadHi=1; Stt_LoadSet=0; Load_stt=2;
      }

      // DigitalInput_1 kích CabMax
      Stt_CabMax = (DigitalInput_1==1) ? 1 : 0;
    }

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}