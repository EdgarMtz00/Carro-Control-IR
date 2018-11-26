#include <IRremote.h>

const int pinRec=13;
const int pinVel=1;
const int M1Izq=3;	//avanzar		derecha
const int M1Der=4;	//retroceder
const int M2Izq=5;	//avanzar		izquierda
const int M2Der=6;	//retroceder

IRrecv receptor(pinRec);
decode_results resultados;
unsigned long valorPrev;

bool encendido = false;
bool marcha = false;
bool reversa = false;
int vel=0;
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

void arrancar(){
	if(encendido & marcha){
		digitalWrite(M1Izq,LOW);
		digitalWrite(M1Der,LOW);
		digitalWrite(M2Izq,LOW);
		digitalWrite(M2Der,LOW);
		marcha = false;
	}else if(!marcha){
		digitalWrite(M1Izq,HIGH);
		digitalWrite(M1Der,LOW);
		digitalWrite(M2Izq,HIGH);
		digitalWrite(M2Der,LOW);
		marcha = true;
	}
}

void subirVel(){
	if(encendido & vel<3){
		vel++
	}
	analogWrite(pinVel, velocidades[vel]);
}

void bajarVel(){
	if(encedido & vel!=0){
		vel--;	
	}
	analogWrite(pinVel, velocidades[vel]);
}

void girar(bool dir){ //0 derecha | 1 izquierda
	if(encendido & !reversa){
		digitalWrite(M1Izq, !dir);
		digitalWrite(M2Izq, dir);
	}else if(reversa){
		digitalWrite(M1Der, dir);
		digitalWrite(M2Der, !dir);
	}
}

void loop(){
	if(receptor.decode(&resultados)){
		if(resultado.value == 0XFFFFFF){
			reultado.value = valorPrev; 
		}
		switch(resultado.value){
			case 0xFFA25D: //Power
				encender();
				break;
			case 0xFF02FD: //Play
				arrancar();
				break;
			case 0xFF629D: //Vol+
				subirVel();
				break;
			case 0xFFA857: //Vol-
				bajarVel();
				break;
			case 0XFFC23D: //Next
				girar(0);
				break;
			case 0xFF22DD: //Prev
				girar(1);
				break;
			case 0xFF906F: //up
				cambiarSentido();
				break;
			case 
			default:
				break;
		}
		valorPrev = resultado.value;
		receptor.resume();
	}
}
