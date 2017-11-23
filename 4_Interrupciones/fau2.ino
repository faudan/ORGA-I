/* Constantes que no cambian y son usadas para setear el numero de los pines */
#define lineIzq 3
#define lineDer 2
#define potMotDer 5
#define masMotDer 6
#define masMotIzq 9
#define potMotIzq 10
#define sensorChoque 12
/* variables que cambian su valor: */
bool girandoIzq = false;
bool girandoDer = false;
bool avanzando = true;
//unsigned long tiempo = 0;
/* setup inicial*/
void setup() {
	Serial.begin(9600);
// Pongo las masas en cero
	pinMode(masMotDer, OUTPUT);
	pinMode(masMotIzq, OUTPUT);
	analogWrite(masMotDer, 0);
	analogWrite(masMotIzq, 0);
	pinMode(lineIzq, INPUT_PULLUP);
	pinMode(lineDer, INPUT_PULLUP);
	pinMode(sensorChoque, INPUT_PULLUP);
	pinMode(potMotDer, OUTPUT);
	pinMode(potMotIzq, OUTPUT);
// Interrupciones
	attachInterrupt(digitalPinToInterrupt(lineIzq), cambioEstado, CHANGE);
	
//attachInterrupt(digitalPinToInterrupt(sensorChoque), choque, CHANGE);
}
/* loop del programa */
void loop(){
	if(!digitalRead(sensorChoque)) {
		analogWrite(potMotIzq, 0);
		analogWrite(potMotDer, 0);
	}
	else{
		if(giro){
			analogWrite(potMotIzq, 75);
			analogWrite(potMotDer, 130);
		}
		else{
			analogWrite(potMotIzq, 75);
			analogWrite(potMotDer, 130);
		}
	}
}


void cambioEstado(){
	giro = not giro;

}