#ifndef GENLIB_H
#define GENLIB_H
#include <FastIMU.h>

extern int Stage;
extern int Pre_Flight_Complete;
extern int Calibration_Complete;
extern int Flight_Complete;

extern MPU6500 IMU;
extern calData calib;
extern AccelData AData;
extern AccelData ALast;
extern float AX;
extern float AY;
extern float AZ;
extern int samples;
extern long long then;

extern float tolerance;

void Abort(void);
float fabs(float a, float b);
int fround(float a);

#endif