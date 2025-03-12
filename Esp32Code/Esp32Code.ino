#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

#define CS 5
#define rele 13

SoftwareSerial RFID(17, 16);

void openValve()
{
  digitalWrite(rele, HIGH);
  delay(1000);

  digitalWrite(rele, LOW);
}

void RegisterID(const char *path, const char *id)
{
  File file = SD.open(path, FILE_WRITE);

  if(file)
  {
    file.println(id);
    file.close();
    Serial.printf("Registered ID: ", id);
  } 
  else
  {
    Serial.println("Error opening file %s", path);
  }
}

bool VerifyIDs(const char *path, const char *id)
{
  File file = SD.open(path);
  
  if(file)
  {
    Serial.printf("Searching ID");
    
    while(file.available())
    {
      uint8_t readId[13];
      file.read(readId, 13);
      
      for(int i = 0; i < 12; i++)
      {
        if(readId[i] != id[i])
        {
          break;
        }
        if(i == 11)
        {
          file.close();
          return(true);
        }
      }
    }
    file.close();
    return(false);
  } 
  else
  {
    Serial.println("Error opening file %s", path);
  }
}

void setup()
{
  Serial.begin(9600);
  RFID.begin(9600);
  
  pinMode(rele, OUTPUT);

  //Inicia a comunicacao com o modulo SD
  if (!SD.begin(CS))
  {
    Serial.println("Fail to connect to MicroSD!\n");
    return;
  }
  Serial.println("MicroSD Connected!\n");
}

void loop()
{
  if(!(RFID.available() > 0))
  {
    delay(500);
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

  while(RFID.available() > 0);
  {
    RFID.read();
  }
}