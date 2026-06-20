#include "SD.h"
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

void ShowAccelData(unsigned long n){
	if(accel_samples > 0){
		AX = AX / accel_samples;
		AY = AY / accel_samples;
		AZ = AZ / accel_samples;
	}else{
		AX = AY = AZ = 0.0;
	}

	#ifdef SEND_SIG
	Serial.print("A: ");
	Serial.print(n);
	Serial.print(", ");
	Serial.print(AX);
	Serial.print(",");
	Serial.print(AY);
	Serial.print(",");
	Serial.println(AZ);
	#endif

	SaveAccelData(n, AX, AY, AZ);
}

void ShowBaroData(unsigned long n){
	#ifdef SEND_SIG
	Serial.print("B: ");
	Serial.print(n);
	Serial.print(", ");
	Serial.print(BData.pressure);
	Serial.print(",");
	Serial.println(BData.altitude);
	#endif

	SaveBaroData(n, BData.pressure, BData.altitude);
}

void SaveAccelData(unsigned long n, float x, float y, float z){
	dataFile = SD.open(ACCEL_PATH, FILE_WRITE);
	if(dataFile){
		dataFile.print(n);
		dataFile.print(", ");
		dataFile.print(x);
		dataFile.print(",");
		dataFile.print(y);
		dataFile.print(",");
		dataFile.println(z);
	}
	dataFile.close();
}

void SaveBaroData(unsigned long n, float p, float a){
	dataFile = SD.open(BAROM_PATH, FILE_WRITE);
	if(dataFile){
		dataFile.print(n);
		dataFile.print(", ");
		dataFile.print(p);
		dataFile.print(",");
		dataFile.println(a);
	}
	dataFile.close();
}

int Flight(void){
	if(!NoIMU){
		IMU.update();
		getAccelData();
	}

	unsigned long now = millis();

	if(!NoIMU){
		if(now - accel_then > ACCEL_DELAY){
			ShowAccelData(now);
			AX = AY = AZ = 0.0;
			accel_samples = 0;
			accel_then = now;
		}
	}

	if(!NoBMP){
		if(now - baro_then > BARO_DELAY){
			getBaroData();
			ShowBaroData(now);
			BData.pressure = BData.altitude = 0.0;
			baro_then = now;
		}
	}

	return 0;
}

#endif