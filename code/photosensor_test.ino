#include <Arduino.h>

#define PHOTOSENSOR_PIN           A1
#define PHOTOSENSOR_TEST_VERSION  "v0.1.2"

#define RL_SEC                1000
#define PHOTOSENSOR_INTERVAL  10 * RL_SEC

uint32_t garduinoTime, lastTimeCheck;
struct Sensors {
    uint8_t light;
} sensorData;

void setup() {
    char output[40];

    Serial.begin(9600);
  
    sprintf(output, "Photosensor Test...%s", PHOTOSENSOR_TEST_VERSION);
    Serial.println(output);

    sprintf(output, "Sensor on pin %s", PHOTOSENSOR_PIN);
    Serial.println(output);
    pinMode(PHOTOSENSOR_PIN, INPUT_PULLUP);

    lastTimeCheck = -PHOTOSENSOR_INTERVAL;
    Serial.println("Photosensor ready.");
}

void loop() {
    char output[40];
  
    delay(2000);
    garduinoTime = millis();

    if ((garduinoTime - lastTimeCheck) > PHOTOSENSOR_INTERVAL) {
        Serial.print("Checking light levels.");
        sensorData.light = analogRead(PHOTOSENSOR_PIN);
        Serial.print(".\n");

        sprintf(output, "Light Reading: %d", sensorData.light);
        Serial.println(output);
    }
}

