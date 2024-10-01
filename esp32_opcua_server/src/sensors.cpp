#include "sensors.h"
#include "opcua_esp32.h"
#include <string>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MSA301.h>
#include <Adafruit_Sensor.h>
#include <math.h>
#include <stdio.h>
#include "LSM303C.h"

// Define GPIO pin numbers for SDA and SCL
const int sdaPin = 21; // Example GPIO pin for SDA
const int sclPin = 22; // Example GPIO pin for SCL

// msa311 accelerometer
Adafruit_MSA311 msa;

void setupmsa311()
{
    while (!Serial)
        delay(10); // will pause Zero, Leonardo, etc until serial console opens

    Serial.println("Adafruit MSA301 test!");

    // Try to initialize!
    if (!msa.begin())
    {
        Serial.println("Failed to find MSA301 chip");
        while (1)
        {
            delay(10);
        }
    }
    Serial.println("MSA301 Found!");
}

float sensorReadingAccelX()
{
    /* Get a new sensor event, normalized */ 
    sensors_event_t event; 
    msa.getEvent(&event);

    int x_adc_value;

    x_adc_value = event.acceleration.x; /* Digital value of voltage on x_out pin */
    return x_adc_value;
}
float sensorReadingAccelY()
{
     /* Get a new sensor event, normalized */ 
    sensors_event_t event; 
    msa.getEvent(&event);

    int x_adc_value;

    x_adc_value = event.acceleration.y; /* Digital value of voltage on x_out pin */
    return x_adc_value;
}
float sensorReadingAccelZ()
{
     /* Get a new sensor event, normalized */ 
    sensors_event_t event; 
    msa.getEvent(&event);

    int x_adc_value;

    x_adc_value = event.acceleration.z; /* Digital value of voltage on x_out pin */
    return x_adc_value;
}