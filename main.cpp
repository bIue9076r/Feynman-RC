#include <Arduino.h>

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
	delay(1000);
	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
	digitalWrite(LED_BUILTIN, HIGH);
}

int main(void){
	init();
	setup();

	for(;;){
		loop();
	}

	return 0;
}
