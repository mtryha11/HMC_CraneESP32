#include <Arduino.h>
#include <TaskDebug.h>


void Task_Debug_code( void * pvParameters )
{
  pinMode(Led1,OUTPUT);
  for(;;)
  {
    if(result_comunication_HMI==1)
    {
      //digitalWrite(Led1, !digitalRead(Led1));
      //Serial.println("Nhan duoc du lieu Modbus");
      result_comunication_HMI=0;
    }
    #ifdef DEBUG_VALUE
      Serial.print("A= ");Serial.println(Angle_value);
      Serial.print("L= ");Serial.println(Length_value);
      Serial.print("W= ");Serial.println(W_value);
      Serial.print("MaxW= ");Serial.println(MaxW_value);
      Serial.print("Cab_number= ");Serial.println(Cab_number);
      Serial.print("H= ");Serial.println(H_value);
      Serial.print("R= ");Serial.println(R_value);
      Serial.print("%= ");Serial.println(Loadpercent);
    #endif
    // Serial.print("Task debug running on: ");
    // Serial.println(xPortGetCoreID());
    // Serial.println("-----------------------");
    // digitalWrite(Led1,!digitalRead(Led1));

    vTaskDelay(1000);
  }
}