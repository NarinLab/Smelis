#include "ThingSpeak.h"
#include <WiFi.h>
#include <ArduinoLog.h>
#include "header.h"
#include "secret.h"
#include "DHTesp.h"

/* START DEKLARASI VARIABEL GLOBAL */
#define PIN_RAIN_SENSOR 34
#define PIN_LIGHT_SENSOR 35
#define PIN_DHT22 4
/* STOP DEKLARASI VARIABEL GLOBAL */

/* START INSTANSIASI OBJEK GLOBAL */
DHTesp dht22;
WiFiClient client;
/* STOP INSTANSIASI OBJEK GLOBAL */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  networking_setup();
  sensory_setup();
  cloud_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  scheduler_run();
}
