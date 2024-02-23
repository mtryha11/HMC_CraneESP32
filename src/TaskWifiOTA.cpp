#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <WebServer.h>
#endif

#include <ElegantOTA.h>
#include <ESPmDNS.h>
// #include <HTTPClient.h>

#include <SPIFFS.h>

const char* ssid = "hmc";
const char* password1 = "hoangminhim";
const char* password = "hoangminhim";

#if defined(ESP8266)
  ESP8266WebServer server(80);
#elif defined(ESP32)
  WebServer server(80);
#endif
uint8_t retry=0;

void Task_WifiOTA_code( void * pvParameters )
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password1);


    while (retry<20)
    {
        if(WiFi.status() == WL_CONNECTED)
        {
            goto jump;
        }
        if (WiFi.status() != WL_CONNECTED) 
        {
            vTaskDelay(1500);
            // Serial.print("Co gang ket noi Wifi lan thu ");
            // Serial.println(retry);
            retry++;
        }
    }
    WiFi.disconnect();
    // Serial.println("Phat Wifi!!");
    WiFi.softAP(WiFi.macAddress(),password);
    jump:
  // Initialize mDNS

    

  if (!MDNS.begin("hmc")) {   // Set the hostname to "esp32.local"
    // Serial.println("Error setting up MDNS responder!");
    while(1) {
      vTaskDelay(1000);
    }
  }
  // Serial.println("mDNS responder started");

    server.on("/", []() {
      server.send(200, "text/plain", "HMC");
    });

    ElegantOTA.begin(&server);    // Start ElegantOTA
    server.begin();
    // Serial.println("HTTP server started");

    for(;;)
    {
        server.handleClient();
        ElegantOTA.loop();
        vTaskDelay(100);
    }
}