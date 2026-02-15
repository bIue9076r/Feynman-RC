#include <Arduino.h>
#include <Wire.h>

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Wire.begin();
	Serial.begin(9600);
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
