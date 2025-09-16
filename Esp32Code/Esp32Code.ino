#include <SoftwareSerial.h>
#include <WebSocketsClient.h> // WebSocketsClient, webSocket.begin()
#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

// #define CS 5
// #define rele 13

// SoftwareSerial RFID(17, 16);

const char* ssid = "IFMS"; // your ssid
#define EAP_ID "caec.tl"
#define EAP_USERNAME "caec.tl"
#define EAP_PASSWORD "kF6P8ZnM"

// void openValve()
// {
//   digitalWrite(rele, HIGH);
//   delay(1000);

//   digitalWrite(rele, LOW);
// }

// void RegisterID(const char *path, const char *id)
// {
//   File file = SD.open(path, FILE_WRITE);

//   if(file)
//   {
//     file.println(id);
//     file.close();
//     Serial.printf("Registered ID: ", id);
//   } 
//   else
//   {
//     Serial.printf("Error opening file %s", path);
//   }
// }

// bool VerifyIDs(const char *path, const char *id)
// {
//   File file = SD.open(path);
  
//   if(file)
//   {
//     Serial.printf("Searching ID");
    
//     while(file.available())
//     {
//       uint8_t readId[13];
//       file.read(readId, 13);
      
//       for(int i = 0; i < 12; i++)
//       {
//         if(readId[i] != id[i])
//         {
//           break;
//         }
//         if(i == 11)
//         {
//           file.close();
//           return(true);
//         }
//       }
//     }
//     file.close();
//     return(false);
//   } 
//   else
//   {
//     Serial.printf("Error opening file %s", path);
//   }
// }

void setup()
{
  Serial.begin(9600);
  delay(1000);
  // RFID.begin(9600);
  
  // pinMode(rele, OUTPUT);

  // //Inicia a comunicacao com o modulo SD
  // if (!SD.begin(CS))
  // {
  //   Serial.println("Fail to connect to MicroSD!\n");
  //   return;
  // }
  // Serial.println("MicroSD Connected!\n");

  Serial.print("Connecting to network: ");
  Serial.println(ssid);
  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA); //init wifi mode
  WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_USERNAME, EAP_ID, EAP_PASSWORD); //without CERTIFICATE, NO ANONYMOUS IDENTITY
  
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(F("."));
  }
  
  Serial.println("");
  Serial.println(F("WiFi is connected!"));
  Serial.println(F("IP address set: "));
  Serial.println(WiFi.localIP()); //print LAN IP

  lcd.begin(16, 2); 
  lcd.clear();    

  lcd.print("Acesso negado");
}

void loop()
{
  /*if(!(RFID.available() > 0))
  {
    delay(500);
    Serial.println("Looking...");
    return;
  }

  char prijateID[14];
  char ID[12];
  
  for(int i = 0; i < 14; i++)
  {
    prijateID[i] = RFID.read();
  }

  if(prijateID[0] != 2 || prijateID[13] != 3)
  {
    return;
  }
  
  for(int i = 1; i < 13; i++)
  {
    ID[i-1] = prijateID[i];
  }
  
  Serial.print("ID: ");
  for(int i = 0; i < 12; i++)
  {
    Serial.print(ID[i]);
  }
  Serial.println();

  RegisterID("/id.txt", ID);

  if(VerifyIDs("/id.txt", ID))
  {
    openValve();
    Serial.println("Access allowed");
  }
  else
  {
    Serial.println("Access denied");
  }

  while(RFID.available() > 0)
  {
    RFID.read();
    Serial.println("Lixo...");
  }*/
}