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
SoftwareSerial MySerial(13, 12); //Rx,Tx
// Variables
int pir = 11;
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
      Serial.write("240, 0, 0, 6, 800,500,");
      delay(3000);
    }
  }
  else {
    if (pirState == HIGH) {
      pirState = LOW;
    }
  }
  if (MySerial.available()) { // Se leen los datos provenientes de los puertos seriales
    char dato = MySerial.read(); //Se lee el dato proveniente del celular
    //Serial.write(MySerial.read());
    switch(dato){
      case 'w':{ // Whatsapp
        Serial.write("20,181,17,3,300,300,");
      }
      break;
      case 'f':{
        Serial.write("19,67,179,2,300,300,");
      }
      break;
      case 'g':{
        Serial.write("200, 0, 0, 2, 300, 300,");
      }
      break;
    }
    delay(100);
  }

  //Timbre
  buttonState = digitalRead(button);
  if(buttonState != lastButtonState){
    unsigned long currentMillis = millis();
    //Se realiza la resta y hasta que no se cumpla la condicion no ejecuta la instruccion
    if((currentMillis - preMillis) >= rebote){
      preMillis = currentMillis;
      Serial.write("238, 255, 7, 4, 1000, 500,");
      lastButtonState = buttonState;
    }
  }
  delay(500);
}



