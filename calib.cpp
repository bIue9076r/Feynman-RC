#ifndef CALIB_CPP
#define CALIB_CPP
#include "calib.h"

int Calibrate(void){
	if(IMU.init(calib)){
		Serial.println("Accelerometer Error");
		NoIMU = 1;
	}

	if(!NoIMU){
		IMU.calibrateAccelGyro(&calib);
		Serial.println("");
		Serial.print("Accel Bias: ");
		Serial.print(calib.accelBias[0]);
		Serial.print("\t");
		Serial.print(calib.accelBias[1]);
		Serial.print("\t");
		Serial.print(calib.accelBias[2]);
		Serial.print("\n");
	}

	if(!BMP.begin()){
		Serial.println("Barometer Error");
		NoBMP = 1;
	}

	if(NoIMU && NoBMP){
		return 1;
	}

	return 0;
}

#endif