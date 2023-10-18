****************************************
* Include Libraries
****************************************/
#include <WiFi.h>
#include <PubSubClient.h>
/****************************************
* Define Constants
****************************************/
#define WIFISSID "IoT" //WIFI SSID aqui
#define PASSWORD "1t3s0IoT23" // WIFI pwd
#define TOKEN "BBFF-L3jp69fcTPNAv3KvNglR9VUF8fNbgv" // Ubidots TOKEN ID el mismo que usamos en clase lo sacan de Ubidtos
#define MQTT_CLIENT_NAME "123456AbCde" //ID del cliente, 8 a 12 chars alfanumericos (ASCII), debe ser random y unico dif a otros devices
#define VARIABLE_LABEL_temp "temperatura" // Variable Temperatura
#define VARIABLE_LABEL_hum "humedad" // Variable Humedad
#define DEVICE_LABEL "MQTT-Publish-esp32" // Nombre del dispositivo a crear
char mqttBroker[]= "industrial.api.ubidots.com";
char payload[200]; // Leer y entender el payload aqui una de tantas referencias https://techterms.com/definition/payload
char topic[150]; //Espacio para el nombre del topico
// Space to store values to send
char str_temp[10];
char str_hum[10];
#include "DHT.h"
#define pin1 15
DHT dht1(pin1, DHT11); //El sensor de temp y humedad azul.
/****************************************
* Funciones auxiliares
****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);
void callback(char* topic, byte* payload, unsigned int length) {
char p[length + 1];
memcpy(p, payload, length);
p[length] = NULL;
String message(p);
Serial.write(payload, length);
Serial.println(topic);
}
void reconnect() {
// Loop until we're reconnected
while (!client.connected()) {
Serial.println("Attempting MQTT connection...");
// Attemp to connect
if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
Serial.println("Connected");
} else {
Serial.print("Failed, rc=");
Serial.print(client.state());
Serial.println(" try again in 2 seconds");
// Wait 2 seconds before retrying
delay(2000);
}
}
}
