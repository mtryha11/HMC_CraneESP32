#include <Arduino.h>
#include <TaskLoadTB.h>
#include <Preferences.h>
#include <ModbusRTU.h>

Preferences preferences;

#define SLAVE_ID 1
ModbusRTU Napbangtai;

uint8_t pos=0;
float val=1.2;
bool ADS_Type;

void Task_LoadTB_code( void * pvParameters )
{
  preferences.begin("HMC", false);
  //preferences.begin("HMC1", false);
  device_type=            preferences.getUChar("DT",1);
  if(device_type>5)
  {
    device_type=1;
  }

  preferences.putBool("ADS_Type",1);
  vTaskDelay(100);
  ADS_Type=  preferences.getBool("ADS_Type",0);

  Multi_Loadtable_State=  preferences.getBool("LTB_state",0);
  Angle_value_calib0=     preferences.getFloat("A1",0);
  Angle_raw_calib0=       preferences.getShort("A3",0);
  Angle_value_calib1=     preferences.getFloat("A2",0);
  Angle_raw_calib1=       preferences.getShort("A4",0);
  Angle_alarm_min=        preferences.getShort("A5",0);
  Angle_alarm_set=        preferences.getShort("A6",0);
  Angle_alarm_max=        preferences.getShort("A7",0);
  
  Length_value_calib0=    preferences.getFloat("L1",0);
  Length_raw_calib0=      preferences.getShort("L3",0);
  Length_value_calib1=    preferences.getFloat("L2",0);
  Length_raw_calib1=      preferences.getShort("L4",0);  
  Length_alarm_min=       preferences.getFloat("L5",0);
  Length_alarm_set=       preferences.getFloat("L6",0);
  Length_alarm_max=       preferences.getFloat("L7",0);

  Load_alarm_set=         preferences.getShort("LoadS",0);
  Load_alarm_max=         preferences.getShort("LoadM",0);

  T0_P_main=              preferences.getFloat("T0_P_main",0);
  T0_P_aux=               preferences.getFloat("T0_P_aux",0);
  T0_Length=              preferences.getFloat("T0_Length",0);
  T0_Angle=               preferences.getFloat("T0_Angle",0);
  T0_value=               preferences.getFloat("T0_value",0);

  P0_Loadcell=            preferences.getFloat("P0_Loadcell",0);
  P0_Length=              preferences.getFloat("P0_Length",0);
  P0_Angle=               preferences.getFloat("P0_Angle",0);
  P0_value=               preferences.getFloat("P0_value",0);
  P0_L0_value=            preferences.getFloat("P0_L0_value",0);

  Cab_main_number=        preferences.getShort("Cab_main_num",0);
  Cab_aux_number=         preferences.getShort("Cab_aux_num",0);

  Main_Aux=               preferences.getBool("Main_Aux",0);
  P1_range=               preferences.getShort("P1",0);
  P2_range=               preferences.getShort("P2",0);                  
  P3_range=               preferences.getShort("P3",0);                  
  P4_range=               preferences.getShort("P4",0);                  
  P5_range=               preferences.getShort("P5",0);                  
  P_main_select=          preferences.getShort("P6",0);   
  P_aux_select=           preferences.getShort("P7",0);
  Parar=                  preferences.getFloat("Parar",0);
  Parah=                  preferences.getFloat("Parah",0);
  ParaCabW=               preferences.getFloat("ParaCabW",0);
  Paraa=                  preferences.getFloat("Paraa",0);
  Parab=                  preferences.getFloat("Parab",0);
  Parac=                  preferences.getFloat("Parac",0);
  Parad=                  preferences.getFloat("Parad",0);
  ParaE=                  preferences.getFloat("ParaE",0);
  Parag=                  preferences.getFloat("Parag",0);
  Paran=                  preferences.getFloat("Paran",0);
  ParaK1=                 preferences.getFloat("ParaK1",0);
  ParaK2=                 preferences.getFloat("ParaK2",0);
  ParaK3=                 preferences.getFloat("ParaK3",0);
  ParaK4=                 preferences.getFloat("ParaK4",0);
  Sohang=                 preferences.getUInt("Sohang",0);
  Socot=                  preferences.getUInt("Socot",0);
  Stt=                    preferences.getUInt("Bangso",0);
  Length_xich_nhap=       preferences.getFloat("L_xich",0);

  Taiphantram_05=         preferences.getUInt("Taiphantram_05",100);
  Taiphantram_10=         preferences.getUInt("Taiphantram_10",100);
  Taiphantram_15=         preferences.getUInt("Taiphantram_15",100);
  Taiphantram_20=         preferences.getUInt("Taiphantram_20",100);
  Taiphantram_25=         preferences.getUInt("Taiphantram_25",100);
  Taiphantram_30=         preferences.getUInt("Taiphantram_30",100);
  Taiphantram_35=         preferences.getUInt("Taiphantram_35",100);
  Taiphantram_40=         preferences.getUInt("Taiphantram_40",100);
  Taiphantram_45=         preferences.getUInt("Taiphantram_45",100);
  Taiphantram_50=         preferences.getUInt("Taiphantram_50",100);
  Taiphantram_55=         preferences.getUInt("Taiphantram_55",100);
  Taiphantram_60=         preferences.getUInt("Taiphantram_60",100);
  Taiphantram_65=         preferences.getUInt("Taiphantram_65",100);
  Taiphantram_70=         preferences.getUInt("Taiphantram_70",100);
  Taiphantram_75=         preferences.getUInt("Taiphantram_75",100);
  Taiphantram_80=         preferences.getUInt("Taiphantram_80",100);
  Taiphantram_85=         preferences.getUInt("Taiphantram_85",100);
  Taiphantram_90=         preferences.getUInt("Taiphantram_90",100);

  Length_value=Length_xich_nhap;
  if(Multi_Loadtable_State==1)
  {
    Load_table_value=0;
  }
  else
  {
    Load_table_value=       preferences.getFloat("LT_value",0);
  }
  Loadcell1_value_calib0= preferences.getFloat("Load1",0);  // Load1
  Loadcell1_value_calib1= preferences.getFloat("Load2",0);  // Load2
  Loadcell2_value_calib0= preferences.getFloat("Load3",0);  // Load3
  Loadcell2_value_calib1= preferences.getFloat("Load4",0);  // Load4
  Loadcell1_raw_calib0  = preferences.getUInt ("Load5",0);  // Load5
  Loadcell1_raw_calib1  = preferences.getUInt ("Load6",0);  // Load6
  Loadcell2_raw_calib0  = preferences.getUInt ("Load7",0);  // Load7
  Loadcell2_raw_calib1  = preferences.getUInt ("Load8",0);  // Load8

               
  preferences.getBytes("Doitrong",Doitrong,(20));
  
  Trigger_LT=1;

  Serial.begin(115200, SERIAL_8N1);
  Serial.print("Taiphantram_05: ");Serial.println(Taiphantram_05);
  Serial.print("Taiphantram_10: ");Serial.println(Taiphantram_10);
  Serial.print("Taiphantram_15: ");Serial.println(Taiphantram_15);
  Serial.print("Taiphantram_20: ");Serial.println(Taiphantram_20);
  Serial.print("NVS "); Serial.println(preferences.freeEntries());
  Serial.print("So hang: ");Serial.println(Sohang);
  Serial.print("So cot: ");Serial.println(Socot);
  Serial.print("Doi trong dang seting: ");Serial.println(Load_table_value);
  for (uint8_t u=0;u<10;u++)
  {
    Serial.print("Doitrong "); Serial.print(u); Serial.print(": "); Serial.println((Doitrong[u]/(float)100),1);
  }

  Napbangtai.begin(&Serial);
  Napbangtai.slave(SLAVE_ID);

  for(uint8_t i=0;i<4;i++)
  {
  Napbangtai.addHreg(i);
  Napbangtai.Hreg(i, 0);
  }

  for(uint16_t i=0;i<800;i++)
  {
    Napbangtai.addHreg(100+i);
    Napbangtai.Hreg(100+i, 0);
  }
  for(;;)
  {
    Napbangtai.task();

    if(Napbangtai.Hreg(0)!=0)
    {
      Stt=      Napbangtai.Hreg(0);
      Sohang=   Napbangtai.Hreg(1);
      Socot=    Napbangtai.Hreg(2);
      preferences.putUInt("Sohang",Sohang);
      preferences.putUInt("Socot",Socot);
      preferences.putUInt("Bangso",Stt);
      
       for(uint16_t a=0;a<Sohang;a++)
      {
        for(uint16_t b=0;b<Socot;b++)
        {
          LT[(a*Socot+b)]=Napbangtai.Hreg(100+ (a*Socot+b));
        }
      }
      switch(Stt)
      {
        case (1): 
        {
          Doitrong[0]= Napbangtai.Hreg(3);
          preferences.putBytes("Bangtai_1",LT,(2*Sohang*Socot));
        }
        break;
        case (2): 
        {
          Doitrong[1]= Napbangtai.Hreg(3);
          preferences.putBytes("Bangtai_2",LT,(2*Sohang*Socot));
        }
        break;
        case (3): 
        {
          Doitrong[2]= Napbangtai.Hreg(3);
          preferences.putBytes("Bangtai_3",LT,(2*Sohang*Socot));
        }
        break;
        case (4): 
        {
          Doitrong[3]= Napbangtai.Hreg(3);
          preferences.putBytes("Bangtai_4",LT,(2*Sohang*Socot));
        }
        break;
        case (5): 
        {
          Doitrong[4]= Napbangtai.Hreg(3);
          preferences.putBytes("Bangtai_5",LT,(2*Sohang*Socot));
        }
        break;
        case (6): 
        {
          Doitrong[5]= Napbangtai.Hreg(3);
          preferences.putBytes("Bangtai_6",LT,(2*Sohang*Socot));
        }
        break;
        case (7): 
        {
          Doitrong[6]= Napbangtai.Hreg(3);
          preferences.putBytes("Bangtai_7",LT,(2*Sohang*Socot));
        }
        break;
        case (8): 
        {
          Doitrong[7]= Napbangtai.Hreg(3);
          preferences.putBytes("Bangtai_8",LT,(2*Sohang*Socot));
        }
        break;
        case (9): 
        {
          Doitrong[8]= Napbangtai.Hreg(3);
          preferences.putBytes("Bangtai_9",LT,(2*Sohang*Socot));
        }
        break;
        case (10): 
        {
          Doitrong[9]= Napbangtai.Hreg(3);
          preferences.putBytes("Bangtai_10",LT,(2*Sohang*Socot));
        }
        break;
      }
      preferences.putBytes("Doitrong",Doitrong,20);
      Napbangtai.Hreg(0, 0);
    }

    if(Trigger_LT==1)
    {
      uint16_t temp;
      temp=Load_table_value*100;
      if(temp==Doitrong[0]) // 
      {
        preferences.getBytes("Bangtai_1",LT,(2*Sohang*Socot));
        Serial.println("Load Bang 1 - Mac dinh");
        Stt=1;
      }
      else if(temp==Doitrong[1])
      {
        preferences.getBytes("Bangtai_2",LT,(2*Sohang*Socot));
        Serial.println("Load Bang 2");
        Stt=2;
      }
      else if(temp==Doitrong[2])
      {
        preferences.getBytes("Bangtai_3",LT,(2*Sohang*Socot));
        Serial.println("Load Bang 3");
        Stt=3;
      }
      else if(temp==Doitrong[3])
      {
        preferences.getBytes("Bangtai_4",LT,(2*Sohang*Socot));
        Serial.println("Load Bang 4");
        Stt=4;
      }
      else if(temp==Doitrong[4])
      {
        preferences.getBytes("Bangtai_5",LT,(2*Sohang*Socot));
        Serial.println("Load Bang 5");
        Stt=5;
      }
      else if(temp==Doitrong[5])
      {
        preferences.getBytes("Bangtai_6",LT,(2*Sohang*Socot));
        Serial.println("Load Bang 6");
        Stt=6;
      }
      else if(temp==Doitrong[6])
      {
        preferences.getBytes("Bangtai_7",LT,(2*Sohang*Socot));
        Serial.println("Load Bang 7");
        Stt=7;
      }
      else if(temp==Doitrong[7])
      {
        preferences.getBytes("Bangtai_8",LT,(2*Sohang*Socot));
        Serial.println("Load Bang 8");
        Stt=8;
      }
      else if(temp==Doitrong[8])
      {
        preferences.getBytes("Bangtai_9",LT,(2*Sohang*Socot));
        Serial.println("Load Bang 9");
        Stt=9;
      }
      else if(temp==Doitrong[9])
      {
        preferences.getBytes("Bangtai_10",LT,(2*Sohang*Socot));
        Serial.println("Load Bang 10");
        Stt=10;
      }

      
      for(uint8_t i=0;i<Sohang;i++) // Show bang tai
      {
        for(uint8_t j=0;j<Socot;j++)
        {
          Serial.print(LT[(i*Socot)+j]); Serial.print("\t");
        }
        Serial.println();
      }
      Serial.println("-------------------------------------------------");
      Trigger_LT=0;
    }
    vTaskDelay(100);
  }
}