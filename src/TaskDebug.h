#ifndef TaskDebug_H
#define TaskDebug_H

#include "Arduino.h"

// #define DEBUG_VALUE
extern const uint8_t Led1;
extern uint8_t result_comunication_HMI;
extern float Angle_value; 
extern float Length_value;
extern float W_value;
extern float MaxW_value;
extern uint16_t Cab_number;
extern float R_value;
extern float H_value;
extern uint16_t Loadpercent;

extern volatile uint16_t Sohang;
extern volatile uint16_t Socot;
extern volatile uint16_t Stt;   
extern volatile uint8_t is_LT_ok;

void Task_Debug_code( void * pvParameters );

#endif