#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

int pinRec=13;

IRrecv receptor(pinRec);
decode_results resultados;

void setup(){
	Serial.begin(9600);
	receptor.enableIRIn();
	Serial.println("Receptor habilitado...");
}

void loop(){
	if(receptor.decode(&resultados)){
		Serial.println(resultados.value,HEX);
		receptor.resume();
	}
	delay(500);
}
