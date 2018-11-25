#include <IRremote.h>

const int pinRec=13;
const int pinVel=1;
const int M1Izq=3;	//avanzar
const int M1Der=4;	//retroceder
const int M2Izq=5;	//avanzar
const int M2Der=6;	//retroceder

IRrecv receptor(pinRec);
decode_results resultados;
unsigned long valorPrev;

bool encendido = false;
int velocidades[4] = {141, 179, 217, 255};

void setup(){
	Serial.begin(9600);
	receptor.enableIRIn();
	Serial.println("Receptor habilitado...");
	digitalWrite(M1Izq,LOW);
	digitalWrite(M1Der,LOW);
	digitalWrite(M2Izq,LOW);
	digitalWrite(M2Der,LOW);
}

void encender(){
	if(encendido){
		digitalWrite(M1Izq,LOW);
		digitalWrite(M1Der,LOW);
		digitalWrite(M2Izq,LOW);
		digitalWrite(M2Der,LOW);	
	}
	encendido = !encendido;
	analogWrite(pinVel, velocidades[0]);
}

void loop(){
	if(receptor.decode(&resultados)){
		if(resultado.value == 0XFFFFFF){
			reultado.value = valorPrev; 
		}
		switch(resultado.value){
			case 0xFFA25D: //Arrancar/Apagar
				encender();
		}
	}
}
