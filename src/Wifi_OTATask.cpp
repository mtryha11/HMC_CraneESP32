#include <Wifi_OTATask.h>
#include <HTTPUpdate.h>
#include <Wifi.h>
#include <WiFiSettings.h>
#include <HTTPClient.h>
#include <ESP32Ping.h>
#include <ArduinoNvs.h>

String      VERSION_INC =   "6.1.1";
String      MAC;

uint32_t updateCounter = 0;
bool is_Task_start=0;
bool is_Task_start_mqtt=0;
bool manual_update_firmware=0;
bool Check_firmware=0;
String ChipID;
bool check_internet;
uint32_t                timerun_WifiTask;
// uint8_t                 time_WifiTask=0;

bool Update_firmware;
bool flag_wificonnected;
bool flag_startup;

bool is_internet_ok = 0;
#define ProductKey "bf1ab444-706c-43c4-8f0a-36cc2baa6722"

uint8_t noconnect=0;
void Wifi_OTATask(void *arg)
{
    NVS.begin();
    MAC=String(WiFi.macAddress());;
    Serial.println("---------------------");
    while(noconnect<5)
    {   noconnect++;
        if(WiFiSettings.connect(false,30)==0)
            {
                Serial.print("No connect = ");
                Serial.println(noconnect);
            }
        else
            goto start;
    }
    Serial.println("Phat Wifi");
    WiFiSettings.connect(true,10);
    
    start:
    flag_startup=1;
    Serial.println("---------------------");
    ChipID=getChipId();
    update();
    vTaskDelay(5000);
    for(;;)
    {
        ///////////////////////// OTA ///////////////////////
        if (WiFi.status() == WL_CONNECTED)
        {
            flag_wificonnected=true;
            if(is_Task_start==0)
            {
                // xTaskCreatePinnedToCore(ModbusTCPTask,  "Task ModbusTCP",       8192,  nullptr,  3, &Handle_ModbusTCPTask,1);    vTaskDelay(100);
                is_Task_start=1;
            }            
        }
        else
        {
            flag_wificonnected=false;
            is_Task_start=0;
            // vTaskDelete(Handle_ModbusTCPTask);
            WiFiSettings.connect();
        }
        ///////////////////////// OTA ///////////////////////

        if(flag_wificonnected==0)
        {
            // save_to_memory=1;
            if(is_Task_start_mqtt==1)
            {
                Serial.println("Xoa MQTT Task!!!!!!!");
                // vTaskDelete(Handle_MQTTTask);
                is_Task_start_mqtt=0;
            }
        }
        else
        {
            if(Update_firmware==1 || Check_firmware==1)
            {
                updateCounter++;
                if (updateCounter > 20)
                {
                updateCounter = 0;
                Check_firmware = 0;
                Update_firmware = 0;
                update();
                }
            }
            
            if(is_Task_start_mqtt==0)
            {
                Serial.println("Khoi tao MQTT Task!!!!!!!");
                // xTaskCreatePinnedToCore(MQTTTask,       "Task MQTT",            8192,  nullptr,  2, &Handle_MQTTTask,0);         vTaskDelay(100);
                is_Task_start_mqtt=1;
            }

        }
        

        if((millis()-timerun_WifiTask>=60000))
        {
            // time_WifiTask++;
            Check_firmware=1;
            timerun_WifiTask=millis();
        }

        vTaskDelay(100);
    }
}

String getChipId()
{
  String ChipIdHex = String((uint32_t)(ESP.getEfuseMac() >> 32), HEX);
  ChipIdHex += String((uint32_t)ESP.getEfuseMac(), HEX);
  ChipIdHex += String(random(99999999),HEX);
  ChipIdHex.toUpperCase();
  return (ChipIdHex);
}



void update()
{
    // String url = "http://test.iot-geyes.duckdns.org/esp32-ota/update?";
    String url = "http://ota.geyes.cloud/update?";
    String feedback="";
    url += "k=" + String("CanXeCau550");
    url += "&v=" + String(VERSION_INC);
    url += "&s=" + String(WiFi.macAddress());
    //Serial.println(url);
    Update.onProgress(OnProgress);
    WiFiClient client;
    t_httpUpdate_return ret = httpUpdate.update(client, url, VERSION_INC);
    feedback = "{\"OTA\": \"" + url + "\", \"";
    feedback += "Code\": ";
    feedback += String(ret) + "}";
    // if we reach here, we failed to update
    Serial.println(feedback);
    // feedback.toCharArray(bufferWifi.Mes,feedback.length()+1);
    // xQueueSend(Hangdoi, &bufferWifi, portMAX_DELAY);
}

int last = 0;
void OnProgress(int progress, int totalt) {
	int progressPercent = (100 * progress) / totalt;
  Serial.print(".");
	if (last != progressPercent && progressPercent % 1 == 0) {
		//print every 10%
		Serial.println(progressPercent);
	}
	last = progressPercent;
}