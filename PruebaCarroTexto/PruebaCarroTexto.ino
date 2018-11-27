#include <IRremote.h>

const int pinRec = 13;
const int pinVel = 1;
const int M1Izq = 3;	//avanzar		derecha
const int M1Der = 4;	//retroceder
const int M2Izq = 5;	//avanzar		izquierda
const int M2Der = 6;	//retroceder
const int pinBocina = 7;


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
	Serial.println("Inicializado");
	/*digitalWrite(M1Izq,LOW);
	digitalWrite(M1Der,LOW);
	digitalWrite(M2Izq,LOW);
	digitalWrite(M2Der,LOW);*/
}

void encender(){
	Serial.println("encendido");
	/*if(encendido){
		digitalWrite(M1Izq,LOW);
		digitalWrite(M1Der,LOW);
		digitalWrite(M2Izq,LOW);
		digitalWrite(M2Der,LOW);	
	}
	analogWrite(pinVel, velocidades[0]);*/
	encendido = !encendido;
  Serial.println(encendido);
}

void arrancar(){
	if(encendido){
		if(marcha){
			/*digitalWrite(M1Izq,LOW);
			digitalWrite(M1Der,LOW);
			digitalWrite(M2Izq,LOW);
			digitalWrite(M2Der,LOW);*/
			Serial.println("Detenido");
			marcha = false;
		}else if(!reversa){
			/*
			digitalWrite(M1Izq,HIGH);
			digitalWrite(M1Der,LOW);
			digitalWrite(M2Izq,HIGH);
			digitalWrite(M2Der,LOW);*/
			Serial.println("andando");
			marcha = true;
		}else if(reversa){
			/*digitalWrite(M1Izq,LOW);
			digitalWrite(M1Der,HIGH);
			digitalWrite(M2Izq,LOW);
			digitalWrite(M2Der,HIGH);*/
			Serial.println("andando de reversa");
			marcha = true;
		}
	}
}

void subirVel(){
	if(encendido & vel<3){
		vel++;
	}
	//analogWrite(pinVel, velocidades[vel]);
  Serial.print("velocidad: ");
  Serial.println(vel);
 }

void bajarVel(){
	if(encendido & vel!=0){
		vel--;	
	}
	//analogWrite(pinVel, velocidades[vel]);
	Serial.print("velocidad: ");
	Serial.println(vel);
}

void girar(bool dir){ //0 derecha | 1 izquierda
	if(encendido){
		if(!reversa){
			/*digitalWrite(M1Izq, !dir);
			digitalWrite(M2Izq, dir);*/
			Serial.print("giro a:");
		}else if(reversa){
			/*digitalWrite(M1Der, dir);
			digitalWrite(M2Der, !dir);*/
			Serial.print("giro de reversa a:");
		}
    if(dir){
        Serial.println("izquierda");
      }else{
        Serial.println("derecha");
      }
		delay(100);
		receptor.resume();
		if (receptor.decode(&resultados))
		{
			if (resultados.value==valorPrev || resultados.value==0xFFFFFFFF)
			{
				girar(dir);
			}else{
				if(!reversa){
					/*digitalWrite(M1Izq, HIGH);
					digitalWrite(M2Izq, HIGH);*/
					Serial.println("dejo de girar");
				}else if(reversa){
					/*digitalWrite(M1Der, HIGH);
					digitalWrite(M2Der, HIGH);*/
					Serial.println("dejo de girar y retrocedio");
				}
				loop();
			}
		}
		
	}
}

void cambiarSentido(bool dir){ //0 adelante | 1 atras
	if (encendido){/*
		digitalWrite(M1Der, dir);
		digitalWrite(M1Izq, !dir);
		digitalWrite(M2Der, dir);
		digitalWrite(M2Izq, !dir);*/
		reversa = dir;
		if (reversa){
			Serial.println("Reversa");
		}else{
			Serial.println("andando");
		}
	}
}

void loop(){
	if(receptor.decode(&resultados)){
		if(resultados.value == 0XFFFFFFFF){
			resultados.value = valorPrev; 
		}
		valorPrev = resultados.value;
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
			case 0xFFE21D: //Func
				//pitar();
				break;
			default:
				break;
		}
   delay(500);
		receptor.resume();
	}
}
