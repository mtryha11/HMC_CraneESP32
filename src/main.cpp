#include <Arduino.h>
#include "main.h"

TaskHandle_t Task_HMI;
TaskHandle_t Task_Debug;
TaskHandle_t Task_Caculate;
TaskHandle_t Task_Alarm;
TaskHandle_t Task_Sensor;
TaskHandle_t Task_LoadTB;
TaskHandle_t Task_WifiOTA;
TaskHandle_t Task_CAN;

void setup() {
  // Serial.begin(115200); 
  //// Khoi tao Task ////
  
  xTaskCreatePinnedToCore(Task_Alarm_code,    "Task_Alarm",         1004,   NULL, 8, &Task_Alarm,   0  );    delay(50);
  xTaskCreatePinnedToCore(Task_WifiOTA_code,  "Task_WifiOTA",       10000,  NULL, 7, &Task_Alarm,   0  );    delay(50);
  xTaskCreatePinnedToCore(Task_LoadTB_code,   "Task_LoadTable",     10000,  NULL, 6, &Task_LoadTB,  1  );    delay(50); 
  xTaskCreatePinnedToCore(Task_HMI_code,      "Task_HMI",           10000,  NULL, 2, &Task_HMI,     1  );    delay(50); 
  xTaskCreatePinnedToCore(Task_Debug_code,    "Task_Debug",         10000,  NULL, 1, &Task_Debug,   0  );    delay(50); 
  xTaskCreatePinnedToCore(Task_Caculate_code, "Task_Cacluate",      10000,  NULL, 3, &Task_Caculate,0  );    delay(50); 
  xTaskCreatePinnedToCore(Task_Sensor_code,   "Task_Sensor",        10000,  NULL, 4, &Task_Sensor,  1  );    delay(50);
  //xTaskCreatePinnedToCore(Task_CAN_code,      "Task_CAN",           10000,  NULL, 5, &Task_CAN,  1  );    delay(50);
  //// Khoi tao Task ////
}

void loop() 
{
  delay(1);
}
