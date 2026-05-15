#ifndef FLIGHT_CPP
#define FLIGHT_CPP
#include "flight.h"

void getAccelData(void){
	IMU.getAccel(&AData);
	AData.accelX = AData.accelX - calib.accelBias[0];
	AData.accelY = AData.accelY - calib.accelBias[1];
	AData.accelZ = AData.accelZ - calib.accelBias[2];

	AData.accelX = (fabs(AData.accelX,ALast.accelX) > tolerance)?((fabs(fround(AData.accelX),AData.accelX) < tolerance)?(fround(AData.accelX)):(AData.accelX)):(ALast.accelX);
	AData.accelY = (fabs(AData.accelY,ALast.accelY) > tolerance)?((fabs(fround(AData.accelY),AData.accelY) < tolerance)?(fround(AData.accelY)):(AData.accelY)):(ALast.accelY);
	AData.accelZ = (fabs(AData.accelZ,ALast.accelZ) > tolerance)?((fabs(fround(AData.accelZ),AData.accelZ) < tolerance)?(fround(AData.accelZ)):(AData.accelZ)):(ALast.accelZ);

	ALast.accelX = AData.accelX;
	ALast.accelY = AData.accelY;
	ALast.accelZ = AData.accelZ;
	AX = AX + AData.accelX;
	AY = AY + AData.accelY;
	AZ = AZ + AData.accelZ;
	samples++;
}

void ShowData(){
	if(samples > 0){
		AX = AX / samples;
		AY = AY / samples;
		AZ = AZ / samples;
	}else{
		AX = AY = AZ = 0.0;
	}

	Serial.print(AX);
	Serial.print(",");
	Serial.print(AY);
	Serial.print(",");
	Serial.println(AZ);
}

int Flight(void){
	IMU.update();
	getAccelData();
	if(millis() - then > 10){
		ShowData();
		AX = AY = AZ = 0.0;
		samples = 0;
		then = millis();
	}

	return 0;
}

#endif