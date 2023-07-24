#include <Arduino.h>

void Wifi_OTATask(void *arg);
void update();
void OnProgress(int progress, int totalt);
String getChipId();



// extern String MQTTPassword;
// extern bool flag_passMQTT;

// extern TaskHandle_t Handle_MQTTTask;
// extern TaskHandle_t Handle_WatchdogTask;
// extern TaskHandle_t Handle_MQTTTask;
// extern TaskHandle_t Handle_ModbusTCPTask;
// extern TaskHandle_t Handle_RS232MeterTask;
// extern TaskHandle_t Handle_Wifi_OTATask;
// extern TaskHandle_t Handle_RS485MasterTask;
// extern TaskHandle_t Handle_RS485SlaveTask;

#define WIFI_SSID           "Buin"
#define WIFI_PASSWORD       "1234qwer"