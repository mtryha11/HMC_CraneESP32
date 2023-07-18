#ifndef TaskLoadTB_H
#define TaskLoadTB_H

#include <Arduino.h>

void Task_LoadTB_code( void * pvParameters );

extern uint16_t Cab_main_number;           // Cab_main_num
extern uint16_t Cab_aux_number;            // Cab_aux_num
extern bool Main_Aux;                      // Main_Aux
extern uint8_t device_type;                // DT
extern bool Multi_Loadtable_State;         // LTB_state
extern float Angle_value_calib0;           // A1
extern float Angle_value_calib1;           // A2
extern uint16_t Angle_raw_calib0;          // A3
extern uint16_t Angle_raw_calib1;          // A4
extern uint16_t Angle_alarm_min;           // A5
extern uint16_t Angle_alarm_set;           // A6
extern uint16_t Angle_alarm_max;           // A7


extern float Length_value_calib0;          // L1
extern float Length_value_calib1;          // L2
extern uint16_t Length_raw_calib0;         // L3
extern uint16_t Length_raw_calib1;         // L4
extern float Length_alarm_min;             // L5
extern float Length_alarm_set;             // L6
extern float Length_alarm_max;             // L7
extern uint16_t Load_alarm_set;            // LoadS
extern uint16_t Load_alarm_max;            // LoadM
extern uint16_t P1_range;                  // P1
extern uint16_t P2_range;                  // P2
extern uint16_t P3_range;                  // P3
extern uint16_t P4_range;                  // P4
extern uint16_t P5_range;                  // P5
extern uint16_t P_main_select;             // P6
extern uint16_t P_aux_select;              // P7

extern float Parar;                        // Parar  
extern float Parah;                        // Parah; 
extern float ParaCabW;                     // ParaCabW
extern float Paraa;                        // Paraa
extern float Parab;                        // Parab
extern float Parac;                        // Parac
extern float Parad;                        // Parad
extern float ParaE;                        // ParaE
extern float Parag;                        // Parag
extern float Paran;                        // Paran
extern float ParaK1;                       // ParaK1
extern float ParaK2;                       // ParaK2
extern float ParaK3;                       // ParaK3
extern float ParaK4;                       // ParaK4

extern float T0_value;                      // T0_value
extern float T0_P_main;                     // T0_P_main
extern float T0_P_aux;                      // T0_P_aux
extern float T0_Length;                     // T0_Length
extern float T0_Angle;                      // T0_Angle

extern float P0_value;                      // P0_value
extern float P0_Loadcell;                   // P0_Loadcell
extern float P0_Length;                     // P0_Length
extern float P0_Angle;                      // P0_Angle
extern float P0_L0_value;

extern float Loadcell1_value_calib0;       // Load1
extern float Loadcell1_value_calib1;       // Load2
extern float Loadcell2_value_calib0;       // Load3
extern float Loadcell2_value_calib1;       // Load4
extern uint32_t Loadcell1_raw_calib0;      // Load5
extern uint32_t Loadcell1_raw_calib1;      // Load6
extern uint32_t Loadcell2_raw_calib0;      // Load7
extern uint32_t Loadcell2_raw_calib1;      // Load8


extern float Length_value;
extern float Length_xich_nhap;
/////////////// Bang tai ////////////////
#define Sohang_Socot_addr           5498

extern volatile uint16_t Sohang;
extern volatile uint16_t Socot;
extern volatile uint16_t Stt;
extern float Load_table_value;   
extern uint16_t Doitrong[10];
extern uint16_t LT[800];
extern volatile uint8_t is_LT_ok;
extern bool Trigger_LT;

extern uint16_t Taiphantram_05;
extern uint16_t Taiphantram_10;
extern uint16_t Taiphantram_15;
extern uint16_t Taiphantram_20;
extern uint16_t Taiphantram_25;
extern uint16_t Taiphantram_30;
extern uint16_t Taiphantram_35;
extern uint16_t Taiphantram_40;
extern uint16_t Taiphantram_45;
extern uint16_t Taiphantram_50;
extern uint16_t Taiphantram_55;
extern uint16_t Taiphantram_60;
extern uint16_t Taiphantram_65;
extern uint16_t Taiphantram_70;
extern uint16_t Taiphantram_75;
extern uint16_t Taiphantram_80;
extern uint16_t Taiphantram_85;
extern uint16_t Taiphantram_90;

#endif