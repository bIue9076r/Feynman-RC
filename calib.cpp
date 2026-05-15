#ifndef CALIB_CPP
#define CALIB_CPP
#include "calib.h"

int Calibrate(void){
	if(IMU.init(calib)){
		Serial.println("Error");
		return 1;
	}

	IMU.calibrateAccelGyro(&calib);
	Serial.println("");
	Serial.print("Accel Bias: ");
	Serial.print(calib.accelBias[0]);
	Serial.print("\t");
	Serial.print(calib.accelBias[1]);
	Serial.print("\t");
	Serial.print(calib.accelBias[2]);
	Serial.print("\n");

	return 0;
}

#endif