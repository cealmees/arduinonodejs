#include <SPI.h>

#include <EthernetUdp.h>
#include <Dns.h>
#include <EthernetServer.h>
#include <Dhcp.h>
#include <EthernetClient.h>
#include <Ethernet.h>

#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x98, 0x91};

// Definimos la Dirección IP del Servidor Node.js
byte server[] = {10, 0, 0, 3};

// Definimos la Dirección IP del Arduino
byte ip[] = {10, 0, 0, 22};

int photoRPin = 5; 
int minLight = 0;          //Used to calibrate the readings
int maxLight = 750;          //Used to calibrate the readings
int lightLevel;
int adjustedLightLevel;


EthernetClient client;

// Definimos la variable donde almacenaremos la respuesta del servidor.
String response = String(10);
// Definimos el separador del mensaje
char separator = '|';
// Utilizaremos esta variable para verificar si la lectura de la respuesta ha comenzado
boolean started = false;

void setup() {
    Ethernet.begin(mac, ip); // Iniciamos el Ethernet Shield
    Serial.begin(9600);
    dht.begin();
}

void loop() {  

if (client.connect(server, 8080)) {
    // Enviamos la peticion GET utilizando el protocolo HTTP
    client.println("GET /temp?value=" + String(GetTemperatureValue()) + "&value=" + String(GetHumidityValue()) + "&value=" + String(GetLightValue()) + " HTTP/2.0");
    client.println();

    // A continuación realizaremos la lectura de la respuesta desde el servidor
    // En este caso solo vamos a hacer lectura mientras estemos conectados
    // Luego de leer la respuesta completa desconectamos el cliente
    while (client.connected()) {
      // Solo realizaremos la lectura de la respuesta si el cliente tiene
      // algo para nosotros
      if (client.available()) {
        // Debemos leer caracter por caracter
        char c = client.read();

        // En el siguiente bloque de código utilizaremos el separador `|` para
        // verificar cuando empieza y termina el mensaje que necesitamos
        if (c != separator && started) {
          response += c;
        } else if (c == separator && !started) {
          started = true;
        } else if (c == separator && started) {
          started = false;
          client.stop();
        }
      }
    }
response = "";

delay (500);
Serial.println ();
}
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

