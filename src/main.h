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
// #include "TaskCAN.h"

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

uint8_t Canphu;
float Length_aux_value=12.2;
float Angle_aux_value=30;
float R_aux_value;
float H_aux_value;
float R_total;
float H_total;

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
bool DigitalInput_4;

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

uint16_t Ptramboom_05;
uint16_t Ptramboom_10;
uint16_t Ptramboom_15;
uint16_t Ptramboom_20;
uint16_t Ptramboom_25;
uint16_t Ptramboom_30;
uint16_t Ptramboom_35;
uint16_t Ptramboom_40;
uint16_t Ptramboom_45;
uint16_t Ptramboom_50;
uint16_t Ptramboom_55;
uint16_t Ptramboom_60;
uint16_t Ptramboom_65;
uint16_t Ptramboom_70;
uint16_t Ptramboom_75;
uint16_t Ptramboom_80;
uint16_t Ptramboom_85;
uint16_t Ptramboom_90;


uint16_t LT[800];
// 13 cot 22 hang
uint16_t LT_main[380]={
0		,1220	,1520	,1830	,2440	,3050	,3660	,4270	,4880	,5490	,5790	,6100	,6110
,300	,8000 	,6950	,6990	,5090	,4460	,3490	,2740	,1920	,1490	,1330	,1110	,1110
,350	,7630	,6950	,6990	,5090	,4460	,3490	,2740	,1920	,1490	,1330	,1110	,1110
,400	,6950	,6950	,6990	,5090	,4460	,3490	,2740	,1920	,1490	,1330	,1110	,1110
,450	,6180	,6170	,6200	,5090	,4460	,3490	,2740	,1920	,1490	,1330	,1110	,1110
,550	,5120	,5130	,5110	,5090	,4460	,3490	,2740	,1920	,1490	,1330	,1110	,1110
,600	,4540	,4530	,4520	,4510	,4460	,3490	,2740	,1920	,1490	,1330	,1110	,1110
,700	,3590	,3580	,3570	,3560	,3530	,3490	,2740	,1920	,1490	,1330	,1110	,1110
,800	,2930	,2940	,2930	,2920	,2910	,2890	,2740	,1920	,1490	,1330	,1110	,1110
,1000	,2170	,2160	,2150	,2130	,2120	,2100	,2100	,1920	,1490	,1330	,1110	,1110
,1200	,1640	,1700	,1680	,1670	,1650	,1640	,1630	,1620	,1410	,1250	,1110	,1110
,1400	,0		,1390	,1380	,1360	,1340	,1320	,1320	,1310	,1290	,1190	,1050	,1050
,1600	,0		,0		,1160	,1140	,1120	,1110	,1110	,1090	,1070	,1070	,990	,990
,1800	,0		,0		,0		,945	,925	,915	,905	,890	,870	,870	,825	,825
,2200	,0		,0		,0		,750	,730	,720	,700	,690	,670	,670	,660	,660
,2400	,0		,0		,0		,0		,630	,615	,595	,580	,560	,560	,550	,550
,2800	,0		,0		,0		,0		,530	,510	,490	,470	,450	,450	,440	,440
,3000	,0		,0		,0		,0		,0		,465	,440	,425	,405	,405	,395	,395
,3200	,0		,0		,0		,0		,0		,420	,390	,380	,360	,360	,350	,350
,3400	,0		,0		,0		,0		,0		,390	,360	,340	,320	,320	,310	,310
,3600	,0		,0		,0		,0		,0		,0		,330	,310	,290	,290	,275	,275
,3800	,0		,0		,0		,0		,0		,0		,300	,280	,260	,260	,240	,240
,4000	,0		,0		,0		,0		,0		,0		,280	,260	,230	,230	,220	,220
,4200	,0		,0		,0		,0		,0		,0		,0		,235	,205	,205	,195	,195
,4400	,0		,0		,0		,0		,0		,0		,0		,210	,180	,180	,170	,170
,4600	,0		,0		,0		,0		,0		,0		,0		,0		,160	,160	,140	,140
,4800	,0		,0		,0		,0		,0		,0		,0		,0		,135	,0		,0		,0
,5200	,0		,0		,0		,0		,0		,0		,0		,0		,110	,0		,0		,0
};

// 7 cot 12 hang
uint16_t LT_canphu_10_12[84]={0		,2440	,3050	,3960	,4880	,5490	,5491
,1000	,1080	,1080	,1080	,1030	,810	,810
,1200	,1080	,1080	,1080	,1030	,810	,810
,1400	,1070	,1080	,1080	,1030	,810	,810
,1800	,860	,960	,950	,920	,810	,810
,2400	,660	,650	,620	,600	,580	,580
,3000	,490	,470	,440	,410	,400	,400
,3600	,0		,350	,320	,290	,280	,280
,4200	,0		,0		,240	,210	,180	,180
,4400	,0		,0		,220	,190	,160	,160
,4800	,0		,0		,0		,140	,120	,120
,5200	,0		,0		,0		,120	,0		,0};

// 7 cot 12 hang
uint16_t LT_canphu_30_12[84]={
0		,2440	,3050	,3960	,4880	,5490	,5491
,1000	,690	,680	,660	,680	,620	,620
,1200	,690	,680	,660	,680	,620	,620
,1400	,680	,680	,660	,680	,620	,620
,1800	,590	,620	,660	,680	,620	,620
,2400	,500	,530	,570	,600	,620	,620
,3000	,0		,470	,470	,450	,430	,430
,3600	,0		,0		,340	,320	,300	,300
,4200	,0		,0		,0		,230	,210	,210
,4400	,0		,0		,0		,220	,180	,180
,4800	,0		,0		,0		,0		,0		,0
,5200	,0		,0		,0		,0		,0		,0};

// 7 cot 12 hang
uint16_t LT_canphu_10_15[84]={
0		,2440	,3050	,3960	,4880	,5490	,5491
,1000	,900	,900	,900	,870	,740	,740
,1200	,900	,900	,900	,870	,740	,740
,1400	,890	,900	,900	,870	,740	,740
,1800	,720	,790	,880	,870	,740	,740
,2400	,550	,610	,630	,610	,590	,590
,3000	,440	,470	,450	,420	,400	,400
,3600	,390	,360	,330	,300	,280	,280
,4200	,0		,290	,250	,200	,190	,190
,4400	,0		,0		,220	,180	,160	,160
,4800	,0		,0		,190	,130	,120	,120
,5200	,0		,0		,0		,120	,0		,0};

// 7 cot 12 hang
uint16_t LT_canphu_30_15[84]={
0		,2440	,3050	,3960	,4880	,5490	,5491
,1000	,480	,500	,520	,510	,480	,480
,1200	,480	,500	,520	,510	,480	,480
,1400	,480	,500	,520	,510	,480	,480
,1800	,480	,500	,520	,510	,480	,480
,2400	,400	,420	,450	,470	,480	,480
,3000	,340	,370	,390	,420	,430	,430
,3600	,0		,0		,350	,330	,310	,310
,4200	,0		,0		,0		,240	,220	,220
,4400	,0		,0		,0		,220	,200	,200
,4800	,0		,0		,0		,0		,150	,150
,5200	,0		,0		,0		,0		,0		,0};

volatile uint8_t is_LT_ok=0;

bool flag_setLoad0_Whell=0;
bool flag_setLoad0_Crawler=0;
#endif