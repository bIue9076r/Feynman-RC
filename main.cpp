#include <SD.h>
#include <FastIMU.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include "genlib.h"
#include "calib.h"
#include "flight.h"
#include "recovery.h"

void setup() {
	// SD.begin();
	Wire.begin();
	Serial.begin(9600);

	unsigned long long now = millis();
	accel_then = now;
	baro_then = now;
}

void loop(){
	int status = 0;
	switch(Stage){
		case 0:	// Pre Launch
			Pre_Flight_Complete = 1;
			if(Pre_Flight_Complete){
				Stage = 1;	// Skip Launch prep
			}
		break;

		case 1: // Calibration
			status = Calibrate();

			// wait for signal
			Calibration_Complete = 1;
			if(Calibration_Complete){
				Stage = 2;
			}
		break;

		case 2:	// Flight
			status = Flight();

			if(Flight_Complete){
				Stage = 3;
			}
		break;

		case 3:	// Recovery
			status = Recovery();
		break;
	}

	if(status){
		Abort();
	}
}

int main(void){
	init();
	setup();

	for(;;){
		loop();
	}

	return 0;
}
