#ifndef TaskSensor_H
#define TaskSensor_H

#include <Arduino.h>

extern uint32_t Loadcell1_raw;
extern uint32_t Loadcell2_raw;
extern bool DigitalInput_1;
extern bool DigitalInput_2;
extern bool DigitalInput_3;

extern uint16_t Angle_raw;
extern uint16_t Length_raw;
extern uint16_t P1_raw;
extern uint16_t P2_raw;
extern uint16_t P3_raw;
extern uint16_t P4_raw;
extern uint16_t P5_raw;
extern float uc_Voltage;

void ReadADS1();
void ReadADS2();
void ReadLoadcell1();
void ReadLoadcell2();
void ReadInput();

void Task_Sensor_code( void * pvParameters );

#endif