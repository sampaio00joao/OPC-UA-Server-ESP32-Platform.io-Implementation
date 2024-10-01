#ifndef SENSORS_H
#define SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

// Function prototypes
void setupmsa311();
float sensorReadingAccelX();
float sensorReadingAccelY();
float sensorReadingAccelZ();

#ifdef __cplusplus
}
#endif

#endif // SENSORS_H