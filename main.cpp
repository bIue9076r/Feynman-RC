#include <EEPROM.h>
#include <FastIMU.h>
#include <Arduino.h>


void setup() {
	Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.print("EEPROM Size: ");
	Serial.println(EEPROM.length());
}

void loop(){
	
}

int main(void){
	init();
	setup();

	for(;;){
		loop();
	}

	return 0;
}
