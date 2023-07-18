// #include <Arduino.h>
// #include <TaskCAN.h>
// #include <CAN.h>

// void Task_CAN_code( void * pvParameters )
// {
//   CAN.setPins(15,14);
//   if (!CAN.begin(500E3)) {
//     Serial.println("Starting CAN failed!");
//     while (1);
//   }
//   for(;;)
//   {
//       // try to parse packet
//     int packetSize = CAN.parsePacket();

//     if (packetSize) 
//     {
//       // received a packet
//       //Serial.print("Received ");

//       if (CAN.packetExtended()) 
//       {
//         Serial.print("extended ");
//       }

//       if (CAN.packetRtr()) {
//         // Remote transmission request, packet contains no data
//         Serial.print("RTR ");
//       }

//       //Serial.print("packet with id 0x");
//       //Serial.print(CAN.packetId(), HEX);

//       if (CAN.packetRtr()) 
//       {
//         //Serial.print(" and requested length ");
//         //Serial.println(CAN.packetDlc());
//       } 
//       else 
//       {
//         //Serial.print(" and length ");
//         //Serial.println(packetSize);

//         // only print packet data for non-RTR packets
//         while (CAN.available()) {
//           Serial.print((char)CAN.read());
//         }
//         Serial.println();
//       }
//     }
//     vTaskDelay(100);
//   }
// }