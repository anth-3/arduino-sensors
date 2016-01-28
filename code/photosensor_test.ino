/******************************************************************************
* File: photosensor_test.ino                                                  *
* Description: This Arduino Sketch tests a light intensity module to ensure   *
*     the module is detecting light levels, that all input pins work          *
*     correctly, and that it correctly detects changes in light levels as the *
*     Arduino and module are moved to different levels of light.              *
* Author: Trey Holdener <trey@atthelamppost.net>                              *
* Copyright: (c) 2016 At the Lamppost.                                        *
* License: MIT License (see LICENSE)                                          *
******************************************************************************/

#include <Arduino.h>

#define PHOTOSENSOR_PIN             A1        // Module will listen on Analog Pin 1
#define PHOTOSENSOR_PIN_STR         "A1"
#define PHOTOSENSOR_TEST_VERSION    "v0.1.3"  // Version of this test sketch

#define RL_SEC                1000          // Number of milliseconds in a second
#define PHOTOSENSOR_INTERVAL  10 * RL_SEC   // Interval in milliseconds between photocell readings

uint32_t lastTimeCheck;     // The time of the last check in the loop()
struct Sensors {            // Struct to hold the sensor data
    uint8_t light;
} sensorData;

/* Do all of the setup stuff here */
void setup() {
    char buf[40];    // This is our output buffer

    Serial.begin(9600);
  
    sprintf(buf, "Photosensor Test...%s", PHOTOSENSOR_TEST_VERSION);
    Serial.println(buf);

    sprintf(buf, "Sensor on pin %s", PHOTOSENSOR_PIN_STR);
    Serial.println(buf);
    /* Setup the pin to listen for data on */
    pinMode(PHOTOSENSOR_PIN, INPUT_PULLUP);

    /* Initialize the time check for a guaranteed check first time in the loop */
    lastTimeCheck = -PHOTOSENSOR_INTERVAL;
    Serial.println("Photosensor ready.");

    /* Take a deep breath before starting */
    delay(3000);
}

/* Do this over and over and over and over... */
void loop() {
    char buf[40];           // This is our output buffer
    uint32_t garduinoTime;  // The current time on the Arduino
  
    /* 
     * Since we are looking at particular intervals, the Arduino does not need
     * to be constantly looping, so give it a small break.
     */
    delay(2000);
    garduinoTime = millis();

    /* Should we query the photocell for data yet? */
    if ((garduinoTime - lastTimeCheck) > PHOTOSENSOR_INTERVAL) {
        Serial.print("Checking light levels.");
        sensorData.light = analogRead(PHOTOSENSOR_PIN);
        Serial.print(".\n");

        sprintf(buf, "Light Reading: %d", sensorData.light);
        Serial.println(buf);
    }

    lastTimeCheck = garduinoTime;
}
