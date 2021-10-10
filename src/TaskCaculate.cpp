#include <Arduino.h>
#include <TaskCaculate.h>
#include <Preferences.h>
#include <ModbusMaster.h>
#include <Preferences.h>

extern ModbusMaster node;
extern Preferences preferences;

void Calculate_H_R()
{
  float temp1=(Angle_value*PI/180);
  R_value=cos(temp1)*Length_value + Parar;
  H_value=sin(temp1)*Length_value + Parah;
}

void Calculate_Angle()
{
  Angle_value=mapFloat(Angle_raw, Angle_raw_calib0, Angle_raw_calib1, Angle_value_calib0, Angle_value_calib1);
}
void Calculate_Length()
{
  Length_value=mapFloat(Length_raw, Length_raw_calib0, Length_raw_calib1, Length_value_calib0, Length_value_calib1);
}

void Calculate_Loadcell()
{
  Loadcell1_value=mapFloat(Loadcell1_raw, Loadcell1_raw_calib0, Loadcell1_raw_calib1, Loadcell1_value_calib0, Loadcell1_value_calib1);
  Loadcell2_value=mapFloat(Loadcell2_raw, Loadcell2_raw_calib0, Loadcell2_raw_calib1, Loadcell2_value_calib0, Loadcell2_value_calib1);
  Loadcelltotal_value=Loadcell1_value+Loadcell2_value;
}

void Calculate_Press()
{
  P1_value=mapFloat(P1_raw, (4*Resistor_4_20ma), (20*Resistor_4_20ma), 0, P1_range);
  P2_value=mapFloat(P2_raw, (4*Resistor_4_20ma), (20*Resistor_4_20ma), 0, P2_range);
  P3_value=mapFloat(P3_raw, (4*Resistor_4_20ma), (20*Resistor_4_20ma), 0, P3_range);
  P4_value=mapFloat(P4_raw, (4*Resistor_4_20ma), (20*Resistor_4_20ma), 0, P4_range);
  P5_value=mapFloat(P5_raw, (4*Resistor_4_20ma), (20*Resistor_4_20ma), 0, P5_range);
  switch(P_main_select)
  {
    case(1):
    {
      P_main_value=P1_value;
      P_main_raw=P1_raw;
    }
    break;

    case(2):
    {
      P_main_value=P2_value;
      P_main_raw=P2_raw;
    }
    break;

    case(3):
    {
      P_main_value=P3_value;
      P_main_raw=P3_raw;
    }
    break;

    case(4):
    {
      P_main_value=P4_value;
      P_main_raw=P4_raw;
    }
    break;

    case(5):
    {
      P_main_value=P5_value;
      P_main_raw=P5_raw;
    }
    break;

    default:
    {
      P_main_value=P1_value;
      P_main_raw=P1_raw;
    }
    break;
  }

  switch(P_aux_select)
  {
    case(1):
    {
      P_aux_value=P1_value;
      P_aux_raw=P1_raw;
    }
    break;

    case(2):
    {
      P_aux_value=P2_value;
      P_aux_raw=P2_raw;
    }
    break;

    case(3):
    {
      P_aux_value=P3_value;
      P_aux_raw=P3_raw;
    }
    break;

    case(4):
    {
      P_aux_value=P4_value;
      P_aux_raw=P4_raw;
    }
    break;

    case(5):
    {
      P_aux_value=P5_value;
      P_aux_raw=P5_raw;
    }
    break;

    default:
    {
      P_aux_value=P2_value;
      P_aux_raw=P2_raw;
    }
    break;
  }
}
/*------------------------------------------------------
   Ham tinh toan m lien tuc cho xe banh lop
   Description: 
------------------------------------------------------*/
float Wheel_Calculatem()
{
  float tmp1,tmp2,tmp3,tmp4;
  tmp1=pow(Paraa,2);
  tmp2=pow(Parab,2);
  tmp3=pow(Parad,2);
  tmp4=tmp1+tmp2-tmp3;
  tmp1=2*Paraa*Parab;
  tmp2=tmp4/tmp1;
  tmp3=acos(tmp2);            // arccos
  tmp2=tmp3;                  // them K1 bo cai nay
  tmp1=Angle_value * PI / 180;
  tmp3=tmp1+tmp2;             // + Angle
  tmp2=cos(tmp3);             // cos ()
  tmp4=tmp2*2*Paraa*Parab;    //*2ab
  tmp1=pow(Paraa,2);
  tmp2=pow(Parab,2);
  tmp3=tmp1+tmp2-tmp4;        //a^2 + b^2 - Ans
  tmp4=sqrt(tmp3);
  return tmp4;
}
/*------------------------------------------------------
   Ham tinh toan T lien tuc cho xe banh lop
   Description: 
------------------------------------------------------*/
float Wheel_CalculateT()
{
  float tmp1,tmp2,tmp3,m;
  m=Wheel_Calculatem();
  tmp1=ParaE*P_main_value;                    //E*P
  tmp2=pow(Parag,2);                          //g^2*E*p      (1) OK
  tmp1=tmp2*tmp1;
  tmp2=ParaE*pow(Parag,2);                    //E*g^2
  tmp3=ParaE*pow(Parac,2);                    //E*c^2
  tmp2=tmp2-tmp3;                             //E*g^2- E*c^2
  tmp2=tmp2*P_aux_value;                      //P1 * (E*g^2 - E*c^2) (2) OK
  tmp1=tmp1-tmp2;                             //(1)-(2)      (12) OK
  tmp2=pow(Parab,2);                          //b^2
  tmp2=tmp2+pow(m,2);                         //b^2+m^2
  tmp2=tmp2-pow(Paraa,2);                     //b^2+m^2-a^2
  tmp3=2*Parab*m;                             //2*b*m     
  tmp2=tmp2/tmp3;                             //(b^2+m^2-a^2)/(2*b*m) (3)
  tmp2=acos(tmp2);                            //acos(3)
  tmp2=ParaE-2*tmp2;                          //E-2*acos(3)
  tmp2=tmp2/2;                                //(E-2*acos(3))/2    (4)
  tmp2=cos(tmp2);                             // cos(4)
  tmp1=tmp1*tmp2*2;                           // 2* cos(4) * (12) (5) OK
  tmp1=tmp1*Parab*Paran;                      // (5)*b*n
  tmp2=ParaK1*PI/180;                         //K1->rad
  tmp1=tmp1*cos(tmp2);                        //5*b*n*cos(K1)   (6) OK
  tmp2=T0_value*Length_value*ParaK2;          // T0*L*K2
  tmp3=Angle_value*PI/180;                    // Angle->rad
	tmp2=tmp2*cos(tmp3)*1000;                   //T0*L*K2*cos(alpha)*1000     (7) OK
  tmp1=tmp1-tmp2;                             //(6)-(7) OK
  tmp2=2*Length_value*ParaK2*cos(tmp3)*1000;  // 2*L*K2*cos(alpha)*1000 (8) OK
  tmp1=tmp1/tmp2;                             //((6)-(7))/(8) OK
  tmp3=tmp1+ParaK3;                           //T
  return tmp3;
}
/*------------------------------------------------------
   Ham tinh toan T0 ban dau cho xe banh lop
   Description: 
------------------------------------------------------*/
float Wheel_CalculateT0(void)
{
  float tmp1,tmp2,tmp3;
  tmp1=T0_P_main*ParaE;               //E*P0
  tmp1=tmp1*pow(Parag,2);             //E*g^2*p   (1)
  tmp2=ParaE*pow(Parag,2);            //E*g^2
  tmp3=ParaE*pow(Parac,2);            //E*c^2
  tmp2=tmp2-tmp3;                     //E*g^2-E*c^2
  tmp2=tmp2*T0_P_aux;                 //(E*g^2-E*c^2)*P1   (2)
  tmp1=tmp1-tmp2;                     //(1)-(2)      (12)    
  tmp2=pow(Parab,2);                  //b^2
  tmp2=tmp2+pow(Parad,2);             //b^2+d^2
  tmp2=tmp2-pow(Paraa,2);             //b^2-d^2-a^2
  tmp3=Parab*Parad;                   //b*d
  tmp3=tmp3*2;                        //2*b*d        
  tmp2=tmp2/tmp3;                     //(b^2-d^2-a^2)/(2*b*d)    (3)
  tmp2=acos(tmp2);                    //acos((3))
  tmp2=2*tmp2;                        //2*acos((3))
  tmp2=ParaE-tmp2;                    //E-2*acos((3))
  tmp2=tmp2/2;                        //(E-2*cos((3)))/2         (4)
  tmp2=cos(tmp2);                     //cos((4))        (34)
  tmp1=tmp1*tmp2*2;                   //(12) * (34) *2
  tmp1=tmp1*Parab;                    //(12) * (34) * b *2
  tmp1=tmp1*Paran;                    //(12) * (34) * b *2 *n
  tmp2=ParaK1*PI/180;                 //K1-> rad
  tmp2=cos(tmp2);                     //cos(K1)
  tmp1=tmp1*tmp2;                     //(12) * (34) * 2 * b * n * cos(K1)
  tmp2=Length_alarm_min*ParaK2*1000;  //Lmin*K2*1000
  tmp2=tmp1/tmp2;                     //T0
  return tmp2;
   //WRITE_FLOAT_EXT_EEPROM(T0Parameter,tmp2);
   //Ram_T0Parameter=READ_FLOAT_EXT_EEPROM(T0Parameter);
}

/*------------------------------------------------------
Ham tinh toan L0 ban dau cho xe banh xich
   Description: 
------------------------------------------------------*/
float CalculateL0()
{
   float tmp2,tmp3;
   tmp2=Length_value*ParaK2-Parad;   //L*k2-d
   
   tmp3=Parag/tmp2;
   tmp3=atan(tmp3);
   tmp3=cos(tmp3);
   tmp2=tmp2/tmp3;
  //  Serial.print("L0=");
  //  Serial.println(tmp2);
   return tmp2;
}

/*------------------------------------------------------
   Ham tinh toan m0 ban dau cho xe banh xich
   Description: 
------------------------------------------------------*/
float Calculatem0()
{
   float tmp2,tmp3;
   P0_L0_value=CalculateL0();
   tmp2=pow(Paraa,2);               //a^2
   tmp2=tmp2+pow(Parac,2);          //a^2+c^2
   tmp2=tmp2-pow(Parab,2);          //a^2+c^2-b^2  (1)
   tmp3=2*Paraa*Parac;              //2*a*c        (2)
   tmp2=tmp2/tmp3;                  //(1)/(2) (12)
   tmp2=acos(tmp2);                 //acos(12)
   tmp2=ParaE-tmp2;                 //E-acos(12)   (3)
   tmp3=Length_value*ParaK2-Parad;  // L*k2-d
   tmp3=Parag/tmp3;                 // g/L*2-d     (**)
   tmp3=atan(tmp3);                 // atan(**)  
   tmp2=tmp2-tmp3;                  // (3) - atan
   tmp2=tmp2-(Angle_value*PI/180);
   tmp2=cos(tmp2);                  //cos(3)
   tmp2=2*Paraa*P0_L0_value*tmp2;      //2 * a * L *cos(3)
   tmp3=pow(Paraa,2);               //a^2
   tmp3=tmp3+ pow(P0_L0_value,2);      //a^2+L^2
   tmp2=tmp3-tmp2;                  //a^2 + L^2 - 2*a*L*cos(3) (4)
   tmp2=sqrt(tmp2);
   //WRITE_FLOAT_EXT_EEPROM(M0Parameter,tmp2);
   // Ram_M0=READ_FLOAT_EXT_EEPROM(M0Parameter);
   return tmp2;
}

/*------------------------------------------------------
   Ham tinh toan tai vi tri ban dau cho xe banh xich
   Description: 
------------------------------------------------------*/
float Crawler_CalculateP0(void)
{
  float tmp1,tmp2,tmp3;
  M0_value=Calculatem0();
  tmp2=pow(M0_value,2);                           //mo^2
  tmp2=tmp2+pow(P0_L0_value,2);                      //mo^2+Lo^2
  tmp2=tmp2-pow(Paraa,2);                         //mo^2+Lo^2-a^2 (1)
  tmp3=2*M0_value*P0_L0_value;                       //2*m0*L        (2)
  tmp2=tmp2/tmp3;                                 //(1)/(2)       (12)
  tmp2=acos(tmp2);                                //acos(12)      (3)
  tmp2=sin(tmp2);                                 //sin(3)
  tmp2=tmp2*2*Paran*Loadcelltotal_value*L0_value; // Tu so
  tmp3=Length_value*ParaK2;                       // Mau so
  tmp1=Angle_value*PI/180;
  tmp1=cos(tmp1);
  tmp3=tmp3*tmp1;
  tmp1=tmp2/tmp3;              
  tmp2=tmp1+ParaK3;
  tmp2=tmp2/Length_value;
  return(tmp2);
  //WRITE_FLOAT_EXT_EEPROM(P0Parameter,tmp2);
  //Processed_Data.P0=READ_FLOAT_EXT_EEPROM(P0Parameter);
}

/*------------------------------------------------------
   Ham tinh toan m cho xe banh xich
   Description: 
------------------------------------------------------*/
float Calculatem()
{
   float tmp1,tmp2,tmp3,tmp4;
   L0_value=CalculateL0();
   tmp1=pow(Paraa,2);
   tmp2=pow(Parac,2);
   tmp3=pow(Parab,2);
   tmp4=tmp1+tmp2-tmp3;
   tmp1=2*Paraa*Parac;
   tmp2=tmp4/tmp1;
   tmp3=acos(tmp2);                   // arccos
   tmp1=Angle_value*PI/180;
   tmp2=Length_value*ParaK2-Parad;
   tmp2=Parag/tmp2;
   tmp2=atan(tmp2);
   tmp4=ParaE-tmp3-tmp1-tmp2;
   tmp4=cos(tmp4);
   tmp4=2*tmp4*Paraa*L0_value;
   tmp1=pow(Paraa,2);
   tmp2=pow(L0_value,2);
   tmp3=tmp2+tmp1-tmp4;
   tmp4=sqrt(tmp3);
   return tmp4;
}

/*------------------------------------------------------
   Ham tinh toan tai cho xe banh xich
   Description: 
------------------------------------------------------*/
float Crawler_CalculateP()
{
  float tmp1,tmp2,tmp3,m;
  m=Calculatem();
  tmp2=pow(m,2);                                      //mo^2
  tmp2=tmp2+pow(L0_value,2);                          //mo^2+Lo^2
  tmp2=tmp2-pow(Paraa,2);                             //mo^2+Lo^2-a^2  (1)
  tmp3=2*m*L0_value;                                  //2*m0*L       (2)
  tmp2=tmp2/tmp3;                                     //(1)/(2)      (12)
  tmp2=acos(tmp2);                                    //acos(12)     (3)
  tmp2=sin(tmp2);                                     // sin (3)
  tmp3=2*Paran*L0_value*Loadcelltotal_value;
  tmp2=tmp2*tmp3;
  tmp1=Angle_value*PI/180;
  tmp1=cos(tmp1);
  tmp3=P0_value*Length_value*Length_value*ParaK2*tmp1;
  tmp2=tmp2-tmp3;                                     // Tu so
  tmp3=2*Length_value*ParaK2*tmp1;                    // Mau so
  tmp2=tmp2/tmp3 + ParaK3;                            // Bieu thuc
  return tmp2;
}


void Calculate_Press_Loadcell()
{
  P_main_value=mapFloat(Loadcell1_raw, Loadcell1_raw_calib0, Loadcell1_raw_calib1, Loadcell1_value_calib0, Loadcell1_value_calib1);
  P_aux_value=mapFloat(Loadcell2_raw, Loadcell2_raw_calib0, Loadcell2_raw_calib1, Loadcell2_value_calib0, Loadcell2_value_calib1);
}


float Tinhtaibangloadcell_tructiep()
{
  float tmp1;
  if(Main_Aux==0)
  {
    tmp1=Cab_main_number*Loadcell1_value;
  }
  else
  {
    tmp1=Cab_aux_number*Loadcell2_value;
  }
  return tmp1;
}

void Calib0_Banhlop(void)
{
  if(flag_setLoad0_Whell==1)
  {
    T0_P_main=P_main_value;
    preferences.putFloat("T0_P_main",T0_P_main);
    T0_P_aux=P_aux_value;
    preferences.putFloat("T0_P_aux",T0_P_aux);
    T0_Length=Length_value;
    preferences.putFloat("T0_Length",T0_Length);
    T0_Angle=Angle_value;
    preferences.putFloat("T0_Angle",T0_Angle);
    T0_value=Wheel_CalculateT0();
    preferences.putFloat("T0_value",T0_value);
    // Serial.println(T0_value);
    node.writeSingleCoil(22,1);
    flag_setLoad0_Whell=0;
  }
}

void Calib0_Banhxich(void)
{
  if(flag_setLoad0_Crawler==1)
  {
    P0_Loadcell=Loadcelltotal_value;
    preferences.putFloat("P0_Loadcell",P0_Loadcell);
    P0_Length=Length_value;
    preferences.putFloat("P0_Length",P0_Length);
    P0_Angle=Angle_value;
    preferences.putFloat("P0_Angle",P0_Angle);
    P0_value=Crawler_CalculateP0();
    preferences.putFloat("P0_value",P0_value);
    P0_L0_value=L0_value;
    preferences.putFloat("P0_L0_value",P0_L0_value);
    node.writeSingleCoil(22,1);
    flag_setLoad0_Crawler=0;
  }
}

void Calibtaitungdoan5do()
{
		if((Angle_value<=5))
		{
			W_value=(W_value/(float)100)*Taiphantram_05;
		}
		else if((Angle_value>5)&&(Angle_value<=10))
		{
			W_value=(W_value/(float)100)*Taiphantram_10;
		}
		else if((Angle_value>10)&&(Angle_value<=15))
		{
			W_value=(W_value/(float)100)*Taiphantram_15;
		}
		else if((Angle_value>15)&&(Angle_value<=20))
		{
			W_value=(W_value/(float)100)*Taiphantram_20;
		}
		else if((Angle_value>20)&&(Angle_value<=25))
		{
			W_value=(W_value/(float)100)*Taiphantram_25;
		}
		else if((Angle_value>25)&&(Angle_value<=30))
		{
			W_value=(W_value/(float)100)*Taiphantram_30;
		}
		else if((Angle_value>30)&&(Angle_value<=35))
		{
			W_value=(W_value/(float)100)*Taiphantram_35;
		}
		else if((Angle_value>35)&&(Angle_value<=40))
		{
			W_value=(W_value/(float)100)*Taiphantram_40;
		}
		else if((Angle_value>40)&&(Angle_value<=45))
		{
			W_value=(W_value/(float)100)*Taiphantram_45;
		}
		else if((Angle_value>45)&&(Angle_value<=50))
		{
			W_value=(W_value/(float)100)*Taiphantram_50;
		}
		else if((Angle_value>50)&&(Angle_value<=55))
		{
			W_value=(W_value/(float)100)*Taiphantram_55;
		}
		else if((Angle_value>55)&&(Angle_value<=60))
		{
			W_value=(W_value/(float)100)*Taiphantram_60;
		}
		else if((Angle_value>60)&&(Angle_value<=65))
		{
			W_value=(W_value/(float)100)*Taiphantram_65;
		}
		else if((Angle_value>65)&&(Angle_value<=70))
		{
			W_value=(W_value/(float)100)*Taiphantram_70;
		}
		else if((Angle_value>70)&&(Angle_value<=75))
		{
			W_value=(W_value/(float)100)*Taiphantram_75;
		}
		else if((Angle_value>75)&&(Angle_value<=80))
		{
			W_value=(W_value/(float)100)*Taiphantram_80;
		}
		else if((Angle_value>80)&&(Angle_value<=85))
		{
			W_value=(W_value/(float)100)*Taiphantram_85;
		}
		else if((Angle_value>85)&&(Angle_value<=90))
		{
			W_value=(W_value/100)*Taiphantram_90;
		}
}

void Task_Caculate_code( void * pvParameters )
{
  for(;;)
  {
    switch(device_type)
    {
      case(1):
      {
        Calculate_Length();
        Calculate_Press();
        Calculate_Angle();
        Calculate_H_R();
        Calib0_Banhlop();
        W_value=Wheel_CalculateT();
        Calibtaitungdoan5do();
        Tinhtoantaimax_bangtai_phantramtai();
        if(MaxW_value==0)
        {
          Loadpercent=100;
        }
      }
      break;

      case(2):
      {
        // Calculate_Press();
        Calculate_Angle();
        Calculate_H_R();
        Calculate_Loadcell();
        Calib0_Banhxich();
        L0_value=CalculateL0();
        W_value=Crawler_CalculateP();
        Calibtaitungdoan5do();
        Tinhtoantaimax_bangtai_phantramtai();
        if(MaxW_value==0)
        {
          Loadpercent=100;
        }
      }
      break;
    
      case(3):
      {
        Calculate_Length();
        Calculate_Angle();
        Calculate_H_R();
        Calculate_Loadcell();
        W_value=Tinhtaibangloadcell_tructiep();
        Tinhtoantaimax_bangtai_phantramtai();
        if(MaxW_value==0)
        {
          Loadpercent=100;
        }
      }
      break;

      case(4):
      {
        Calculate_Angle();
        Calculate_H_R();
        Calculate_Loadcell();
        W_value=Tinhtaibangloadcell_tructiep();
        Tinhtoantaimax_bangtai_phantramtai();
        if(MaxW_value==0)
        {
          Loadpercent=100;
        }
      }
      break;

      case(5):
      {
        Calculate_Length();
        Calculate_Press_Loadcell();
        Calculate_Angle();
        Calculate_H_R();
        Calib0_Banhlop();
        W_value=Wheel_CalculateT();
        Calibtaitungdoan5do();
        Tinhtoantaimax_bangtai_phantramtai();
        if(MaxW_value==0)
        {
          Loadpercent=100;
        }
      }
      break;
      default:
      break;

      Loadpercent=W_value/MaxW_value;
    }
    // Serial.print("Task calculate running on: ");
    // Serial.println(xPortGetCoreID());
    vTaskDelay(400);
  }
}

void Tinhtoantaimax_bangtai_phantramtai()
{
if((Length_value <(LT[Socot-1]*0.01f)) && ((R_value <(LT[Socot*(Sohang-1)]*0.01f))))	
			{
				MaxW_value=CalculateMaxWe();
				
				if(Main_Aux==0) 
				{
					if((ParaCabW*Cab_main_number) < MaxW_value)     // Cap chinh qua tai
          {
						MaxW_value=ParaCabW*Cab_main_number;
					}
				} 
				else 
				{
					if((ParaCabW*Cab_aux_number) < MaxW_value)    
          {
						MaxW_value=ParaCabW*Cab_aux_number;
					}
				}
				
				if(W_value>0) 
				{
					Loadpercent=(uint16_t)(W_value/MaxW_value*100);
					// if(Loadpercent>100) 
					// {
					// 	Loadpercent=100;
					// }
				} 
				else 
				{
					Loadpercent=0;
				}
			}
			else 
			{
				MaxW_value=0.1;
				Loadpercent=100;
			}
}

float CalculateMaxWe()
{  
   int x1,x2,y1,y2;
   int temp1,temp2,temp4;
   int Radiusd,Lengthd;
   uint16_t i,PA1,PA2,PA3,PA4;
   uint8_t cpS;
   LT[0]=0;
   Radiusd=(int16_t)(((R_value))*100);
   Lengthd=(int16_t)(((Length_value))*100);
   cpS=0;
  //  Serial.print("So hang: "); Serial.print(Sohang); Serial.print(" - ");
  //  Serial.print("So cot: "); Serial.print(Socot); Serial.print(" - ");
  //  Serial.print("R: "); Serial.print(R_value,2);
  //  Serial.println();

   for(i=0;i<Socot;i++)
   {
    // Serial.print("Lengthd: "); Serial.print(Lengthd); Serial.print(" - ");
    // Serial.print("LT: "); Serial.print(LT[i]); Serial.println();
      if(Lengthd==(LT[i]))
      {
        x1=i;
        x2=i;
        break;
      }
      else
      if(Lengthd<(LT[1]))
      {
        x1=0;
        x2=1;
        // Serial.println("Dai can nho hon bang tai");
        cpS=2;
        return(0);
        break;
      }
      else
      if(((LT[i]) < Lengthd) && (Lengthd < (LT[i+1])))
      {
        x1=i;
        x2=i+1;
        break;
      }
      else
      if(Lengthd > (LT[Socot-1]))
      {
        x1=Socot-1;
			  x2=Socot;
        // Serial.println("Dai can lon hon bang tai");
        cpS=3;
        return(0);
			  break;
      }
   }
   
   for(i=0;i<=Sohang;i++)
   {  
      // Serial.print("Radiusd: "); Serial.print(Radiusd); Serial.print(" - ");
      // Serial.print("LT: "); Serial.print(LT[i*Socot]); Serial.println();
      if(Radiusd == (LT[i*Socot]))
      {
        y1=i;
        y2=i;
        break;
      }
      else
      if(Radiusd < (LT[1*Socot]) )
      {
        y1=0;
        y2=1;
        // Serial.println("Tam voi nho hon bang tai");
        cpS=4;
        return(0);
        break;
      }
      else
      if(((LT[i*Socot]) < Radiusd) && (Radiusd < (LT[(i+1)*Socot])))
      {
        y1=i;
        y2=i+1;
        break;
      }
      else
      if(Radiusd > ((LT[(Sohang-1)*Socot])) )
      {
        y1=Sohang-1;
				y2=Sohang;
        // Serial.println("Tam voi lon hon bang tai");
        cpS=5;
        return(0);
				break;
      }
   }

  // Serial.print("x1:"); Serial.print(x1); Serial.print(" - ");
  // Serial.print("x2:"); Serial.print(x2); Serial.print(" - ");
  // Serial.print("y1:"); Serial.print(y1); Serial.print(" - ");
  // Serial.print("y2:"); Serial.println(y2);
  // Serial.println("---------------------------------------");
  PA1=(y1*Socot+x1);
  PA2=(y1*Socot+x2);
  PA3=(y2*Socot+x1);
  PA4=(y2*Socot+x2);
  // Serial.print("LT"); Serial.print(PA1); Serial.print(": "); Serial.print(LT[PA1]); Serial.print(" - ");
  // Serial.print("LT"); Serial.print(PA2); Serial.print(": "); Serial.print(LT[PA2]); Serial.print(" - ");
  // Serial.print("LT"); Serial.print(PA3); Serial.print(": "); Serial.print(LT[PA3]); Serial.print(" - ");
  // Serial.print("LT"); Serial.print(PA4); Serial.print(": "); Serial.println(LT[PA4]);
  if((x1==x2) && (y1==y2))
  {
    // Serial.println("Trung ca hang va cot");
    temp4=LT[PA1];
  }
  else if(x1==x2)
  {
    // Serial.println("Trung cot");
    temp4=mapFloat(Radiusd, (LT[Socot*y1]), (LT[Socot*y2]), (LT[PA1]), (LT[PA3]));

    // Serial.print("Tam voi 1: "); Serial.println(LT[Socot*y1]);
    // Serial.print("Tam voi 2: "); Serial.println(LT[Socot*y2]);
    // Serial.print("PA1: "); Serial.println(LT[PA1]);
    // Serial.print("PA3: "); Serial.println(LT[PA3]);
  }
  else if (y1==y2)
  {
    // Serial.println("Trung hang");
    temp4=mapFloat(Lengthd, (LT[x1]), (LT[x2]), (LT[PA1]), (LT[PA2]));
    // Serial.print("PA1: "); Serial.println(LT[PA1]);
    // Serial.print("PA2: "); Serial.println(LT[PA2]);
  }
  else
  {
    // Serial.println("Xu ly binh thuong");
    temp1=mapFloat(Radiusd, (LT[Socot*y1]), (LT[Socot*y2]), (LT[PA1]), (LT[PA3]));
    temp2=mapFloat(Radiusd, (LT[Socot*y1]), (LT[Socot*y2]), (LT[PA2]), (LT[PA4]));
    temp4=mapFloat(Lengthd, (LT[x1]), (LT[x2]), temp1, temp2);
    // Serial.print("PA1: "); Serial.println(LT[PA1]);
    // Serial.print("PA2: "); Serial.println(LT[PA2]);
    // Serial.print("PA3: "); Serial.println(LT[PA3]);
    // Serial.print("PA4: "); Serial.println(LT[PA4]);
  }
  // Serial.print("KQ: "); Serial.println(temp4);
  return (temp4*0.01);
}