#include <SPI.h>

#include <EthernetServer.h>
#include <EthernetClient.h>
#include <Ethernet.h>

#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x98, 0x91};
byte ip[] = {10, 0, 0, 22};

byte server[] = {10, 0, 0, 3};

int photoRPin = 5; 
int minLight = 0;   
int maxLight = 750;    
int lightLevel;
int adjustedLightLevel;

EthernetClient client;

void setup() 
{
    Ethernet.begin(mac, ip); 
    Serial.begin(9600);
    dht.begin();
}

void loop() 
{  
  DebugSerialValues();
  SendDataToServer(GetTemperatureValue(), GetHumidityValue(), GetLightValue());
  delay (1000);
}

void SendDataToServer(int temperature, int humidity, int light)
{
  if (client.connect(server, 8080)) 
  {
    client.println("GET /temp?value=" + String(temperature) + "&value=" + String(humidity) + "&value=" + String(light) + " HTTP/2.0\n");
  }
  client.stop();
}

int GetLightValue()
{
  lightLevel=analogRead(photoRPin);  
  return adjustedLightLevel = map(lightLevel, minLight, maxLight, 0, 100);
}

int GetTemperatureValue()
{
  return dht.readTemperature();
}

int GetHumidityValue()
{
  return dht.readHumidity();
}

void DebugSerialValues()
{
  Serial.print("\nTemperature: ");
  Serial.println(GetTemperatureValue());
  Serial.print("Humidity: ");
  Serial.println(GetHumidityValue());
  Serial.print("Light: ");
  Serial.println(GetLightValue());
}


