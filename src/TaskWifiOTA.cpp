// #include <TaskWifiOTA.h>
// #include <Arduino.h>
// #include <ESPmDNS.h>
// #include <WiFi.h>
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// #include <AsyncElegantOTA.h>

// const char* ssid = "HMC";
// const char* password = "12345678";

// AsyncWebServer server(80);

// void Task_WifiOTA_code( void * pvParameters )
// {
//     Serial.begin(115200);
//     WiFi.mode(WIFI_STA);
//     WiFi.begin(ssid, password);
//     Serial.println("");
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }
//     Serial.println("");
//     Serial.print("Connected to ");
//     Serial.println(ssid);
//     Serial.print("IP address: ");

//     if(!MDNS.begin("hmc")) 
//     {
//         Serial.println("Error starting mDNS");
//         return;
//     }

//     Serial.println(WiFi.localIP());

//     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
//         request->send(200, "text/plain", "hmc.local/update");
//     });

//     AsyncElegantOTA.begin(&server);    // Start ElegantOTA
//     server.begin();
//     Serial.println("HTTP server started");

//     for(;;)
//     {
//         vTaskDelay(50);
//     }
// }