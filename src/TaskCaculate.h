#ifndef TaskCaculate_H
#define TaskCaculate_H

#include "Arduino.h"
#include <math.h>
#include "MapFloat.h"

extern uint8_t device_type;

extern float Angle_value_calib0;
extern float Angle_value_calib1;
extern float Length_value_calib0;
extern float Length_value_calib1;
extern float Loadcell1_value_calib0;
extern float Loadcell1_value_calib1;
extern float Loadcell2_value_calib0;
extern float Loadcell2_value_calib1;
extern uint16_t P1_range;
extern uint16_t P2_range;
extern uint16_t P3_range;
extern uint16_t P4_range;
extern uint16_t P5_range;
extern uint16_t P_main_select;
extern uint16_t P_aux_select;
extern uint16_t Angle_raw_calib0;
extern uint16_t Angle_raw_calib1;
extern uint16_t Length_raw_calib0;
extern uint16_t Length_raw_calib1;
extern uint32_t Loadcell1_raw_calib0;
extern uint32_t Loadcell1_raw_calib1;
extern uint32_t Loadcell2_raw_calib0;
extern uint32_t Loadcell2_raw_calib1;
extern bool Multi_Loadtable_State;
extern bool Main_Aux;
extern uint16_t Cab_main_number;
extern uint16_t Cab_aux_number;

extern float Parar;
extern float Parah;
extern float ParaCabW;
extern float Paraa;
extern float Parab;
extern float Parac;
extern float Parad;
extern float ParaE;
extern float Parag;
extern float Paran;
extern float ParaK1;
extern float ParaK2;
extern float ParaK3;
extern float ParaK4;

extern float Angle_value; 
extern float Length_value;
extern float W_value;
extern float MaxW_value;
extern uint16_t Cab_number;
extern float R_value;
extern float H_value;
extern uint16_t Loadpercent;
extern float P_main_value;
extern float P_aux_value;
extern float P1_value;
extern float P2_value;
extern float P3_value;
extern float P4_value;
extern float P5_value;
extern float Load_table_value;
extern float Loadcell1_value;
extern float Loadcell2_value;
extern float Loadcelltotal_value;

extern float T0_value;
extern float T0_P_main;
extern float T0_P_aux;
extern float T0_Length;
extern float T0_Angle;

extern float L0_value;
extern float M0_value;
extern float P0_value;
extern float P0_Loadcell;
extern float P0_Length;
extern float P0_Angle;
extern float P0_L0_value;

extern uint16_t Angle_raw;
extern uint16_t Length_raw;
extern uint16_t P_main_raw;
extern uint16_t P_aux_raw;
extern uint16_t P1_raw;
extern uint16_t P2_raw;
extern uint16_t P3_raw;
extern uint16_t P4_raw;
extern uint16_t P5_raw;
extern uint32_t Loadcell1_raw;
extern uint32_t Loadcell2_raw;
extern uint16_t Resistor_4_20ma;

// Bien alarm
extern uint16_t Angle_alarm_min;
extern uint16_t Angle_alarm_set;
extern uint16_t Angle_alarm_max;
extern uint16_t Load_alarm_set;
extern uint16_t Load_alarm_max;
extern float Length_alarm_min;
extern float Length_alarm_set;
extern float Length_alarm_max;
extern bool flag_setLoad0_Whell;
extern bool flag_setLoad0_Crawler;

extern volatile uint16_t Sohang;
extern volatile uint16_t Socot;
extern volatile uint16_t Stt;   
extern uint16_t LT[600];


void Calculate_H_R();
void Calculate_Angle(void);
void Calculate_Length(void);
void Calculate_Press(void);
void Calib0_Banhlop(void);
void Calib0_Banhxich(void);
void Calculate_Loadcell(void);
void Tinhtoantaimax_bangtai_phantramtai(void);
float CalculateMaxWe();

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

/*------------------------------------------------------
   Ham tinh toan m lien tuc cho xe banh lop
   Description: 
------------------------------------------------------*/
float Wheel_Calculatem(void);
/*------------------------------------------------------
   Ham tinh toan T lien tuc cho xe banh lop
   Description: 
------------------------------------------------------*/
float Wheel_CalculateT(void);
/*------------------------------------------------------
   Ham tinh toan T0 ban dau cho xe banh lop
   Description: 
------------------------------------------------------*/
float Wheel_CalculateT0(void);

/*------------------------------------------------------
Ham tinh toan L0 ban dau cho xe banh xich
   Description: 
------------------------------------------------------*/
float CalculateL0(void);
/*------------------------------------------------------
   Ham tinh toan m0 ban dau cho xe banh xich
   Description: 
------------------------------------------------------*/
float Calculatem0(void);
/*------------------------------------------------------
   Ham tinh toan tai vi tri ban dau cho xe banh xich
   Description: 
------------------------------------------------------*/
float Crawler_CalculateP0(void);

/*------------------------------------------------------
   Ham tinh toan m cho xe banh xich
   Description: 
------------------------------------------------------*/
float Calculatem();

/*------------------------------------------------------
   Ham tinh toan tai cho xe banh xich
   Description: 
------------------------------------------------------*/
float Crawler_CalculateP();

void Calculate_Press_Loadcell();

float Tinhtaibangloadcell_tructiep();

void Calibtaitungdoan5do();

void Task_Caculate_code( void * pvParameters );

#endif