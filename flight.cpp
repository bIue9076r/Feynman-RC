#ifndef FLIGHT_CPP
#define FLIGHT_CPP
#include "flight.h"

void getAccelData(void){
	IMU.getAccel(&AData);
	AData.accelX = AData.accelX - calib.accelBias[0];
	AData.accelY = AData.accelY - calib.accelBias[1];
	AData.accelZ = AData.accelZ - calib.accelBias[2];

	AData.accelX = (fabs(AData.accelX,ALast.accelX) > accel_tolerance)?((fabs(fround(AData.accelX),AData.accelX) < accel_tolerance)?(fround(AData.accelX)):(AData.accelX)):(ALast.accelX);
	AData.accelY = (fabs(AData.accelY,ALast.accelY) > accel_tolerance)?((fabs(fround(AData.accelY),AData.accelY) < accel_tolerance)?(fround(AData.accelY)):(AData.accelY)):(ALast.accelY);
	AData.accelZ = (fabs(AData.accelZ,ALast.accelZ) > accel_tolerance)?((fabs(fround(AData.accelZ),AData.accelZ) < accel_tolerance)?(fround(AData.accelZ)):(AData.accelZ)):(ALast.accelZ);

	ALast.accelX = AData.accelX;
	ALast.accelY = AData.accelY;
	ALast.accelZ = AData.accelZ;
	AX = AX + AData.accelX;
	AY = AY + AData.accelY;
	AZ = AZ + AData.accelZ;
	accel_samples++;
}

void getBaroData(void){
	BData.pressure = BData.pressure + BMP.readPressure();
	BData.altitude = BData.altitude + BMP.readAltitude();
}

void ShowAccelData(){
	if(accel_samples > 0){
		AX = AX / accel_samples;
		AY = AY / accel_samples;
		AZ = AZ / accel_samples;
	}else{
		AX = AY = AZ = 0.0;
	}

	Serial.print("A: ");
	Serial.print(AX);
	Serial.print(",");
	Serial.print(AY);
	Serial.print(",");
	Serial.println(AZ);
}

void ShowBaroData(void){
	Serial.print("B: ");
	Serial.print(BData.pressure);
	Serial.print(",");
	Serial.println(BData.altitude);
}

int Flight(void){
	if(!NoIMU){
		IMU.update();
		getAccelData();
	}

	unsigned long long now = millis();

	if(!NoIMU){
		if(now - accel_then > 10){
			ShowAccelData();
			AX = AY = AZ = 0.0;
			accel_samples = 0;
			accel_then = now;
		}
	}

	if(!NoBMP){
		if(now - baro_then > 10){
			getBaroData();
			ShowBaroData();
			BData.pressure = BData.altitude = 0.0;
			baro_then = now;
		}
	}

	return 0;
}

#endif