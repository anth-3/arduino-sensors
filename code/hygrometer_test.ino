/******************************************************************************
* File: hygrometer.ino                                                        *
* Description: This Arduino Sketch tests a hygrometer module to ensure the    *
*     module is detecting moisture levels, that all input pins work           *
*     correctly, and that it correctly detects changes in moisture levels as  *
*     Arduino and module are moved to different types of soil/water           *
      combinations.                                                           *
* Author: Trey Holdener <trey@atthelamppost.net>                              *
* Copyright: (c) 2016 At the Lamppost.                                        *
* License: MIT License (see LICENSE)                                          *
******************************************************************************/

#include <Arduino.h>

#define HYGROMETER_SENSOR_PIN       A0          // Module will listen on Analog Pin 0
#define HYGROMETER_SENSOR_PIN_STR   "A0"
#define HYGROMETER_VOLTAGE_PIN      13          // Voltage will be controlled on Digital Pin 13
#define HYGROMETER_TEST_VERSION     "v0.1.3"    // Version of this test sketch

#define RL_SEC              1000            // Number of milliseconds in a second
#define HYGROMETER_INTERVAL 60 * RL_SEC     // Interval in milliseconds between moisture readings

uint32_t lastTimeCheck;     // The time of the last check in the loop()
struct Sensors {            // Struct to hold the sensor data
    uint8_t moisture;  
} sensorData;

/* Do all of the setup stuff here */
void setup() {
    char buf[40];    // This is our output buffer
    
    Serial.begin(9600);

    sprintf(buf, "Hygrometer Test...%s", HYGROMETER_TEST_VERSION);
    Serial.println(output);
    
    sprintf(buf, "Sensor on pin %s", HYGROMETER_SENSOR_PIN_STR);
    Serial.println(buf);
    /* Setup the pin to listen for data on */
    pinMode(HYGROMETER_SENSOR_PIN, INPUT_PULLUP);
    
    sprintf(buf, "Voltage on pin %d", HYGROMETER_VOLTAGE_PIN);
    Serial.println(buf);
    /* 
     * Setup the pin to send power to. By using a digital pin instead of the 
     * voltage pin, we can control when the power is on and off for this 
     * individual sensor. 
     */
    pinMode(HYGROMETER_VOLTAGE_PIN, OUTPUT);
    
    /* Initialize the time check for a guaranteed check first time in the loop */
    lastTimeCheck = -HYGROMETER_INTERVAL;
    Serial.println("Hygrometer ready.");

    /* Take a deep breath before starting */
    delay(3000);
}

/* Do this over and over and over and over... */
void loop() {
    char output[40];        // This is our output buffer
    uint32_t garduinoTime;  // The current time on the Arduino

    /* 
     * Since we are looking at particular intervals, the Arduino does not need
     * to be constantly looping, so give it a small break.
     */
    delay(2000);
    garduinoTime = millis();

    /* Should we query the hygrometer for data yet? */
    if ((garduinoTime - lastTimeCheck) > HYGROMETER_INTERVAL) {
        Serial.print("Checking moisture levels");
        /* Turn on the hygrometer sensor */
        digitalWrite(HYGROMETER_VOLTAGE_PIN, HIGH);
        Serial.print(".");
        delay(20);
        sensorData.moisture = analogRead(HYGROMETER_SENSOR_PIN);
        Serial.print(".");
        /* Turn off the hygrometer sensor */
        digitalWrite(HYGROMETER_VOLTAGE_PIN, LOW);
        Serial.print(".\n");
        
        sprintf(output, "Moisture Reading: %d", sensorData.moisture);
        Serial.println(output);
    }

    lastTimeCheck = garduinoTime;
}
