#ifndef TaskSensor_H
#define TaskSensor_H

#include <Arduino.h>

extern uint32_t Loadcell1_raw;
extern uint32_t Loadcell2_raw;
extern float Loadcell1_value;
extern float Loadcell2_value;
extern float Loadcelltotal_value;

extern float Loadcell1_value_calib0;       // Load1
extern float Loadcell1_value_calib1;       // Load2
extern float Loadcell2_value_calib0;       // Load3
extern float Loadcell2_value_calib1;       // Load4
extern uint32_t Loadcell1_raw_calib0;      // Load5
extern uint32_t Loadcell1_raw_calib1;      // Load6
extern uint32_t Loadcell2_raw_calib0;      // Load7
extern uint32_t Loadcell2_raw_calib1;      // Load8


extern bool DigitalInput_1;
extern bool DigitalInput_2;
extern bool DigitalInput_3;
extern bool DigitalInput_4;

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