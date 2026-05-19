#ifndef GENLIB_H
#define GENLIB_H
#include <SD.h>
#include <FastIMU.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>

extern int Stage;
extern int Pre_Flight_Complete;
extern int Calibration_Complete;
extern int Flight_Complete;

extern int NoIMU;
extern int NoBMP;

extern MPU6500 IMU;
extern calData calib;
extern AccelData AData;
extern AccelData ALast;
extern float AX;
extern float AY;
extern float AZ;
extern int accel_samples;
extern long long accel_then;
extern float accel_tolerance;

extern Adafruit_BMP085 BMP;

typedef struct {
	float pressure;
	float altitude;
} BaroData;

extern BaroData BData;
extern long long baro_then;

void Abort(void);
float fabs(float a, float b);
int fround(float a);

#endif