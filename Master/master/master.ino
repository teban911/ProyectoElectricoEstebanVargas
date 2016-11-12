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
const int pir = 11;
const int button = 10;
const int sound = 9;
const int gas = A0;
int pirState = LOW;
int gasState = LOW;
int gasValue = 0;
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
  pinMode(sound, HIGH);
}

void loop() {
  //Los datos se transmiten en el siguiente orden:
  // (R,G,B,tTotal,thL,tlL,thM,tlM,Despertador,Sonido) //Nota: poner siempre la coma "," al final, pues se necesita para saber donde termina el string
  /////////////////////////////////////////////////////////////////////////////////////////////
  //                    GAS sensor
  /////////////////////////////////////////////////////////////////////////////////////////////
  gasValue = analogRead(gas);
  if (gasValue > 10){  //Se lee el dato del sensor de gas
    if (gasState == LOW){
      gasState = HIGH;
      Serial.write("230,11,246,6000,500,400,1000,300,0,1,");
      delay(3000);  
    }
  }
  else {
    if (gasState == HIGH){
      gasState = LOW;
    }
  }
  /////////////////////////////////////////////////////////////////////////////////////////////
  //                    PIR sensor
  /////////////////////////////////////////////////////////////////////////////////////////////
  if (digitalRead(pir) == HIGH) { //Se lee el dato del sensor de movimiento
    if (pirState == LOW) {
      pirState = HIGH;
      Serial.write("240,0,0,7000,500,400,1800,400,0,1,");
      delay(3000);
    }
  }
  else {
    if (pirState == HIGH) {
      pirState = LOW;
    }
  }
 /////////////////////////////////////////////////////////////////////////////////////////////
  //                   Bluetooth sensor
  /////////////////////////////////////////////////////////////////////////////////////////////
  if (MySerial.available()) { // Se leen los datos provenientes de los puertos seriales
    char dato = MySerial.read(); //Se lee el dato proveniente del celular
    //Serial.write(MySerial.read());
    switch(dato){
      case 'w':{ // Whatsapp
        Serial.write("20,181,17,1300,300,300,1300,0,0,0,");
      }
      break;
      case 'f':{ //facebook
        Serial.write("19,67,179,2000,500,500,500,500,0,0,");
      }
      break;
      case 'g':{ //Gmail
        Serial.write("200,0,0,1000,1000,1,1000,1,0,0,");
      }
      break;
      case 'd':{ //Despertador
        Serial.write("239,239,0,500,500,500,750,750,1,1,");
      }
      break;
    }
  }
  /////////////////////////////////////////////////////////////////////////////////////////////
  //                    Timbre
  /////////////////////////////////////////////////////////////////////////////////////////////
  buttonState = digitalRead(button);
  if(buttonState != lastButtonState){
    unsigned long currentMillis = millis();
    //Se realiza la resta y hasta que no se cumpla la condicion no ejecuta la instruccion
    if((currentMillis - preMillis) > rebote){
      preMillis = currentMillis;
      Serial.write("238,255,7,3000,800,200,3000,200,0,1,");
    }  
      lastButtonState = buttonState;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////
  //                    Sonido
  /////////////////////////////////////////////////////////////////////////////////////////////
  if(sound == HIGH){
    Serial.write("252,127,206,300,500,500,750,750,1,1,");
  }
}



