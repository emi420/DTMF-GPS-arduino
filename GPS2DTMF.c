#include <dtmfgen.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

DTMFGenerator DTMF;
TinyGPS GPS;
SoftwareSerial SerialGPS(8, 9);

const int WAIT_DELAY = 100;
const int PLAY_LENGTH = 175;
const char SEPARATOR = '#';
const int PIN_OPEN = 12;
const int PIN_LED = 13;
// const int PIN_PTT = 11;

float latitude;
float longitude;

void setup() {
  pinMode(PIN_OPEN, INPUT);
  pinMode(PIN_LED, OUTPUT);
  // pinMode(PIN_PTT, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_LED, LOW);
  Serial.begin(9600);
  delay(250);
  Serial.println("Ready.");
}

void loop() {
  if (digitalRead(PIN_OPEN)) {
    powerGPS(false);
    playCoordinates(latitude, longitude);
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

void playCoordinates(float latitude, float longitude) {
    DTMF.generate(SEPARATOR, PLAY_LENGTH);
    Serial.print(SEPARATOR);
    delay(WAIT_DELAY);
    playCoordinate(longitude);
    playCoordinate(latitude);
}

void playCoordinate(float coordinate) {
  String coordinateString = String((coordinate + 180) * 1000);
  Serial.println(coordinateString);
  for (int i = 0; i < coordinateString.length(); i++) {
    char character = coordinateString.charAt(i);
    if (character == '.') {
      break;
    }
    DTMF.generate(character, PLAY_LENGTH);
    Serial.print(character);
    delay(WAIT_DELAY);
    if (character == coordinateString.charAt(i + 1)) {
      DTMF.generate(SEPARATOR, PLAY_LENGTH);
      Serial.print(SEPARATOR);
      delay(WAIT_DELAY);
    }
  }
  Serial.println(" ");
}
