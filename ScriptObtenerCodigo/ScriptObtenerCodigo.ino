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

/* CODIGOS //////////////////////////////////
PWR  	0xFFA25D
VOL+ 	0xFF629D
FUNC 	0xFFE21D
PREV 	0xFF22DD
PLAY 	0xFF02FD
NEXT 	0XFFC23D
DOWN 	0xFFE01F
VOL- 	0xFFA857
UP   	0xFF906F
0		0xFF6897
EQ		0xFF9867
REPT 	0xFFB04F
1		0xFF30CF
2		0xFF18E7
3		0xFF7A85
4		0xFF10EF
5		0xFF38C7
6		0xFF5AA5
7		0xFF42BD
8		0xFF4AB5
9		0xFF52AD
/////////////////////////////////////// */

