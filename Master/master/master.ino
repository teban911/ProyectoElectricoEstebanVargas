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
long rebote = 500;

void setup() {
  //Se inicializa el puerto serial
  Serial.begin(9600);
  MySerial.begin(9600);
  pinMode(pir, INPUT);
  pinMode(button, INPUT);
}

void loop() {
  //Los datos se transmiten en el siguiente orden:
  // (R,G,B,tTotal,thL,tlL,thM,tlM)
  if (digitalRead(pir) == HIGH) { //Se lee el valor del PIR
    if (pirState == LOW) {
      pirState = HIGH;
      Serial.write("240,0,0,7000,500,400,1800,400,");
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
        Serial.write("20,181,17,1300,300,300,1300,0,");
      }
      break;
      case 'f':{
        Serial.write("19,67,179,2000,500,500,500,500,");
      }
      break;
      case 'g':{
        Serial.write("200,0,0,1000,1000,1,1000,1,");
      }
      break;
    }
  }

  //Timbre
  buttonState = digitalRead(button);
  if(buttonState != lastButtonState){
    unsigned long currentMillis = millis();
    //Se realiza la resta y hasta que no se cumpla la condicion no ejecuta la instruccion
    if((currentMillis - preMillis) > rebote){
      preMillis = currentMillis;
      Serial.write("238,255,7,3000,800,200,3000,200,");
    }  
      lastButtonState = buttonState;
  }
}



