#ifndef CALIB_CPP
#define CALIB_CPP
#include "calib.h"

int Calibrate(void){
	unsigned long long now = millis();
	accel_then = now;
	baro_then = now;

	if(!SD.begin()){
		#ifdef SEND_SIG
		Serial.println("SD Card Error");
		#endif
		return 1;
	}

	if(SD.exists(ACCEL_PATH)){
		SD.remove(ACCEL_PATH);
	}

	if(SD.exists(BAROM_PATH)){
		SD.remove(BAROM_PATH);
	}

	if(IMU.init(calib)){
		#ifdef SEND_SIG
		Serial.println("Accelerometer Error");
		#endif
		NoIMU = 1;
	}

	if(!NoIMU){
		IMU.calibrateAccelGyro(&calib);
		#ifdef SEND_SIG
		Serial.println("");
		Serial.print("Accel Bias: ");
		Serial.print(calib.accelBias[0]);
		Serial.print("\t");
		Serial.print(calib.accelBias[1]);
		Serial.print("\t");
		Serial.print(calib.accelBias[2]);
		Serial.print("\n");
		#endif

		dataFile = SD.open(ACCEL_PATH, FILE_WRITE);
		dataFile.print("Accel Bias: ");
		dataFile.print(calib.accelBias[0]);
		dataFile.print("\t");
		dataFile.print(calib.accelBias[1]);
		dataFile.print("\t");
		dataFile.println(calib.accelBias[2]);
		dataFile.close();
	}

	if(!BMP.begin()){
		#ifdef SEND_SIG
		Serial.println("Barometer Error");
		#endif
		NoBMP = 1;
	}

	if(NoIMU && NoBMP){
		return 1;
	}

	return 0;
}

#endif