#ifndef TaskAlarm_H
#define TaskAlarm_H

#include "Arduino.h"

void Relay_process(uint8_t Relaypin,bool Status);
void RelayTestMode();
void Task_Alarm_code( void * pvParameters );
extern uint8_t Page_status;
extern float Angle_value; 
extern float Length_value;
extern float W_value;
extern uint16_t Loadpercent;
extern uint8_t Load_stt;

extern uint16_t Angle_alarm_min;       // A4
extern uint16_t Angle_alarm_set;       // A5
extern uint16_t Angle_alarm_max;       // A6
extern uint16_t Load_alarm_set;        // LoadS
extern uint16_t Load_alarm_max;        // LoadM
extern float Length_alarm_min;         // L5
extern float Length_alarm_set;         // L6
extern float Length_alarm_max;         // L7
extern bool DigitalInput_1;


#endif