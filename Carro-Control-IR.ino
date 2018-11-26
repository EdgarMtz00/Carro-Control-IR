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
	if(encendido){
		if(marcha){
			digitalWrite(M1Izq,LOW);
			digitalWrite(M1Der,LOW);
			digitalWrite(M2Izq,LOW);
			digitalWrite(M2Der,LOW);
			marcha = false;
		}else if(!reversa){
			digitalWrite(M1Izq,HIGH);
			digitalWrite(M1Der,LOW);
			digitalWrite(M2Izq,HIGH);
			digitalWrite(M2Der,LOW);
			marcha = true;
		}else if(reversa){
			digitalWrite(M1Izq,LOW);
			digitalWrite(M1Der,HIGH);
			digitalWrite(M2Izq,LOW);
			digitalWrite(M2Der,HIGH);
			marcha = true;
		}
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
	if(encendido){
		if(!reversa){
			digitalWrite(M1Izq, !dir);
			digitalWrite(M2Izq, dir);
		}else if(reversa){
			digitalWrite(M1Der, dir);
			digitalWrite(M2Der, !dir);
		}
		delay(100);
		receptor.resume();
		if (receptor.decode_results(&resultados))
		{
			if (resultados.value==valorPrev || resultados.value==0xFFFFFFFF)
			{
				girar(dir);
			}else{
				if(!reversa){
					digitalWrite(M1Izq, HIGH);
					digitalWrite(M2Izq, HIGH);
				}else if(reversa){
					digitalWrite(M1Der, HIGH);
					digitalWrite(M2Der, HIGH);
				}
				loop();
			}
		}
		
	}
}

void cambiarSentido(bool dir){ //0 adelante | 1 atras
	if (encendido){
		digitalWrite(M1Der, dir);
		digitalWrite(M1Izq, !dir);
		digitalWrite(M2Der, dir);
		digitalWrite(M2Izq, !dir);
		reversa = dir;
	}
}

void loop(){
	if(receptor.decode(&resultados)){
		if(resultados.value == 0XFFFFFFFF){
			reultados.value = valorPrev; 
		}
		valorPrev = resultado.value;
		switch(resultados.value){
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
			case 0xFF906F: //Up
				cambiarSentido(0);
				break;			
			case 0xFFE01F: //Down
				cambiarSentido(1);
				break;
			default:
				break;
		}
		receptor.resume();
	}
}