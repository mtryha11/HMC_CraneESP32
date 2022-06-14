#ifndef Main_H
#define Main_H

#include "Arduino.h"
#include <stdint.h>

#include "TaskCaculate.h"
#include "TaskHMI.h"
#include "TaskDebug.h"
#include "TaskAlarm.h"
#include "TaskSensor.h"
#include "TaskLoadTB.h"
#include "TaskWifiOTA.h"
#include "TaskCAN.h"

uint8_t result_comunication_HMI;
uint8_t device_type=1;

const uint8_t Led1 = 2;


uint16_t data[6];

// Bien cai dat
float Angle_value_calib0;           // A1
float Angle_value_calib1;           // A2
float Length_value_calib0;          // L1
float Length_value_calib1;          // L2

float Loadcell1_value_calib0;       // Load1
float Loadcell1_value_calib1;       // Load2
float Loadcell2_value_calib0;       // Load3
float Loadcell2_value_calib1;       // Load4
uint32_t Loadcell1_raw_calib0;      // Load5
uint32_t Loadcell1_raw_calib1;      // Load6
uint32_t Loadcell2_raw_calib0;      // Load7
uint32_t Loadcell2_raw_calib1;      // Load8

float Length_xich_nhap;             // L_xich
uint16_t P1_range;                  // P1
uint16_t P2_range;                  // P2
uint16_t P3_range;                  // P3
uint16_t P4_range;                  // P4
uint16_t P5_range;                  // P5
uint16_t P_main_select;             // P6
uint16_t P_aux_select;              // P7
uint16_t Angle_raw_calib0;          // A3
uint16_t Angle_raw_calib1;          // A4
uint16_t Length_raw_calib0;         // L3
uint16_t Length_raw_calib1;         // L4



bool Multi_Loadtable_State;         // LTB_state
bool Main_Aux;                      // Main_Aux
uint16_t Cab_main_number;           // Cab_main_num
uint16_t Cab_aux_number;            // Cab_aux_num


float Parar;                        // Parar  
float Parah;                        // Parah; 
float ParaCabW;                     // ParaCabW
float Paraa;                        // Paraa
float Parab;                        // Parab
float Parac;                        // Parac
float Parad;                        // Parad
float ParaE;                        // ParaE
float Parag;                        // Parag
float Paran;                        // Paran
float ParaK1;                       // ParaK1
float ParaK2;                       // ParaK2
float ParaK3;                       // ParaK3
float ParaK4;                       // ParaK4


// Bien tinh toan
float Angle_value; 
float Length_value;
float W_value;
float MaxW_value;
uint16_t Cab_number;
float R_value;
float H_value;
uint16_t Loadpercent;
uint8_t Load_stt;
float P_main_value;
float P_aux_value;
float P1_value;
float P2_value;
float P3_value;
float P4_value;
float P5_value;
float Load_table_value;
float Loadcell1_value;
float Loadcell2_value;
float Loadcelltotal_value;
bool Trigger_LT;

float T0_value;                      // T0_value
float T0_P_main;                     // T0_P_main
float T0_P_aux;                      // T0_P_aux
float T0_Length;                     // T0_Length
float T0_Angle;                      // T0_Angle

float L0_value;
float M0_value;
float P0_value;
float P0_Loadcell;
float P0_Length;
float P0_Angle;
float P0_L0_value;

// Bien doc tu cam bien
uint16_t Angle_raw;
uint16_t Length_raw;
uint16_t P_main_raw;
uint16_t P_aux_raw;
uint16_t P1_raw;
uint16_t P2_raw;
uint16_t P3_raw;
uint16_t P4_raw;
uint16_t P5_raw;
uint32_t Loadcell1_raw;
uint32_t Loadcell2_raw;
uint16_t Resistor_4_20ma=150;
float uc_Voltage;

// Bien alarm
uint16_t Angle_alarm_min;       // A4
uint16_t Angle_alarm_set;       // A5
uint16_t Angle_alarm_max;       // A6
uint16_t Load_alarm_set;        // LoadS
uint16_t Load_alarm_max;        // LoadM
float Length_alarm_min;         // L5
float Length_alarm_set;         // L6
float Length_alarm_max;         // L7

bool DigitalInput_1;
bool DigitalInput_2;
bool DigitalInput_3;

volatile uint16_t Sohang;
volatile uint16_t Socot;    
volatile uint16_t Stt;    
uint16_t Doitrong[10];

uint16_t Taiphantram_05;
uint16_t Taiphantram_10;
uint16_t Taiphantram_15;
uint16_t Taiphantram_20;
uint16_t Taiphantram_25;
uint16_t Taiphantram_30;
uint16_t Taiphantram_35;
uint16_t Taiphantram_40;
uint16_t Taiphantram_45;
uint16_t Taiphantram_50;
uint16_t Taiphantram_55;
uint16_t Taiphantram_60;
uint16_t Taiphantram_65;
uint16_t Taiphantram_70;
uint16_t Taiphantram_75;
uint16_t Taiphantram_80;
uint16_t Taiphantram_85;
uint16_t Taiphantram_90;



uint16_t LT[800];
volatile uint8_t is_LT_ok=0;

bool flag_setLoad0_Whell=0;
bool flag_setLoad0_Crawler=0;
#endif