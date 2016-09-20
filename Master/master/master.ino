/* Proyecto Eléctrico IE-0502
    Diseño e implementación de un sistema de alarmas multisensoriales
    Estudiante: Esteban Vargas Arrieta
    Carné: A96486
    Profesor guía: MSc. Fabian Abarca Calderón
    Lectores: Lic. Carlos Nájera Guadamuz
              Dr. Jaime Cascante Vindas
*/

#include <SoftwareSerial.h>
// Se definen los nuevos puertos seriales en el orden Rx, Tx
SoftwareSerial MySerial(11, 12); //Rx,Tx
// Variables
int pir = 13;
int button = 10;
int pirState = LOW;
int buttonState = 0;
int lastButtonState = 0;
unsigned long preMillis = 0;
long rebote = 400;

void setup() {
  //Se inicializa el puerto serial
  Serial.begin(9600);
  MySerial.begin(9600);
  pinMode(pir, INPUT);
  pinMode(button, INPUT);
}

void loop() {
  if (digitalRead(pir) == HIGH) { //Se lee el valor del PIR
    if (pirState == LOW) {
      pirState = HIGH;
      Serial.write('m');
      delay(3000);
    }
  }
  else {
    if (pirState == HIGH) {
      pirState = LOW;
    }
  }
  if (MySerial.available()) { // Se leen los datos provenientes de los puertos seriales
    Serial.write(MySerial.read());
    delay(100);
  }
  buttonState = digitalRead(button);
  if(buttonState != lastButtonState){
    unsigned long currentMillis = millis();
    //Se realiza la resta y hasta que no se cumpla la condicion no ejecuta la instruccion
    if((currentMillis - preMillis) >= rebote){
      preMillis = currentMillis;
      Serial.write('t');
      lastButtonState = buttonState;
    }
  }
  delay(500);
}



