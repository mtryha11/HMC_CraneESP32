#include <Arduino.h>
#include <TaskHMI.h>
#include <ModbusMaster.h>
#include <Preferences.h>

ModbusMaster node;
extern Preferences preferences;

uint8_t Page_status=0;
bool Trigger_Page=0;
uint8_t result,j;

bool Trigger_Setting_Angle=0;
bool Trigger_Setting_Angle_calib0=0;
bool Trigger_Setting_Angle_calib1=0;

bool Trigger_Setting_Length=0;
bool Trigger_Setting_Length_calib0=0;
bool Trigger_Setting_Length_calib1=0;

bool Trigger_Setting_Press=0;
bool Trigger_Setting_Device=0;
bool Trigger_Setting_Other=0;
bool Trigger_Setting_Other1=0;
bool Trigger_Cab_Input=0;
bool Trigger_Main_Aux=0;
bool Trigger_Loadtable=0;
bool Trigger_Length_nhapmanhinh=0;
bool Set_load_0=0;
bool Trigger_Setting_Load=0;

bool Trigger_Setting_Loadcell1_calib0=0;
bool Trigger_Setting_Loadcell1_calib1=0;
bool Trigger_Setting_Loadcell2_calib0=0;
bool Trigger_Setting_Loadcell2_calib1=0;
bool Trigger_Setting_Loadcell=0;
bool Trigger_Customer=0;

float bytesToFloat(uint16_t *bytes) 
{
    float f;
    uint16_t *f_ptr = (uint16_t *) &f;
        f_ptr[1] = bytes[1];
        f_ptr[0] = bytes[0];
    return f;
}


void Float_to_Register(float variable, uint8_t register0, uint8_t register1)
{
    uint16_t temp[2] 
    {
        ((uint16_t*)&variable)[0],
        ((uint16_t*)&variable)[1]
    };
    node.setTransmitBuffer(register0-1, temp[0]);
    node.setTransmitBuffer(register1-1, temp[1]);
}

void Word_to_Register(uint16_t variable,uint8_t register2)
{
    node.setTransmitBuffer(register2-1, variable);
}


///////////////////// RS485 ///////////////////
void preTransmission()
{
  digitalWrite(DE_pin, 1);
//   digitalWrite(Led1, !digitalRead(Led1));
}

void postTransmission()
{
  digitalWrite(DE_pin, 0);
  digitalWrite(Led1, !digitalRead(Led1));
}
///////////////////// RS485 ///////////////////

uint16_t page_old;
void Task_HMI_code( void * pvParameters )
{
    //// Khoi tao cho RS485 ////
  pinMode(DE_pin, OUTPUT);
  digitalWrite(DE_pin, LOW); // Trang thai nhan
  SerialRS485.begin(115200);
  node.begin(2, SerialRS485);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
    //// Khoi tao cho RS485 ////

  for(;;)
  {
    if (node.readHoldingRegisters(Screen_no_status_addr, 1) == node.ku8MBSuccess)
    {
        page_old=node.getResponseBuffer(0);
        if(page_old != Page_status)
        {
            Page_status=page_old;
            // Trigger_Page=1;
            node.writeSingleCoil(Trigger_Page_addr,1);
            Serial.println("Chuyen trang");
        }
        
        node.clearResponseBuffer();
        result_comunication_HMI=1;
    }
    if(node.readCoils(Trigger_Page_addr,1) == node.ku8MBSuccess)
    {
        Trigger_Page=node.getResponseBuffer(0);
        node.clearResponseBuffer();
    }

    switch(Page_status)
    {
        case 1: // Dang o trang Logo
        {
            node.writeSingleCoil(Multi_Loadtable_State_addr,Multi_Loadtable_State);
            node.writeSingleRegister(Device_addr,device_type);

            if((device_type==2) ||(device_type==4))
            {
                node.writeSingleCoil(33,1);
            }
            else
            {
                node.writeSingleCoil(33,0);
            }

            if((device_type==1) ||(device_type==3))
            {
                node.writeSingleCoil(63,1);
            }
            else
            {
                node.writeSingleCoil(63,0);
            }


            Word_to_Register(Load_alarm_set,1);
            Word_to_Register(Load_alarm_max,2);
            result = node.writeMultipleRegisters(Load_alarm_set_addr, 2); // Gui bien len man hinh 1 lan dau load trang
            node.clearTransmitBuffer();
            Float_to_Register(Load_table_value,1,2);
            node.writeMultipleRegisters(Load_table_value_addr,2);   // Gui bien len man hinh
            node.clearTransmitBuffer();
            switch(device_type)
            {
                case(0):
                case(1):    // Chuyen trang Home banh Lop
                case(3):
                case(5):
                {
                    Trigger_Main_Aux=1;
                    node.writeSingleCoil(20,1); // Clear Trigger_Main_Aux
                    result = node.writeSingleRegister(Screen_no_control_addr,0x02);
                    // Serial.println("Chuyen trang banh lop");
                }
                break;

                case(2):    // Chuyen trang Home banh Xich
                case(4):
                {   
                    Trigger_Main_Aux=1;
                    node.writeSingleCoil(20,1); // Clear Trigger_Main_Aux
                    result = node.writeSingleRegister(Screen_no_control_addr,0x03);
                    // Serial.println("Chuyen trang banh xich");
                }
                break;
                case(6):
                {   
                    Trigger_Main_Aux=1;
                    node.writeSingleCoil(20,1); // Clear Trigger_Main_Aux
                    result = node.writeSingleRegister(Screen_no_control_addr,20);
                    // Serial.println("Chuyen trang banh xich");
                }
                break;

                case(7):
                {   
                    Trigger_Main_Aux=1;
                    node.writeSingleCoil(20,1); // Clear Trigger_Main_Aux
                    result = node.writeSingleRegister(Screen_no_control_addr,22);
                    // Serial.println("Chuyen trang banh xich");
                }
                break;
            }
        }
        break;

        case 2: // Dang o trang Banh lop
        {
            if(node.readCoils(19,3) == node.ku8MBSuccess)  // Read Trigger_Cab_Input
            {
                Trigger_Loadtable=node.getResponseBuffer(0) & bit(0);
                Trigger_Main_Aux=node.getResponseBuffer(0) & bit(1);
                Trigger_Cab_Input=node.getResponseBuffer(0) & bit(2);
                node.clearResponseBuffer();
            }

            if(DigitalInput_1==1)               // Hien thi ngat cap len man hinh
            {
                node.writeSingleCoil(31,0);
            }
            else
            {
                node.writeSingleCoil(31,1);
            }

            if(Trigger_Main_Aux==1)
            {
                if(node.readCoils(35, 1) == node.ku8MBSuccess)
                {
                    Main_Aux=node.getResponseBuffer(0);
                    node.clearResponseBuffer();
                    preferences.putBool("Main_Aux",Main_Aux);
                }
                node.writeSingleCoil(20,0); // Clear Trigger_Main_Aux
                // Serial.print("Vua chon cap: "); Serial.println(Main_Aux);        /// 1 La cap phu, 0 la cap chinh
            }

            if(Trigger_Cab_Input==1)
            {
                node.readHoldingRegisters(Cab_number_addr, 1);
                if(Main_Aux==1)
                {
                    Cab_aux_number=node.getResponseBuffer(0);
                    preferences.putShort("Cab_aux_num",Cab_aux_number);
                    // Serial.print("So soi cap phu vua nhap: "); Serial.println(Cab_aux_number);
                }
                else
                {
                    Cab_main_number=node.getResponseBuffer(0);
                    preferences.putShort("Cab_main_num",Cab_main_number);
                    // Serial.print("So soi cap chinh vua nhap: "); Serial.println(Cab_main_number);                    
                }
                node.clearResponseBuffer();
                node.writeSingleCoil(21,0); // Clear Trigger_Cab_Input
            }

            if(Trigger_Loadtable==1)
            {
                uint16_t temp[2];
                node.readHoldingRegisters(Load_table_value_addr, 2);
                temp[0]=node.getResponseBuffer(0);
                temp[1]=node.getResponseBuffer(1);
                node.clearResponseBuffer();
                Load_table_value=bytesToFloat(&temp[0]);

                preferences.putFloat("LT_value",Load_table_value);
                node.clearResponseBuffer();
                Trigger_LT=1;
                node.writeSingleCoil(19,0); // Clear Trigger_Loadtable
            }

            if(Main_Aux==1)
                Cab_number = Cab_aux_number;
            else
                Cab_number = Cab_main_number;

            Float_to_Register(Angle_value,1,2);
            Float_to_Register(Length_value,3,4);
            if(W_value<0)
            {
                Float_to_Register(0-W_value,5,6);
            }
            else
            {
                Float_to_Register(W_value,5,6);
            }
            Float_to_Register(MaxW_value,7,8);
            Word_to_Register(Cab_number,9);
            //Word_to_Register(Load_stt,10);
            Float_to_Register(R_value,11,12);
            Float_to_Register(H_value,13,14);
            Word_to_Register(Loadpercent,15);
            result = node.writeMultipleRegisters(Angle_value_addr, 15);   // Gui bien len man hinh
            node.clearTransmitBuffer();

            uint8_t temp1;
            temp1=((!Stt_LoadSet)<<1) | (!Stt_LoadHi);
            node.setTransmitBuffer(0, temp1);
            result = node.writeMultipleCoils(56, 2);
            node.clearTransmitBuffer();

            uint8_t temp;
            temp=((!Stt_AngleHi)<<6) | ((!Stt_AngleSet)<<5) | ((!Stt_LengthHi)<<3) | ((!Stt_LengthLow)<<2) | ((!Stt_LoadHi)<<1) | (!Stt_LoadSet);
            node.setTransmitBuffer(0, temp);
            result = node.writeMultipleCoils(11, 7);
            node.clearTransmitBuffer();

        }
        break;

        case 3: // Dang o trang Banh xich
        {
            if(node.readCoils(18,4) == node.ku8MBSuccess)  // Read Trigger_Cab_Input
            {
                Trigger_Length_nhapmanhinh=node.getResponseBuffer(0) & bit(0);
                Trigger_Loadtable=node.getResponseBuffer(0) & bit(1);
                Trigger_Main_Aux=node.getResponseBuffer(0) & bit(2);
                Trigger_Cab_Input=node.getResponseBuffer(0) & bit(3);
                node.clearResponseBuffer();
            }

            if(DigitalInput_1==1)               // Hien thi ngat cap len man hinh
            {
                node.writeSingleCoil(31,0);
            }
            else
            {
                node.writeSingleCoil(31,1);
            }

            if(Trigger_Length_nhapmanhinh==1)
            {   uint16_t temp[2];
                node.readHoldingRegisters(Length_banhxich_addr, 2);
                temp[0]=node.getResponseBuffer(0);
                temp[1]=node.getResponseBuffer(1);
                node.clearResponseBuffer();
                Length_xich_nhap=bytesToFloat(&temp[0]);
                preferences.putFloat("L_xich",Length_xich_nhap);
                Length_value=Length_xich_nhap;
                Serial.print("Gia tri vua nhap: ");Serial.println(Length_value);
                node.writeSingleCoil(18,0); // Clear Trigger_Loadtable
            }
            if(Trigger_Main_Aux==1)
            {
                node.readCoils(35, 1);
                Main_Aux=node.getResponseBuffer(0);
                node.clearResponseBuffer();
                preferences.putBool("Main_Aux",Main_Aux);
                node.writeSingleCoil(20,0); // Clear Trigger_Main_Aux
                // Serial.print("Vua chon cap: "); Serial.println(Main_Aux);        /// 1 La cap phu, 0 la cap chinh
            }

            if(Trigger_Cab_Input==1)
            {
                node.readHoldingRegisters(Cab_number_addr, 1);
                if(Main_Aux==1)
                {
                    Cab_aux_number=node.getResponseBuffer(0);
                    preferences.putShort("Cab_aux_num",Cab_aux_number);
                    // Serial.print("So soi cap phu vua nhap: "); Serial.println(Cab_aux_number);
                }
                else
                {
                    Cab_main_number=node.getResponseBuffer(0);
                    preferences.putShort("Cab_main_num",Cab_main_number);
                    // Serial.print("So soi cap chinh vua nhap: "); Serial.println(Cab_main_number);                    
                }
                node.clearResponseBuffer();
                node.writeSingleCoil(21,0); // Clear Trigger_Cab_Input
            }

            if(Trigger_Loadtable==1)
            {   uint16_t temp[2];
                node.readHoldingRegisters(Load_table_value_addr, 2);
                temp[0]=node.getResponseBuffer(0);
                temp[1]=node.getResponseBuffer(1);
                node.clearResponseBuffer();
                Load_table_value=bytesToFloat(&temp[0]);

                preferences.putFloat("LT_value",Load_table_value);
                node.clearResponseBuffer();
                Trigger_LT=1;
                node.writeSingleCoil(19,0); // Clear Trigger_Loadtable
            }

            if(Main_Aux==1)
                Cab_number = Cab_aux_number;
            else
                Cab_number = Cab_main_number;

            Float_to_Register(Angle_value,1,2);
            Float_to_Register(Length_value,3,4);

            if(W_value<0)
            {
                Float_to_Register(0-W_value,5,6);
            }
            else
            {
                Float_to_Register(W_value,5,6);
            }

            Float_to_Register(MaxW_value,7,8);
            Word_to_Register(Cab_number,9);
            Float_to_Register(R_value,11,12);
            Float_to_Register(H_value,13,14);
            Word_to_Register(Loadpercent,15);
            result = node.writeMultipleRegisters(Angle_value_addr, 15);   // Gui bien len man hinh
            node.clearTransmitBuffer();

            uint8_t temp1;
            temp1=((!Stt_LoadSet)<<1) | (!Stt_LoadHi);
            node.setTransmitBuffer(0, temp1);
            result = node.writeMultipleCoils(56, 2);
            node.clearTransmitBuffer();

            uint8_t temp;
            temp=((!Stt_AngleHi)<<6) | ((!Stt_AngleSet)<<5) | ((!Stt_LengthHi)<<3) | ((!Stt_LengthLow)<<2) | ((!Stt_LoadHi)<<1) | (!Stt_LoadSet);
            node.setTransmitBuffer(0, temp);
            result = node.writeMultipleCoils(11, 7);
            node.clearTransmitBuffer();

        }
        break;

        case 4: // Dang o trang Dang nhap
        {

        }
        break;

        case 5: // Dang o trang Cai dat Admin
        {
            Trigger_Customer=0;
            node.writeSingleCoil(64,0); // Trigger Customer
        }
        break;

        case 6: // Dang o trang Cai dat Angle
        {   
            if(Trigger_Page==1)
            {
                Float_to_Register(Angle_value_calib0,1,2);
                Float_to_Register(Angle_value_calib1,3,4);
                result = node.writeMultipleRegisters(Angle_value_calib0_addr, 4);   // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                Word_to_Register(Angle_alarm_min,1);
                Word_to_Register(Angle_alarm_set,2);
                Word_to_Register(Angle_alarm_max,3);
                result = node.writeMultipleRegisters(Angle_alarm_min_addr, 3);   // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                Word_to_Register(Angle_raw_calib0,1);
                Word_to_Register(Angle_raw_calib1,2);
                result = node.writeMultipleRegisters(Angle_raw_calib0_addr, 2);   // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }
            if(node.readCoils(52,2) == node.ku8MBSuccess)
            {
                Trigger_Setting_Angle_calib0=node.getResponseBuffer(0) & bit(0);
                Trigger_Setting_Angle_calib1=node.getResponseBuffer(0) & bit(1);
                node.clearResponseBuffer();
            }

            if(node.readCoils(24,1) == node.ku8MBSuccess)
            {
                Trigger_Setting_Angle=node.getResponseBuffer(0);
                node.clearResponseBuffer();
            }

            if(Trigger_Setting_Angle_calib0==1)         // Cài đặt Calib 0
            {
                uint16_t temp[2];
                if (node.readHoldingRegisters(Angle_value_calib0_addr, 2) == node.ku8MBSuccess)
                {
                    temp[0]=node.getResponseBuffer(0);
                    temp[1]=node.getResponseBuffer(1);
                    node.clearResponseBuffer();
                    Angle_value_calib0=bytesToFloat(&temp[0]);
                    Angle_raw_calib0=Angle_raw;

                    preferences.putFloat("A1",Angle_value_calib0);
                    preferences.putShort("A3",Angle_raw_calib0);

                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(52,0);      // Clear Trigger_Setting_Angle
                    //Serial.print("Angle_value_calib0 "); Serial.println(Angle_value_calib0,2);
            }

            if(Trigger_Setting_Angle_calib1==1)     // Cài đặt Calib 1
            {
                uint16_t temp[2];
                if (node.readHoldingRegisters(Angle_value_calib1_addr, 2) == node.ku8MBSuccess)
                {
                    temp[0]=node.getResponseBuffer(0);
                    temp[1]=node.getResponseBuffer(1);
                    node.clearResponseBuffer();
                    Angle_value_calib1=bytesToFloat(&temp[0]);
                    Angle_raw_calib1=Angle_raw;
                    preferences.putFloat("A2",Angle_value_calib1);
                    preferences.putShort("A4",Angle_raw_calib1);
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(53,0);      // Clear Trigger_Setting_Angle
                    //Serial.print("Angle_value_calib1 "); Serial.println(Angle_value_calib1,2);
            }

            if(Trigger_Setting_Angle==1)     // Cài đặt Alarm Angle
            {
                if (node.readHoldingRegisters(Angle_alarm_min_addr, 3) == node.ku8MBSuccess)
                {
                    Angle_alarm_min=node.getResponseBuffer(0);
                    Angle_alarm_set=node.getResponseBuffer(1);
                    Angle_alarm_max=node.getResponseBuffer(2);
                    node.clearResponseBuffer();

                    preferences.putShort("A5",Angle_alarm_min);
                    preferences.putShort("A6",Angle_alarm_set);
                    preferences.putShort("A7",Angle_alarm_max);

                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(24,0);      // Clear Trigger_Setting_Angle
                    //Serial.print("Angle_alarm_min "); Serial.println(Angle_alarm_min);
                    //Serial.print("Angle_alarm_set "); Serial.println(Angle_alarm_set);
                    //Serial.print("Angle_alarm_max "); Serial.println(Angle_alarm_max);
            }

            result = node.writeSingleRegister(Angle_raw_addr,Angle_raw); // Gui bien len man hinh lien tuc
            Float_to_Register(Angle_value,1,2);
            result = node.writeMultipleRegisters(Angle_value_addr, 2); // Gui bien len man hinh lien tuc
            node.clearTransmitBuffer();
        }
        break;

        case 7: // Dang o trang Cai dat Length
        {   
            if(Trigger_Page==1)
            {
                Float_to_Register(Length_value_calib0,1,2);
                Float_to_Register(Length_value_calib1,3,4);
                result = node.writeMultipleRegisters(Length_value_calib0_addr, 4);   // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                Float_to_Register(Length_alarm_min,1,2);
                Float_to_Register(Length_alarm_set,3,4);
                Float_to_Register(Length_alarm_max,5,6);
                result = node.writeMultipleRegisters(Length_alarm_min_addr, 6);   // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                Word_to_Register(Length_raw_calib0,1);
                Word_to_Register(Length_raw_calib1,2);
                result = node.writeMultipleRegisters(Length_raw_calib0_addr, 2);   // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }

            if(node.readCoils(54,2) == node.ku8MBSuccess)
            {
                Trigger_Setting_Length_calib0=node.getResponseBuffer(0) & bit(0);
                Trigger_Setting_Length_calib1=node.getResponseBuffer(0) & bit(1);
                node.clearResponseBuffer();
            }

            if(node.readCoils(25,1) == node.ku8MBSuccess)
            {
                Trigger_Setting_Length=node.getResponseBuffer(0);
                node.clearResponseBuffer();
            }

            if(Trigger_Setting_Length_calib0==1)
            {
                uint16_t temp[2];
                if (node.readHoldingRegisters(Length_value_calib0_addr, 2) == node.ku8MBSuccess)
                {
                    temp[0]=node.getResponseBuffer(0);
                    temp[1]=node.getResponseBuffer(1);
                    node.clearResponseBuffer();
                    Length_value_calib0=bytesToFloat(&temp[0]);
                    Length_raw_calib0=Length_raw;

                    preferences.putFloat("L1",Length_value_calib0);
                    preferences.putShort("L3",Length_raw_calib0);

                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(54,0);
                    //Serial.print("Length_value_calib0 "); Serial.println(Length_value_calib0,2);
            }

            if(Trigger_Setting_Length_calib1==1)
            {
                uint16_t temp[2];
                if (node.readHoldingRegisters(Length_value_calib1_addr, 2) == node.ku8MBSuccess)
                {
                    temp[0]=node.getResponseBuffer(0);
                    temp[1]=node.getResponseBuffer(1);
                    node.clearResponseBuffer();
                    Length_value_calib1=bytesToFloat(&temp[0]);
                    Length_raw_calib1=Length_raw;

                    preferences.putFloat("L2",Length_value_calib1);
                    preferences.putShort("L4",Length_raw_calib1);

                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(55,0);
                    //Serial.print("Length_value_calib1 "); Serial.println(Length_value_calib1,2);
            }

            if(Trigger_Setting_Length==1)
            {   uint16_t temp[6];
                if (node.readHoldingRegisters(Length_alarm_min_addr, 6) == node.ku8MBSuccess)
                {
                    temp[0]=node.getResponseBuffer(0);
                    temp[1]=node.getResponseBuffer(1);
                    temp[2]=node.getResponseBuffer(2);
                    temp[3]=node.getResponseBuffer(3);
                    temp[4]=node.getResponseBuffer(4);
                    temp[5]=node.getResponseBuffer(5);
                    node.clearResponseBuffer();
                    Length_alarm_min=bytesToFloat(&temp[0]);
                    Length_alarm_set=bytesToFloat(&temp[2]);
                    Length_alarm_max=bytesToFloat(&temp[4]);
                    
                    preferences.putFloat("L5",Length_alarm_min);
                    preferences.putFloat("L6",Length_alarm_set);
                    preferences.putFloat("L7",Length_alarm_max);

                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(25,0);      // Clear Trigger_Setting_Length
                    //Serial.print("Length_alarm_min "); Serial.println(Length_alarm_min);
                    //Serial.print("Length_alarm_set "); Serial.println(Length_alarm_set);
                    //Serial.print("Length_alarm_max "); Serial.println(Length_alarm_max);
            }

            result = node.writeSingleRegister(Length_raw_addr,Length_raw); // Gui bien len man hinh lien tuc
            Float_to_Register(Length_value,1,2);
            result = node.writeMultipleRegisters(Length_value_addr, 2); // Gui bien len man hinh lien tuc
            node.clearTransmitBuffer();
        }
        break;

        case 8: // Dang o trang Set Device
        {   
            if(Trigger_Page==1)
            {
                node.writeSingleRegister(Device_addr,device_type);  // Gui bien len man hinh 1 lan dau load trang
                node.writeSingleCoil(Multi_Loadtable_State_addr,Multi_Loadtable_State);
                node.writeSingleCoil(Trigger_Page_addr,0);          // Clear Trigger Page
            }
            if(node.readCoils(26,1) == node.ku8MBSuccess)
            {
                Trigger_Setting_Device=node.getResponseBuffer(0);
                node.clearResponseBuffer();
            }

            if(Trigger_Setting_Device==1)
            {   
                if (node.readHoldingRegisters(Device_addr, 1) == node.ku8MBSuccess)
                {
                    
                    device_type=node.getResponseBuffer(0);
                    if(device_type>9)
                    {
                        device_type=1;
                    }
                    node.clearResponseBuffer();
                    preferences.putUChar("DT",device_type);
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                }

                if(node.readCoils(27,1) == node.ku8MBSuccess)
                {
                    Multi_Loadtable_State=node.getResponseBuffer(0);
                    preferences.putBool("LTB_state",Multi_Loadtable_State);
                    node.clearResponseBuffer();
                }
                    node.writeSingleCoil(26,0);      // Clear Trigger_Setting_Length
                    //Serial.print("Device_type "); Serial.println(device_type);
                    //Serial.print("Multi_Loadtable_State "); Serial.println(Multi_Loadtable_State);
            }
        }
        break;

        case 9: // Dang o trang Set Load
        {   
            if(Trigger_Page==1)
            {
                Word_to_Register(Load_alarm_set,1);
                Word_to_Register(Load_alarm_max,2);
                result = node.writeMultipleRegisters(Load_alarm_set_addr, 2); // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                Float_to_Register(T0_value,1,2);
                Float_to_Register(T0_P_main,3,4);
                Float_to_Register(T0_P_aux,5,6);
                Float_to_Register(T0_Length,7,8);
                Float_to_Register(T0_Angle,9,10);
                result = node.writeMultipleRegisters(T0_value_addr, 10); // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }

            if(node.readCoils(28,2) == node.ku8MBSuccess)
            {
                Set_load_0=node.getResponseBuffer(0) & bit(0);
                Trigger_Setting_Load=node.getResponseBuffer(0) & bit(1);
                node.clearResponseBuffer();
            }

            if(Set_load_0==1)   // Bắt đầu set Load 0, quan trọng.......
            {
                flag_setLoad0_Whell=1;
                node.writeSingleCoil(28,0);
                node.writeSingleCoil(Trigger_Page_addr,1);
            }

            if(Trigger_Setting_Load==1)
            {
                if (node.readHoldingRegisters(Load_alarm_set_addr, 2) == node.ku8MBSuccess)
                {
                    Load_alarm_set=node.getResponseBuffer(0);
                    Load_alarm_max=node.getResponseBuffer(1);
                    node.clearResponseBuffer();
                    preferences.putShort("LoadS",Load_alarm_set);
                    preferences.putShort("LoadM",Load_alarm_max);
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(29,0);      // Clear Trigger_Setting_Load
            }

            Float_to_Register(Angle_value,1,2);
            Float_to_Register(Length_value,3,4);
            Float_to_Register(W_value,5,6);
            result = node.writeMultipleRegisters(Angle_value_addr, 6); // Gui bien len man hinh lien tuc
            node.clearTransmitBuffer();

            Float_to_Register(P_main_value,1,2);
            Float_to_Register(P_aux_value,3,4);
            result = node.writeMultipleRegisters(P_main_value_addr, 4); // Gui bien len man hinh lien tuc
            node.clearTransmitBuffer();
        }
        break;

        case 10: // Dang o trang Cai dat Press
        {   
            if(Trigger_Page==1)
            {
                Word_to_Register(P1_range,1);
                Word_to_Register(P2_range,2);
                Word_to_Register(P3_range,3);
                Word_to_Register(P4_range,4);
                Word_to_Register(P5_range,5);
                Word_to_Register(P_main_select,6);
                Word_to_Register(P_aux_select,7);
                result = node.writeMultipleRegisters(P1_range_addr, 7);   // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }

            if(node.readCoils(30,1) == node.ku8MBSuccess)
            {
                Trigger_Setting_Press=node.getResponseBuffer(0);
                node.clearResponseBuffer();
            }

            if(Trigger_Setting_Press==1)     // Cài đặt Alarm Press
            {
                if (node.readHoldingRegisters(P1_range_addr, 7) == node.ku8MBSuccess)
                {
                    P1_range=node.getResponseBuffer(0);
                    P2_range=node.getResponseBuffer(1);
                    P3_range=node.getResponseBuffer(2);
                    P4_range=node.getResponseBuffer(3);
                    P5_range=node.getResponseBuffer(4);
                    P_main_select=node.getResponseBuffer(5);
                    P_aux_select=node.getResponseBuffer(6);
                    node.clearResponseBuffer();
                    preferences.putShort("P1",P1_range);
                    preferences.putShort("P2",P2_range);
                    preferences.putShort("P3",P3_range);
                    preferences.putShort("P4",P4_range);
                    preferences.putShort("P5",P5_range);
                    preferences.putShort("P6",P_main_select);
                    preferences.putShort("P7",P_aux_select);
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(30,0);      // Clear Trigger_Setting_Press
            }
            Word_to_Register(P_main_raw,1);
            Word_to_Register(P_aux_raw,2);
            Word_to_Register(P1_raw,3);
            Word_to_Register(P2_raw,4);
            Word_to_Register(P3_raw,5);
            Word_to_Register(P4_raw,6);
            Word_to_Register(P5_raw,7);
            result = node.writeMultipleRegisters(P_main_raw_addr, 7);   // Gui bien len man hinh lien tuc
            node.clearTransmitBuffer();

            Float_to_Register(P_main_value,1,2);
            Float_to_Register(P_aux_value,3,4);
            Float_to_Register(P1_value,5,6);
            Float_to_Register(P2_value,7,8);
            Float_to_Register(P3_value,9,10);
            Float_to_Register(P4_value,11,12);
            Float_to_Register(P5_value,13,14);
            result = node.writeMultipleRegisters(P_main_value_addr, 14); // Gui bien len man hinh lien tuc
            node.clearTransmitBuffer();
        }
        break;

        case 11: // Dang o trang Cai dat Other
        {   
            if(Trigger_Page==1)
            {
                Float_to_Register(Parar,1,2);
                Float_to_Register(Parah,3,4);
                Float_to_Register(ParaCabW,5,6);
                Float_to_Register(Paraa,7,8);
                Float_to_Register(Parab,9,10);
                Float_to_Register(Parac,11,12);
                Float_to_Register(Parad,13,14);
                Float_to_Register(ParaE,15,16);
                Float_to_Register(Parag,17,18);
                Float_to_Register(Paran,19,20);
                Float_to_Register(ParaK1,21,22);
                Float_to_Register(ParaK2,23,24);
                Float_to_Register(ParaK3,25,26);
                Float_to_Register(ParaK4,27,28);
                result = node.writeMultipleRegisters(Parar_addr, 28);   // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }
            if(node.readCoils(32,1) == node.ku8MBSuccess)
            {
                Trigger_Setting_Other=node.getResponseBuffer(0);
                node.clearResponseBuffer();
            }

            if(Trigger_Setting_Other==1)     // Cài đặt Setting Other
            {   uint16_t temp[28];
                if (node.readHoldingRegisters(Parar_addr, 28) == node.ku8MBSuccess)
                {
                    for(uint8_t i=0;i<28;i++)
                    {
                        temp[i]=node.getResponseBuffer(i);
                    }
                    node.clearResponseBuffer();
                    Parar=bytesToFloat(&temp[0]);
                    Parah=bytesToFloat(&temp[2]);
                    ParaCabW=bytesToFloat(&temp[4]);
                    Paraa=bytesToFloat(&temp[6]);
                    Parab=bytesToFloat(&temp[8]);
                    Parac=bytesToFloat(&temp[10]);
                    Parad=bytesToFloat(&temp[12]);
                    ParaE=bytesToFloat(&temp[14]);
                    Parag=bytesToFloat(&temp[16]);
                    Paran=bytesToFloat(&temp[18]);
                    ParaK1=bytesToFloat(&temp[20]);
                    ParaK2=bytesToFloat(&temp[22]);
                    ParaK3=bytesToFloat(&temp[24]);
                    ParaK4=bytesToFloat(&temp[26]);
                    preferences.putFloat("Parar",Parar);
                    preferences.putFloat("Parah",Parah);
                    preferences.putFloat("ParaCabW",ParaCabW);
                    preferences.putFloat("Paraa",Paraa);
                    preferences.putFloat("Parab",Parab);
                    preferences.putFloat("Parac",Parac);
                    preferences.putFloat("Parad",Parad);
                    preferences.putFloat("ParaE",ParaE);
                    preferences.putFloat("Parag",Parag);
                    preferences.putFloat("Paran",Paran);
                    preferences.putFloat("ParaK1",ParaK1);
                    preferences.putFloat("ParaK2",ParaK2);
                    preferences.putFloat("ParaK3",ParaK3);
                    preferences.putFloat("ParaK4",ParaK4);
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(32,0);      // Clear Trigger_Setting_Other
                    // Serial.print("Parar "); Serial.println(Parar);
                    // Serial.print("Parah "); Serial.println(Parah);
                    // Serial.print("ParaCabW "); Serial.println(ParaCabW);
                    // Serial.print("Paraa "); Serial.println(Paraa);
                    // Serial.print("Parab "); Serial.println(Parab);
                    // Serial.print("Parac "); Serial.println(Parac);
                    // Serial.print("Parad "); Serial.println(Parad);
                    // Serial.print("ParaE "); Serial.println(ParaE);
                    // Serial.print("Parag "); Serial.println(Parag);
                    // Serial.print("Paran "); Serial.println(Paran);
                    // Serial.print("ParaK1 "); Serial.println(ParaK1);
                    // Serial.print("ParaK2 "); Serial.println(ParaK2);
                    // Serial.print("ParaK3 "); Serial.println(ParaK3);
                    // Serial.print("ParaK4 "); Serial.println(ParaK4);
            }
        }
        break;

        case 12: // Dang o trang Test Parameter
        {   
            if(Trigger_Page==1)
            {
                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }

            uint16_t temp,temp1;
            temp=(is_rom_init_ok<<7) | (is_hx7112_init_ok<<6) | (is_hx7111_init_ok<<5) | (is_ads2_init_ok<<4) | (is_ads1_init_ok<<3) | (DigitalInput_3<<2) | (DigitalInput_2<<1) | DigitalInput_1;
            node.setTransmitBuffer(0, temp);
            result = node.writeMultipleCoils(43, 8);
            node.clearTransmitBuffer();
            Mode_Test_Relay=1;
            
            if(node.readCoils(36,7) == node.ku8MBSuccess)
            {
                temp1=node.getResponseBuffer(0);
                node.clearResponseBuffer();
                Stt_CabMax=temp1 & bit(0);
                Stt_AngleHi=temp1 & bit(1);
                Stt_AngleSet=temp1 & bit(2);
                Stt_LengthHi=temp1 & bit(3);
                Stt_LengthLow=temp1 & bit(4);
                Stt_LoadHi=temp1 & bit(5);
                Stt_LoadSet=temp1 & bit(6);
            }
        }
        break;

        case 13: // Dang o trang Set Loadtable
        {   
            if(Trigger_Page==1)
            {
                node.writeSingleCoil(Multi_Loadtable_State_addr,Multi_Loadtable_State);
                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }
            if(node.readCoils(26,1) == node.ku8MBSuccess)
            {
                Trigger_Setting_Device=node.getResponseBuffer(0);
                node.clearResponseBuffer();
            }
            if(Trigger_Setting_Device==1)     // Cài đặt Alarm Angle
            {   
                if(node.readCoils(27,1) == node.ku8MBSuccess)
                {
                    Multi_Loadtable_State=node.getResponseBuffer(0);
                    preferences.putBool("LTB_state",Multi_Loadtable_State);

                    if(Multi_Loadtable_State==1)
                    {
                        Serial.println("Khong su dung");
                        Load_table_value=0;
                        Stt=1;
                        Trigger_LT=1;
                    }
                    else
                    {
                        Serial.println("Su dung");
                        Load_table_value=       preferences.getFloat("LT_value",0);
                        Trigger_LT=1;
                    }

                    node.clearResponseBuffer();
                }
            node.writeSingleCoil(26,0);      // Clear Trigger
            }

            Word_to_Register(Sohang,1);
            Word_to_Register(Socot,2);
            Word_to_Register(Stt,3);
            Float_to_Register(Load_table_value,4,5);
            Float_to_Register((Doitrong[0]/(float)100),6,7);
            Float_to_Register((Doitrong[1]/(float)100),8,9);
            Float_to_Register((Doitrong[2]/(float)100),10,11);
            Float_to_Register((Doitrong[3]/(float)100),12,13);
            Float_to_Register((Doitrong[4]/(float)100),14,15);
            Float_to_Register((Doitrong[5]/(float)100),16,17);
            Float_to_Register((Doitrong[6]/(float)100),18,19);
            Float_to_Register((Doitrong[7]/(float)100),20,21);
            Float_to_Register((Doitrong[8]/(float)100),22,23);
            Float_to_Register((Doitrong[9]/(float)100),24,25);
            result = node.writeMultipleRegisters(40500, 25);
            node.clearTransmitBuffer();
        }
        break;


        case 14: // Dang o trang Set Loadcell
        {   
            uint16_t temp;
            if(Trigger_Page==1)
            {
                Float_to_Register(Loadcell1_value_calib0,1,2);
                Float_to_Register(Loadcell1_value_calib1,3,4);
                Float_to_Register(Loadcell2_value_calib0,5,6);
                Float_to_Register(Loadcell2_value_calib1,7,8);
                result = node.writeMultipleRegisters(40109, 8); // Gui bien len man hinh lan dau
                node.clearTransmitBuffer();

                node.setTransmitBuffer(1, (Loadcell1_raw_calib0>>16) & 0xFFFF);
                node.setTransmitBuffer(0, (Loadcell1_raw_calib0 & 0xFFFF));
                node.setTransmitBuffer(3, (Loadcell1_raw_calib1>>16) & 0xFFFF);
                node.setTransmitBuffer(2, (Loadcell1_raw_calib1 & 0xFFFF));
                node.setTransmitBuffer(5, (Loadcell2_raw_calib0>>16) & 0xFFFF);
                node.setTransmitBuffer(4, (Loadcell2_raw_calib0 & 0xFFFF));
                node.setTransmitBuffer(7, (Loadcell2_raw_calib1>>16) & 0xFFFF);
                node.setTransmitBuffer(6, (Loadcell2_raw_calib1 & 0xFFFF));
                result = node.writeMultipleRegisters(40128, 8); // Gui bien len man hinh lan dau
                node.clearTransmitBuffer();

                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }

            if(node.readCoils(58,5) == node.ku8MBSuccess)
            {
                temp=node.getResponseBuffer(0);
                node.clearResponseBuffer();
                Trigger_Setting_Loadcell1_calib0=temp & bit(0);
                Trigger_Setting_Loadcell1_calib1=temp & bit(1);
                Trigger_Setting_Loadcell2_calib0=temp & bit(2);
                Trigger_Setting_Loadcell2_calib1=temp & bit(3);
                Trigger_Setting_Loadcell=temp & bit(4);
            }

            if(Trigger_Setting_Loadcell1_calib0==1)     // Cài đặt Calib0 Loadcell 1
            {   
                uint16_t temp[2];
                if (node.readHoldingRegisters(40109, 2) == node.ku8MBSuccess)
                {
                    temp[0]=node.getResponseBuffer(0);
                    temp[1]=node.getResponseBuffer(1);
                    node.clearResponseBuffer();
                    Loadcell1_value_calib0=bytesToFloat(&temp[0]);
                    Loadcell1_value_calib0=Loadcell1_value_calib0/Cab_main_number;
                    Loadcell1_raw_calib0=Loadcell1_raw;
                    preferences.putFloat("Load1",Loadcell1_value_calib0);
                    preferences.putUInt("Load5",Loadcell1_raw_calib0);
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                }
                node.writeSingleCoil(58,0);
                Serial.print("Loadcell1_value_calib0 "); Serial.println(Loadcell1_value_calib0,2);
                Serial.print("Loadcell1_raw_calib0 "); Serial.println(Loadcell1_raw_calib0);
            }

            if(Trigger_Setting_Loadcell1_calib1==1)     // Cài đặt Calib1 Loadcell 1
            {   
                uint16_t temp[2];
                if (node.readHoldingRegisters(40111, 2) == node.ku8MBSuccess)
                {
                    temp[0]=node.getResponseBuffer(0);
                    temp[1]=node.getResponseBuffer(1);
                    node.clearResponseBuffer();
                    Loadcell1_value_calib1=bytesToFloat(&temp[0]);
                    Loadcell1_value_calib1=Loadcell1_value_calib1/Cab_main_number;
                    Loadcell1_raw_calib1=Loadcell1_raw;
                    preferences.putFloat("Load2",Loadcell1_value_calib1);
                    preferences.putUInt("Load6",Loadcell1_raw_calib1);
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                }
                node.writeSingleCoil(59,0);
                Serial.print("Loadcell1_value_calib1 "); Serial.println(Loadcell1_value_calib1,2);
                Serial.print("Loadcell1_raw_calib1 "); Serial.println(Loadcell1_raw_calib1);
            }

            if(Trigger_Setting_Loadcell2_calib0==1)     // Cài đặt Calib0 Loadcell 2
            {   
                uint16_t temp[2];
                if (node.readHoldingRegisters(40113, 2) == node.ku8MBSuccess)
                {
                    temp[0]=node.getResponseBuffer(0);
                    temp[1]=node.getResponseBuffer(1);
                    node.clearResponseBuffer();
                    Loadcell2_value_calib0=bytesToFloat(&temp[0]);
                    Loadcell2_value_calib0=Loadcell2_value_calib0/Cab_aux_number;
                    Loadcell2_raw_calib0=Loadcell2_raw;
                    preferences.putFloat("Load3",Loadcell2_value_calib0);
                    preferences.putUInt("Load7",Loadcell2_raw_calib0);
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                }
                node.writeSingleCoil(60,0);
                Serial.print("Loadcell2_value_calib0 "); Serial.println(Loadcell2_value_calib0,2);
                Serial.print("Loadcell2_raw_calib0 "); Serial.println(Loadcell2_raw_calib0);
            }

            if(Trigger_Setting_Loadcell2_calib1==1)     // Cài đặt Calib1 Loadcell 2
            {   
                uint16_t temp[2];
                if (node.readHoldingRegisters(40115, 2) == node.ku8MBSuccess)
                {
                    temp[0]=node.getResponseBuffer(0);
                    temp[1]=node.getResponseBuffer(1);
                    node.clearResponseBuffer();
                    Loadcell2_value_calib1=bytesToFloat(&temp[0]);
                    Loadcell2_value_calib1=Loadcell2_value_calib1/Cab_aux_number;
                    Loadcell2_raw_calib1=Loadcell2_raw;
                    preferences.putFloat("Load4",Loadcell2_value_calib1);
                    preferences.putUInt("Load8",Loadcell2_raw_calib1);
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                }
                node.writeSingleCoil(61,0);
                Serial.print("Loadcell2_value_calib1 "); Serial.println(Loadcell2_value_calib1,2);
                Serial.print("Loadcell2_raw_calib1 "); Serial.println(Loadcell2_raw_calib1);
            }

            if(Trigger_Setting_Loadcell==1)
            {   uint16_t temp[8];
                if (node.readHoldingRegisters(40128, 8) == node.ku8MBSuccess)
                {
                    temp[0]=node.getResponseBuffer(0);
                    temp[1]=node.getResponseBuffer(1);
                    temp[2]=node.getResponseBuffer(2);
                    temp[3]=node.getResponseBuffer(3);
                    temp[4]=node.getResponseBuffer(4);
                    temp[5]=node.getResponseBuffer(5);
                    temp[6]=node.getResponseBuffer(6);
                    temp[7]=node.getResponseBuffer(7);

                    node.clearResponseBuffer();
                    Loadcell1_raw_calib0=temp[0] | temp[1]<<16;
                    Loadcell1_raw_calib1=temp[2] | temp[3]<<16;
                    Loadcell2_raw_calib0=temp[4] | temp[5]<<16;
                    Loadcell2_raw_calib1=temp[6] | temp[7]<<16;
                    
                    preferences.putUInt("Load5",Loadcell1_raw_calib0);
                    preferences.putUInt("Load6",Loadcell1_raw_calib1);
                    preferences.putUInt("Load7",Loadcell2_raw_calib0);
                    preferences.putUInt("Load8",Loadcell2_raw_calib1);

                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(62,0);      // Clear Trigger_Setting_Length
                    Serial.print("Loadcell1_raw_calib0 "); Serial.println(Loadcell1_raw_calib0);
                    Serial.print("Loadcell1_raw_calib1 "); Serial.println(Loadcell1_raw_calib1);
                    Serial.print("Loadcell2_raw_calib0 "); Serial.println(Loadcell2_raw_calib0);
                    Serial.print("Loadcell2_raw_calib1 "); Serial.println(Loadcell2_raw_calib1);
            }
            
            Float_to_Register(Loadcell1_value,1,2);
            Float_to_Register(Loadcell2_value,3,4);
            Float_to_Register(Loadcelltotal_value,5,6);
            result = node.writeMultipleRegisters(40085, 6); // Gui bien len man hinh lien tuc
            node.clearTransmitBuffer();

            node.setTransmitBuffer(1, (Loadcell1_raw>>16) & 0xFFFF);
            node.setTransmitBuffer(0, (Loadcell1_raw & 0xFFFF));
            node.setTransmitBuffer(3, (Loadcell2_raw>>16) & 0xFFFF);
            node.setTransmitBuffer(2, (Loadcell2_raw & 0xFFFF));
            result = node.writeMultipleRegisters(40310, 4); // Gui bien len man hinh lien tuc
            node.clearTransmitBuffer();
            // Serial.print("Loadcell1_raw ");Serial.println(Loadcell1_raw);
            // Serial.print("Loadcell2_raw ");Serial.println(Loadcell2_raw);
        }
        break;

        case 15: // Dang o trang Set Load Banh xich
        {   
            if(Trigger_Page==1)
            {
                Word_to_Register(Load_alarm_set,1);
                Word_to_Register(Load_alarm_max,2);
                result = node.writeMultipleRegisters(Load_alarm_set_addr, 2); // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();

                Float_to_Register(P0_value,1,2);
                Float_to_Register(P0_Loadcell,3,4);
                Float_to_Register(P0_Length,5,6);
                Float_to_Register(P0_Angle,7,8);
                Float_to_Register(P0_L0_value,9,10);

                result = node.writeMultipleRegisters(40159, 10); // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }

            if(node.readCoils(28,2) == node.ku8MBSuccess)
            {
                Set_load_0=node.getResponseBuffer(0) & bit(0);
                Trigger_Setting_Load=node.getResponseBuffer(0) & bit(1);
                node.clearResponseBuffer();
            }

            if(Set_load_0==1)   // Bắt đầu set Load 0, quan trọng.......
            {
                flag_setLoad0_Crawler=1;
                node.writeSingleCoil(28,0);
                node.writeSingleCoil(Trigger_Page_addr,1);
            }

            if(Trigger_Setting_Load==1)
            {
                if (node.readHoldingRegisters(Load_alarm_set_addr, 2) == node.ku8MBSuccess)
                {
                    Load_alarm_set=node.getResponseBuffer(0);
                    Load_alarm_max=node.getResponseBuffer(1);
                    node.clearResponseBuffer();
                    preferences.putShort("LoadS",Load_alarm_set);
                    preferences.putShort("LoadM",Load_alarm_max);
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(29,0);      // Clear Trigger_Setting_Load
            }

            Float_to_Register(Angle_value,1,2);
            Float_to_Register(Length_value,3,4);
            Float_to_Register(W_value,5,6);
            result = node.writeMultipleRegisters(Angle_value_addr, 6); // Gui bien len man hinh lien tuc
            node.clearTransmitBuffer();

            Float_to_Register(Loadcelltotal_value,1,2);
            Float_to_Register(L0_value,3,4);
            result = node.writeMultipleRegisters(40089, 4); // Gui bien len man hinh lien tuc
            node.clearTransmitBuffer();
        }
        break;

        case 16: // Dang o trang Cài đặt customer
        {   
            Trigger_Customer=1;
            node.writeSingleCoil(64,1); // Trigger Customer
        }
        break;

        case 17: // Dang o trang Cài đặt %
        {   
            if(Trigger_Page==1)
            {
                Serial.println("Cap nhat lan dau");
                Word_to_Register(Taiphantram_05,1);
                Word_to_Register(Taiphantram_10,2);
                Word_to_Register(Taiphantram_15,3);
                Word_to_Register(Taiphantram_20,4);
                Word_to_Register(Taiphantram_25,5);
                Word_to_Register(Taiphantram_30,6);
                Word_to_Register(Taiphantram_35,7);
                Word_to_Register(Taiphantram_40,8);
                Word_to_Register(Taiphantram_45,9);
                Word_to_Register(Taiphantram_50,10);
                Word_to_Register(Taiphantram_55,11);
                Word_to_Register(Taiphantram_60,12);
                Word_to_Register(Taiphantram_65,13);
                Word_to_Register(Taiphantram_70,14);
                Word_to_Register(Taiphantram_75,15);
                Word_to_Register(Taiphantram_80,16);
                Word_to_Register(Taiphantram_85,17);
                Word_to_Register(Taiphantram_90,18);
                result = node.writeMultipleRegisters(40525, 18); // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }

            if(node.readCoils(65,1) == node.ku8MBSuccess)
            {
                Trigger_Setting_Other1=node.getResponseBuffer(0);
                node.clearResponseBuffer();
            }

            if(Trigger_Setting_Other1==1)     // Cài đặt Setting Other
            {   uint16_t temp[18];
                if (node.readHoldingRegisters(40525, 18) == node.ku8MBSuccess)
                {
                    for(uint8_t i=0;i<18;i++)
                    {
                        temp[i]=node.getResponseBuffer(i);
                    }
                    node.clearResponseBuffer();
                    node.getResponseBuffer(0);
                    Taiphantram_05=temp[0];
                    Taiphantram_10=temp[1];
                    Taiphantram_15=temp[2];
                    Taiphantram_20=temp[3];
                    Taiphantram_25=temp[4];
                    Taiphantram_30=temp[5];
                    Taiphantram_35=temp[6];
                    Taiphantram_40=temp[7];
                    Taiphantram_45=temp[8];
                    Taiphantram_50=temp[9];
                    Taiphantram_55=temp[10];
                    Taiphantram_60=temp[11];
                    Taiphantram_65=temp[12];
                    Taiphantram_70=temp[13];
                    Taiphantram_75=temp[14];
                    Taiphantram_80=temp[15];
                    Taiphantram_85=temp[16];
                    Taiphantram_90=temp[17];

                    preferences.putUInt("Taiphantram_05",Taiphantram_05);
                    preferences.putUInt("Taiphantram_10",Taiphantram_10);
                    preferences.putUInt("Taiphantram_15",Taiphantram_15);
                    preferences.putUInt("Taiphantram_20",Taiphantram_20);
                    preferences.putUInt("Taiphantram_25",Taiphantram_25);
                    preferences.putUInt("Taiphantram_30",Taiphantram_30);
                    preferences.putUInt("Taiphantram_35",Taiphantram_35);
                    preferences.putUInt("Taiphantram_40",Taiphantram_40);
                    preferences.putUInt("Taiphantram_45",Taiphantram_45);
                    preferences.putUInt("Taiphantram_50",Taiphantram_50);
                    preferences.putUInt("Taiphantram_55",Taiphantram_55);
                    preferences.putUInt("Taiphantram_60",Taiphantram_60);
                    preferences.putUInt("Taiphantram_65",Taiphantram_65);
                    preferences.putUInt("Taiphantram_70",Taiphantram_70);
                    preferences.putUInt("Taiphantram_75",Taiphantram_75);
                    preferences.putUInt("Taiphantram_80",Taiphantram_80);
                    preferences.putUInt("Taiphantram_85",Taiphantram_85);
                    preferences.putUInt("Taiphantram_90",Taiphantram_90);
                    Serial.println("Cap nhat %");
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(65,0);      // Clear Trigger_Setting_Other
            }
        }
        break;


        case 18: // Dang o trang Cài đặt % Dài Cần
        {   
            if(Trigger_Page==1)
            {
                Serial.println("Cap nhat lan dau");
                Word_to_Register(Ptramboom_05,1);
                Word_to_Register(Ptramboom_10,2);
                Word_to_Register(Ptramboom_15,3);
                Word_to_Register(Ptramboom_20,4);
                Word_to_Register(Ptramboom_25,5);
                Word_to_Register(Ptramboom_30,6);
                Word_to_Register(Ptramboom_35,7);
                Word_to_Register(Ptramboom_40,8);
                Word_to_Register(Ptramboom_45,9);
                Word_to_Register(Ptramboom_50,10);
                Word_to_Register(Ptramboom_55,11);
                Word_to_Register(Ptramboom_60,12);
                Word_to_Register(Ptramboom_65,13);
                Word_to_Register(Ptramboom_70,14);
                Word_to_Register(Ptramboom_75,15);
                Word_to_Register(Ptramboom_80,16);
                Word_to_Register(Ptramboom_85,17);
                Word_to_Register(Ptramboom_90,18);
                result = node.writeMultipleRegisters(40601, 18); // Gui bien len man hinh 1 lan dau load trang
                node.clearTransmitBuffer();
                node.writeSingleCoil(Trigger_Page_addr,0);      // Clear Trigger Page
            }

            if(node.readCoils(65,1) == node.ku8MBSuccess)
            {
                Trigger_Setting_Other1=node.getResponseBuffer(0);
                node.clearResponseBuffer();
            }

            if(Trigger_Setting_Other1==1)     // Cài đặt Setting Other
            {   uint16_t temp[18];
                if (node.readHoldingRegisters(40601, 18) == node.ku8MBSuccess)
                {
                    for(uint8_t i=0;i<18;i++)
                    {
                        temp[i]=node.getResponseBuffer(i);
                    }
                    node.clearResponseBuffer();
                    node.getResponseBuffer(0);
                    
                    Ptramboom_05=temp[0];
                    Ptramboom_10=temp[1];
                    Ptramboom_15=temp[2];
                    Ptramboom_20=temp[3];
                    Ptramboom_25=temp[4];
                    Ptramboom_30=temp[5];
                    Ptramboom_35=temp[6];
                    Ptramboom_40=temp[7];
                    Ptramboom_45=temp[8];
                    Ptramboom_50=temp[9];
                    Ptramboom_55=temp[10];
                    Ptramboom_60=temp[11];
                    Ptramboom_65=temp[12];
                    Ptramboom_70=temp[13];
                    Ptramboom_75=temp[14];
                    Ptramboom_80=temp[15];
                    Ptramboom_85=temp[16];
                    Ptramboom_90=temp[17];

                    preferences.putUInt("Ptramboom_05",Ptramboom_05);
                    preferences.putUInt("Ptramboom_10",Ptramboom_10);
                    preferences.putUInt("Ptramboom_15",Ptramboom_15);
                    preferences.putUInt("Ptramboom_20",Ptramboom_20);
                    preferences.putUInt("Ptramboom_25",Ptramboom_25);
                    preferences.putUInt("Ptramboom_30",Ptramboom_30);
                    preferences.putUInt("Ptramboom_35",Ptramboom_35);
                    preferences.putUInt("Ptramboom_40",Ptramboom_40);
                    preferences.putUInt("Ptramboom_45",Ptramboom_45);
                    preferences.putUInt("Ptramboom_50",Ptramboom_50);
                    preferences.putUInt("Ptramboom_55",Ptramboom_55);
                    preferences.putUInt("Ptramboom_60",Ptramboom_60);
                    preferences.putUInt("Ptramboom_65",Ptramboom_65);
                    preferences.putUInt("Ptramboom_70",Ptramboom_70);
                    preferences.putUInt("Ptramboom_75",Ptramboom_75);
                    preferences.putUInt("Ptramboom_80",Ptramboom_80);
                    preferences.putUInt("Ptramboom_85",Ptramboom_85);
                    preferences.putUInt("Ptramboom_90",Ptramboom_90);
                    Serial.println("Cap nhat %");
                    node.writeSingleCoil(Trigger_Page_addr,1);      // Clear Trigger Page
                 }
                    node.writeSingleCoil(65,0);      // Clear Trigger_Setting_Other
            }
        }
        break;

        case 19: // Dang o trang Banh xich
        case 20:
        {
            if(node.readCoils(18,4) == node.ku8MBSuccess)  // Read Trigger_Cab_Input
            {
                Trigger_Length_nhapmanhinh=node.getResponseBuffer(0) & bit(0);
                Trigger_Loadtable=node.getResponseBuffer(0) & bit(1);
                Trigger_Main_Aux=node.getResponseBuffer(0) & bit(2);
                Trigger_Cab_Input=node.getResponseBuffer(0) & bit(3);
                node.clearResponseBuffer();
            }

            if(DigitalInput_1==1)               // Hien thi ngat cap len man hinh
            {
                node.writeSingleCoil(31,0);
            }
            else
            {
                node.writeSingleCoil(31,1);
            }

            if(Trigger_Length_nhapmanhinh==1)
            {   uint16_t temp[2];
                node.readHoldingRegisters(Length_banhxich_addr, 2);
                temp[0]=node.getResponseBuffer(0);
                temp[1]=node.getResponseBuffer(1);
                node.clearResponseBuffer();
                Length_xich_nhap=bytesToFloat(&temp[0]);
                preferences.putFloat("L_xich",Length_xich_nhap);
                Length_value=Length_xich_nhap;
                Serial.print("Gia tri vua nhap: ");Serial.println(Length_value);
                node.writeSingleCoil(18,0); // Clear Trigger_Loadtable
            }
            if(Trigger_Main_Aux==1)
            {
                node.readCoils(35, 1);
                Main_Aux=node.getResponseBuffer(0);
                node.clearResponseBuffer();
                preferences.putBool("Main_Aux",Main_Aux);
                node.writeSingleCoil(20,0); // Clear Trigger_Main_Aux
                // Serial.print("Vua chon cap: "); Serial.println(Main_Aux);        /// 1 La cap phu, 0 la cap chinh
            }

            if(Trigger_Cab_Input==1)
            {
                node.readHoldingRegisters(Cab_number_addr, 1);
                if(Main_Aux==1)
                {
                    Cab_aux_number=node.getResponseBuffer(0);
                    preferences.putShort("Cab_aux_num",Cab_aux_number);
                    // Serial.print("So soi cap phu vua nhap: "); Serial.println(Cab_aux_number);
                }
                else
                {
                    Cab_main_number=node.getResponseBuffer(0);
                    preferences.putShort("Cab_main_num",Cab_main_number);
                    // Serial.print("So soi cap chinh vua nhap: "); Serial.println(Cab_main_number);                    
                }
                node.clearResponseBuffer();
                node.writeSingleCoil(21,0); // Clear Trigger_Cab_Input
            }

            if(Trigger_Loadtable==1)
            {   uint16_t temp[2];
                node.readHoldingRegisters(40400, 1);
                Canphu=node.getResponseBuffer(0);
                node.clearResponseBuffer();
                Trigger_LT=1;
                node.writeSingleCoil(19,0); // Clear Trigger_Loadtable
                node.clearTransmitBuffer();

                if(Canphu!=0)
                {
                    Trigger_Main_Aux=1;
                    node.writeSingleCoil(20,1); // Clear Trigger_Main_Aux
                    result = node.writeSingleRegister(Screen_no_control_addr,19);
                    node.clearTransmitBuffer();
                }

                if(Canphu==0)
                {
                    Trigger_Main_Aux=1;
                    node.writeSingleCoil(20,1); // Clear Trigger_Main_Aux
                    result = node.writeSingleRegister(Screen_no_control_addr,20);
                    node.clearTransmitBuffer();
                }
            }

            if(Main_Aux==1)
                Cab_number = Cab_aux_number;
            else
                Cab_number = Cab_main_number;

            Float_to_Register(Angle_value,1,2);
            Float_to_Register(Length_value,3,4);

            if(W_value<0)
            {
                Float_to_Register(0-W_value,5,6);
            }
            else
            {
                Float_to_Register(W_value,5,6);
            }

            Float_to_Register(MaxW_value,7,8);
            Word_to_Register(Cab_number,9);
            Float_to_Register(R_value,11,12);
            Float_to_Register(H_value,13,14);
            Word_to_Register(Loadpercent,15);
            result = node.writeMultipleRegisters(Angle_value_addr, 15);   // Gui bien len man hinh
            node.clearTransmitBuffer();

            uint8_t temp1;
            temp1=((!Stt_LoadSet)<<1) | (!Stt_LoadHi);
            node.setTransmitBuffer(0, temp1);
            result = node.writeMultipleCoils(56, 2);
            node.clearTransmitBuffer();

            uint8_t temp;
            temp=((!Stt_AngleHi)<<6) | ((!Stt_AngleSet)<<5) | ((!Stt_LengthHi)<<3) | ((!Stt_LengthLow)<<2) | ((!Stt_LoadHi)<<1) | (!Stt_LoadSet);
            node.setTransmitBuffer(0, temp);
            result = node.writeMultipleCoils(11, 7);
            node.clearTransmitBuffer();

            if(Canphu==1)
            {
                Float_to_Register(float(12.2),1,2);
                Float_to_Register(float(10.0),3,4);
                result = node.writeMultipleRegisters(40402, 4);   // Gui bien len man hinh
                node.clearTransmitBuffer();
            }
            if(Canphu==2)
            {
                Float_to_Register(float(12.2),1,2);
                Float_to_Register(float(30.0),3,4);
                result = node.writeMultipleRegisters(40402, 4);   // Gui bien len man hinh
                node.clearTransmitBuffer();
            }
            if(Canphu==3)
            {
                Float_to_Register(float(15.2),1,2);
                Float_to_Register(float(10.0),3,4);
                result = node.writeMultipleRegisters(40402, 4);   // Gui bien len man hinh
                node.clearTransmitBuffer();
            }
            if(Canphu==4)
            {
                Float_to_Register(float(15.2),1,2);
                Float_to_Register(float(30.0),3,4);
                result = node.writeMultipleRegisters(40402, 4);   // Gui bien len man hinh
                node.clearTransmitBuffer();
            }

        }
        break;

        case 22:
        {
            if(node.readCoils(19,3) == node.ku8MBSuccess)  // Read Trigger_Cab_Input
            {
                Trigger_Loadtable=node.getResponseBuffer(0) & bit(0);
                Trigger_Main_Aux=node.getResponseBuffer(0) & bit(1);
                Trigger_Cab_Input=node.getResponseBuffer(0) & bit(2);
                node.clearResponseBuffer();
            }

            if(DigitalInput_1==1)               // Hien thi ngat cap len man hinh
            {
                node.writeSingleCoil(31,0);
            }
            else
            {
                node.writeSingleCoil(31,1);
            }

            if(Trigger_Main_Aux==1)
            {
                if(node.readCoils(35, 1) == node.ku8MBSuccess)
                {
                    Main_Aux=node.getResponseBuffer(0);
                    node.clearResponseBuffer();
                    preferences.putBool("Main_Aux",Main_Aux);
                }
                node.writeSingleCoil(20,0); // Clear Trigger_Main_Aux
                // Serial.print("Vua chon cap: "); Serial.println(Main_Aux);        /// 1 La cap phu, 0 la cap chinh
            }

            if(Trigger_Cab_Input==1)
            {
                node.readHoldingRegisters(Cab_number_addr, 1);
                if(Main_Aux==1)
                {
                    Cab_aux_number=node.getResponseBuffer(0);
                    preferences.putShort("Cab_aux_num",Cab_aux_number);
                    // Serial.print("So soi cap phu vua nhap: "); Serial.println(Cab_aux_number);
                }
                else
                {
                    Cab_main_number=node.getResponseBuffer(0);
                    preferences.putShort("Cab_main_num",Cab_main_number);
                    // Serial.print("So soi cap chinh vua nhap: "); Serial.println(Cab_main_number);                    
                }
                node.clearResponseBuffer();
                node.writeSingleCoil(21,0); // Clear Trigger_Cab_Input
            }

            if(Trigger_Loadtable==1)
            {
                uint16_t temp[2];
                node.readHoldingRegisters(Load_table_value_addr, 2);
                temp[0]=node.getResponseBuffer(0);
                temp[1]=node.getResponseBuffer(1);
                node.clearResponseBuffer();
                Load_table_value=bytesToFloat(&temp[0]);

                preferences.putFloat("LT_value",Load_table_value);
                node.clearResponseBuffer();
                Trigger_LT=1;
                node.writeSingleCoil(19,0); // Clear Trigger_Loadtable
            }

            if(Main_Aux==1)
                Cab_number = Cab_aux_number;
            else
                Cab_number = Cab_main_number;

            Float_to_Register(Angle_value,1,2);
            Float_to_Register(Length_value,3,4);
            if(W_value<0)
            {
                Float_to_Register(0-W_value,5,6);
            }
            else
            {
                Float_to_Register(W_value,5,6);
            }
            Float_to_Register(MaxW_value,7,8);
            Word_to_Register(Cab_number,9);
            //Word_to_Register(Load_stt,10);
            Float_to_Register(R_value,11,12);
            Float_to_Register(H_value,13,14);
            Word_to_Register(Loadpercent,15);
            result = node.writeMultipleRegisters(Angle_value_addr, 15);   // Gui bien len man hinh
            node.clearTransmitBuffer();

            uint8_t temp1;
            temp1=((!Stt_LoadSet)<<1) | (!Stt_LoadHi);
            node.setTransmitBuffer(0, temp1);
            result = node.writeMultipleCoils(56, 2);
            node.clearTransmitBuffer();

            uint8_t temp;
            temp=((!Stt_AngleHi)<<6) | ((!Stt_AngleSet)<<5) | ((!Stt_LengthHi)<<3) | ((!Stt_LengthLow)<<2) | ((!Stt_LoadHi)<<1) | (!Stt_LoadSet);
            node.setTransmitBuffer(0, temp);
            result = node.writeMultipleCoils(11, 7);
            node.clearTransmitBuffer();

        }
        break;

        default:
        {
            //result = node.writeSingleRegister(Screen_no_control_addr,0x02);
        }
        break;
    }
    digitalWrite(Led1, !digitalRead(Led1));
    vTaskDelay(200);
  } 
}