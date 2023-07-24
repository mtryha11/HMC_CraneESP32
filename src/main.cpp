#include <Arduino.h>
#include "main.h"
#include "Wifi_OTATask.h"

TaskHandle_t Task_HMI;
TaskHandle_t Task_Debug;
TaskHandle_t Task_Caculate;
TaskHandle_t Task_Alarm;
TaskHandle_t Task_Sensor;
TaskHandle_t Task_LoadTB;
TaskHandle_t Handle_Wifi_OTATask;
TaskHandle_t Task_CAN;

void setup() {
  // Serial.begin(115200); 
  //// Khoi tao Task ////
  
 
  xTaskCreatePinnedToCore(Wifi_OTATask,   "Task Wifi",            10192,  nullptr,  3, &Handle_Wifi_OTATask,1);     delay(50);
  xTaskCreate(Task_Alarm_code,    "Task_Alarm",         1004,   NULL, 8, &Task_Alarm);    delay(50);
  xTaskCreate(Task_LoadTB_code,   "Task_LoadTable",     20000,  NULL, 6, &Task_LoadTB);    delay(50); 
  xTaskCreate(Task_HMI_code,      "Task_HMI",           8000,  NULL, 2, &Task_HMI);    delay(50); 
  xTaskCreate(Task_Debug_code,    "Task_Debug",         5000,  NULL, 1, &Task_Debug);    delay(50); 
  xTaskCreate(Task_Caculate_code, "Task_Cacluate",      8000,  NULL, 3, &Task_Caculate);    delay(50); 
  xTaskCreate(Task_Sensor_code,   "Task_Sensor",        5000,  NULL, 4, &Task_Sensor);    delay(50);
  //xTaskCreatePinnedToCore(Task_CAN_code,      "Task_CAN",           10000,  NULL, 5, &Task_CAN,  1  );    delay(50);
  //// Khoi tao Task ////
}

void loop() 
{
  delay(1);
}
