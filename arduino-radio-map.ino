#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include "GeoDTMF.h"
#include "DTMFPlayer.h"

TinyGPS GPS;
SoftwareSerial SerialGPS(8, 9);

const int PIN_OPEN = 12;
const int PIN_LED = 13;

float latitude;
float longitude;

void setup() {
  pinMode(PIN_OPEN, INPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_LED, LOW);
  Serial.begin(9600);
  delay(250);
  Serial.println("Ready.");
}

void loop() {
  if (digitalRead(PIN_OPEN)) {
    powerGPS(false);
    String encodedMessage = encodeDTMF(latitude, longitude);
    playMessage(encodedMessage);
    powerGPS(true);
  } else {
    while (SerialGPS.available() > 0) {
        int data = SerialGPS.read();
        if (GPS.encode(data)) {
            GPS.f_get_position(&latitude, &longitude);
            powerLED(true);
            Serial.println(latitude);
            Serial.println(longitude);
        }
    }
  }
}

void powerGPS(bool power) {
  if (power) {
    SerialGPS.begin(9600);
  } else {
    SerialGPS.end();
  }
}

void powerLED(bool power) {
  if (power) {
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }
}

