#include <IRremote.h>

int pinRec=13;

IRrecv receptor(pinRec);
decode_results *resultados;

void setup(){
	Serial.begin(9600);
	receptor.enableIRIn();
	Serial.println("Receptor habilitado...");
}

void loop(){
	
}
