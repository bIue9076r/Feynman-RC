#include <SD.h>
#include <FastIMU.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include "genlib.h"
#include "calib.h"
#include "flight.h"
#include "recovery.h"

void setup() {
	Wire.begin();
	#ifdef SEND_SIG
	Serial.begin(9600);
	#endif
}

void loop(){
	int status = 0;
	switch(Stage){
		case 0:	// Pre Launch
			Pre_Launch_Complete = 1;
			if(Pre_Launch_Complete){
				Stage = 1;	// Skip Launch prep
			}
		break;

		case 1: // Calibration
			status = Calibrate();
			Calibration_Complete = 1;
			if(Calibration_Complete){
				Stage = 2;
			}
		break;

		case 2:	// Pre Flight
			Pre_Flight_Complete = 1;
			pinMode(LIGHT_PIN, OUTPUT);
			digitalWrite(LIGHT_PIN, HIGH);
			delay(LIGHT_DELAY);
			digitalWrite(LIGHT_PIN, LOW);
			if(Pre_Flight_Complete){
				Stage = 3;
			}
		break;

		case 3:	// Flight
			status = Flight();

			if(Flight_Complete){
				Stage = 4;
			}
		break;

		case 4:	// Recovery
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
