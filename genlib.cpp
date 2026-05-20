#ifndef GENLIB_CPP
#define GENLIB_CPP
#include "genlib.h"

int Stage = 0;
int Pre_Flight_Complete = 0;
int Calibration_Complete = 0;
int Flight_Complete = 0;

int NoIMU = 0;
int NoBMP = 0;

File dataFile;

MPU6500 IMU;
calData calib = {0};
AccelData AData;
AccelData ALast;
float AX = 0.0;
float AY = 0.0;
float AZ = 0.0;
int accel_samples = 0;
unsigned long accel_then;
float accel_tolerance = 0.1;

Adafruit_BMP085 BMP;
BaroData BData = {0.0,0.0};
unsigned long baro_then;

void Abort(void){
	pinMode(LED_BUILTIN, OUTPUT);
	for(;;){
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
	}
}

float fabs(float a, float b){
	float r = (a - b);
	return (r < 0)?(-r):(r);
}

int fround(float a){
	int ia = a;
	return (a - ia < 0.5)?(ia):(ia + 1);
}

#endif