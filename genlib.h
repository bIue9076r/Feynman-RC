#ifndef GENLIB_H
#define GENLIB_H
#include <SD.h>
#include <FastIMU.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>

// #define SEND_SIG
#define ACCEL_PATH "ACCEL.DAT"
#define BAROM_PATH "BAROM.DAT"

extern int Stage;
extern int Pre_Launch_Complete;
extern int Calibration_Complete;
extern int Pre_Flight_Complete;
extern int Flight_Complete;

extern int NoIMU;
extern int NoBMP;

extern File dataFile;

extern MPU6500 IMU;
extern calData calib;
extern AccelData AData;
extern AccelData ALast;
extern float AX;
extern float AY;
extern float AZ;
extern int accel_samples;
extern unsigned long accel_then;
extern float accel_tolerance;

extern Adafruit_BMP085 BMP;

typedef struct {
	float pressure;
	float altitude;
} BaroData;

extern BaroData BData;
extern unsigned long baro_then;

void Abort(void);
float fabs(float a, float b);
int fround(float a);

#define LIGHT_PIN 2
#define LIGHT_DELAY (5*1000)

#define ACCEL_DELAY 10
#define BARO_DELAY 10

#endif