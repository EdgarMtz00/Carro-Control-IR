#include <IRremote.h>

const int pinRec=13;

IRrecv receptor(pinRec);
decode_results *resultados;

void setup(){
	Serial.begin(9600);
	repceptor.enableIRIn();
	Serial.println("Receptor habilitado...");
}

void loop(){
	if(receptor.decode(&resultados)){
		Serial.println(resultados.value,HEX);
		receptor.resume();
	}
	delay(500);
	
}