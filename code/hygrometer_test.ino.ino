#include <Arduino.h>

#define HYGROMETER_SENSOR_PIN   A0
#define HYGROMETER_VOLTAGE_PIN  13
#define HYGROMETER_TEST_VERSION "v0.1.3"

#define RL_SEC              1000
#define HYGROMETER_INTERVAL 60 * RL_SEC

uint32_t garduinoTime, lastTimeCheck;
struct Sensors {
    uint8_t moisture;  
} sensorData;

void setup() {
    char output[40];
    
    Serial.begin(9600);    

    sprintf(output, "Hygrometer Test...%s", HYGROMETER_TEST_VERSION);
    Serial.println(output);
    
    sprintf(output, "Sensor on pin %s", HYGROMETER_SENSOR_PIN);
    Serial.println(output);
    pinMode(HYGROMETER_SENSOR_PIN, INPUT_PULLUP);
    
    sprintf(output, "Voltage on pin %d", HYGROMETER_VOLTAGE_PIN);
    Serial.println(output);
    pinMode(HYGROMETER_VOLTAGE_PIN, OUTPUT);
    
    lastTimeCheck = -HYGROMETER_INTERVAL;
    Serial.println("Hygrometer ready.");
}

void loop() {
    char output[40];

    delay(2000);
    garduinoTime = millis();

    if ((garduinoTime - lastTimeCheck) > HYGROMETER_INTERVAL) {
        Serial.print("Checking moisture levels");
        digitalWrite(HYGROMETER_VOLTAGE_PIN, HIGH);
        Serial.print(".");
        delay(20);
        sensorData.moisture = analogRead(HYGROMETER_SENSOR_PIN);
        Serial.print(".");
        digitalWrite(HYGROMETER_VOLTAGE_PIN, LOW);
        Serial.print(".\n");
        
        sprintf(output, "Moisture Reading: %d", sensorData.moisture);
        Serial.println(output);
    }
}

