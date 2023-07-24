#include <Arduino.h>
#include <TaskAlarm.h>
bool Mode_Test_Relay=0;

bool Stt_CabMax=0;
bool Stt_AngleHi=1;
bool Stt_AngleSet=0;
bool Stt_LengthHi=0;
bool Stt_LengthLow=0;
bool Stt_LoadHi=0;
bool Stt_LoadSet=0;
extern bool Bypass;
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
pinMode(Pin_CabMax,OUTPUT); 
pinMode(Pin_AngleHi,OUTPUT); 
pinMode(Pin_AngleSet,OUTPUT); 
pinMode(Pin_LengthHi,OUTPUT); 
pinMode(Pin_LengthLow,OUTPUT); 
pinMode(Pin_LoadHi,OUTPUT); 
pinMode(Pin_LoadSet,OUTPUT); 

digitalWrite(Pin_CabMax,LOW);
digitalWrite(Pin_AngleHi,LOW);
digitalWrite(Pin_AngleSet,LOW);
digitalWrite(Pin_LengthHi,LOW);
digitalWrite(Pin_LengthLow,LOW);
digitalWrite(Pin_LoadHi,LOW);
digitalWrite(Pin_LoadSet,LOW);

  for(;;)
  {
    RelayTestMode();
    if(Page_status!=12)
    {
      ///// Process Angle Alarm ///////
      // if(Angle_value<Angle_alarm_set)
      // {
      //   Stt_AngleSet=1;
      //   Stt_AngleHi=0;
      // }
      // else if((Angle_value>=Angle_alarm_set) && (Angle_value<Angle_alarm_max))
      // {
      //   Stt_AngleSet=0;
      //   Stt_AngleHi=0;
      // }
      // else
      // {
      //   Stt_AngleSet=0;
      //   Stt_AngleHi=1;
      // }
      ///// Process Angle Alarm ///////

      // ///// Process Length Alarm Low ///////
      // if(Length_value<Length_alarm_min)
      // {
      //   Stt_LengthLow=1;
      // }
      // else
      // {
      //   Stt_LengthLow=0;
      // }
      // ///// Process Length Alarm Low ///////

      // ///// Process Length Alarm Hi ///////
      // if(Length_value>=Length_alarm_max)
      // {
      //   Stt_LengthHi=1;
      // }
      // else
      // {
      //   Stt_LengthHi=0;
      // }
      // ///// Process Length Alarm Hi ///////

      ///// Process Load Alarm ///////
      if(Loadpercent<Load_alarm_set)
      {
        Stt_LoadHi=0;
        Stt_LoadSet=0;
        Load_stt=0;
      }
      else if((Loadpercent>=Load_alarm_set) && (Loadpercent<(Load_alarm_max-0.1)))
      {
        Stt_LoadHi=0;
        Stt_LoadSet=1;
        Load_stt=1;
        Bypass=0;
      }
      else if(Loadpercent>=(Load_alarm_max-0.1))
      {
        Stt_LoadHi=1;
        Stt_LoadSet=0;
        Load_stt=2;
      }
      ///// Process Load Alarm ///////

    if(DigitalInput_1==0)
    {
      Stt_CabMax=0;
    }
    else
    {
      Stt_CabMax=1;
    }

    if(DigitalInput_2==0)
    {
      Stt_LengthLow=0;
    }
    else
    {
      Stt_LengthLow=1;
    }

    if(DigitalInput_3==0)
    {
      Stt_LengthHi=0;
    }
    else
    {
      Stt_LengthHi=1;
    }

    }
    //Serial.println("TaskRelay");
    vTaskDelay(100);
  }
}