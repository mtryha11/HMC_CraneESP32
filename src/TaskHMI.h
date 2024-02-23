#ifndef TaskHMI_H
#define TaskHMI_H

#include <Arduino.h>



void preTransmission(void);
void postTransmission(void);

void Float_to_Register(float variable,uint8_t register0, uint8_t register1);
void Word_to_Register(uint16_t variable,uint8_t register2);

#define Trigger_Page_addr           22
#define Multi_Loadtable_State_addr  27

#define Screen_no_status_addr       40001
#define Screen_no_control_addr      40032
#define Load_stt_addr               40060
#define Angle_value_addr            40051
#define Length_value_addr           40053
#define Cab_number_addr             40059
#define Angle_value_calib0_addr     40101
#define Angle_value_calib1_addr     40103
#define Length_value_calib0_addr    40105
#define Length_value_calib1_addr    40107
#define Angle_alarm_min_addr        40136
#define Length_alarm_min_addr       40141
#define Angle_raw_calib0_addr       40124
#define Length_raw_calib0_addr      40126
#define Angle_raw_addr              40301
#define Length_raw_addr             40302
#define Device_addr                 40031
#define P1_range_addr               40117

#define P_main_raw_addr         	40303
#define P_main_value_addr           40069
#define Load_alarm_set_addr         40139
#define T0_value_addr               40147
#define Load_table_value_addr       40083
#define Length_banhxich_addr        40053
#define Parar_addr                  40201

      



extern const uint8_t Led1;

#define SerialRS485 Serial2
const uint8_t DE_pin = 4;

extern volatile uint16_t Stt;
extern uint16_t Doitrong[10];
extern uint8_t result_comunication_HMI;
extern uint8_t device_type;
extern uint8_t Load_stt;
extern uint16_t Loadpercent;
extern bool flag_setLoad0_Whell;
extern bool flag_setLoad0_Crawler;
extern bool Main_Aux;
extern uint16_t Cab_main_number;
extern uint16_t Cab_aux_number;
extern float Angle_value; 
extern float Length_value;
extern float W_value;
extern float MaxW_value;
extern uint16_t Cab_number;
extern float Length_xich_nhap;
extern float R_value;
extern float H_value;
extern float Angle_value_calib0;
extern float Angle_value_calib1;
extern float Length_value_calib0;
extern float Length_value_calib1;
extern float Loadcell1_value_calib0;
extern float Loadcell1_value_calib1;
extern float Loadcell2_value_calib0;
extern float Loadcell2_value_calib1;
extern uint16_t Angle_alarm_min;
extern uint16_t Angle_alarm_set;
extern uint16_t Angle_alarm_max;
extern uint16_t Load_alarm_set;
extern uint16_t Load_alarm_max;
extern float Length_alarm_min;
extern float Length_alarm_set;
extern float Length_alarm_max;
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
extern bool Multi_Loadtable_State;
extern float T0_value;
extern float T0_P_main;
extern float T0_P_aux;
extern float T0_Length;
extern float T0_Angle;
extern float P_main_value;
extern float P_aux_value;
extern float P1_value;
extern float P2_value;
extern float P3_value;
extern float P4_value;
extern float P5_value;
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
extern float Load_table_value;
extern bool Trigger_LT;
extern bool DigitalInput_1;
extern bool DigitalInput_2;
extern bool DigitalInput_3;

extern bool is_ads1_init_ok;
extern bool is_ads2_init_ok;
extern bool is_hx7111_init_ok;
extern bool is_hx7112_init_ok;
extern bool is_rom_init_ok;
extern bool Mode_Test_Relay;

extern bool Stt_CabMax;
extern bool Stt_AngleHi;
extern bool Stt_AngleSet;
extern bool Stt_LengthHi;
extern bool Stt_LengthLow;
extern bool Stt_LoadHi;
extern bool Stt_LoadSet;

extern bool Stt_LoadHi;
extern bool Stt_LoadSet;

extern volatile uint16_t Sohang;
extern volatile uint16_t Socot; 
extern float Loadcell1_value;
extern float Loadcell2_value;
extern float Loadcelltotal_value;

extern float P0_value;
extern float P0_Loadcell;
extern float P0_Length;
extern float P0_Angle;
extern float L0_value;
extern float P0_L0_value;

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

extern uint16_t Ptramboom_05;
extern uint16_t Ptramboom_10;
extern uint16_t Ptramboom_15;
extern uint16_t Ptramboom_20;
extern uint16_t Ptramboom_25;
extern uint16_t Ptramboom_30;
extern uint16_t Ptramboom_35;
extern uint16_t Ptramboom_40;
extern uint16_t Ptramboom_45;
extern uint16_t Ptramboom_50;
extern uint16_t Ptramboom_55;
extern uint16_t Ptramboom_60;
extern uint16_t Ptramboom_65;
extern uint16_t Ptramboom_70;
extern uint16_t Ptramboom_75;
extern uint16_t Ptramboom_80;
extern uint16_t Ptramboom_85;
extern uint16_t Ptramboom_90;

void Task_HMI_code( void * pvParameters );

#endif