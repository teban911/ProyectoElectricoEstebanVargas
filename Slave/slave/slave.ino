/* Proyecto Eléctrico IE-0502
    Diseño e implementación de un sistema de alarmas multisensoriales
    Estudiante: Esteban Vargas Arrieta
    Carné: A96486
    Profesor guía: MSc. Fabian Abarca Calderón
    Lectores: Lic. Carlos Nájera Guadamuz
              Dr. Jaime Cascante Vindas
*/
//#include <SoftwareSerial.h>
#include "FastLED.h"
#define NUM_LEDS 1
#define DATA_PIN 3

////////////////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////////////////
CRGB leds[NUM_LEDS];
String Datos[8];
String Msg;
int motor = 6;
unsigned long tRef;
unsigned long tRefL;
unsigned long tRefM;
const int parlante = 13;
int despertar = 0;
int boton = 10;
int sensitividad = 0;
int buttonState = 0;


void setup() {
  // Se definen los I/O del sistema incluyendo el puerto serial
  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(motor, OUTPUT);
  pinMode(boton, INPUT);
}


// Este loop contiene las instrucciones que se ejecutaran segun la instruccion leida a traves del puerto serial
void loop(){
  if (Serial.available()){
    //Msg = Serial.read(); //Se lee el mensaje que ha llegado
    int j = 0;
    for(int i=0; i<=9; i++){
      Datos[j] = Serial.readStringUntil(',');
      j++;
    }
    //j++;
    //Datos[j] = Serial.readStringUntil('\0');

    //Se procede a convertir los datos a numeros enteros
    int Red = Datos[0].toInt();
    int Green = Datos[1].toInt();
    int Blue = Datos[2].toInt();
    int tTotal = Datos[3].toInt();
    int thL = Datos[4].toInt();
    int tlL = Datos[5].toInt();
    int thM = Datos[6].toInt();
    int tlM = Datos[7].toInt();
    int Desp = Datos[8].toInt();
    int Sound = Datos[9].toInt();

    //Se escoge el tipo de funcion segun el valor de Desp, si es 1 llama la funcion despertador, si es cero llama la funcion alarma
    //alarma(Red,Green,Blue,Ciclos,th,tl);
    if(Desp == 0){
      alarma(Red,Green,Blue,tTotal,thL,tlL,thM,tlM,Sound);
    }
    if(Desp == 1){
      despertar = 1;
      sensitividad = 20;
      despertador(Red, Green, Blue, thL,tlL,thM,tlM,Sound);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                           Funcion de alarma
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//int alarma(int color1, int color2, int color3, int ciclos, int th, int tl) {
int alarma(int color1, int color2, int color3, int tTotal, int thL, int tlL, int thM, int tlM, int Sound) {
  tRef = millis();
  tRefL = millis();
  tRefM = millis();
  while((millis() - tRef) < tTotal){
    ////////////////////////////////////////////////////////
    // Enciende los LED durante el tiempo en alto de los LED
    ////////////////////////////////////////////////////////
    if((millis()- tRefL) < thL ){ 
      leds[0] = CRGB(color1, color2, color3);
      //leds[1] = CRGB(color1, color2, color3);
      //leds[2] = CRGB(color1, color2, color3);
      FastLED.show();
    }
    ////////////////////////////////////////////////////////
    // Si se excede el tiempo en alto de los LED se apagan
    ////////////////////////////////////////////////////////
    if(((millis()- tRefL) > thL) && ((millis()-tRefL) < (thL + tlL))){
      leds[0] = CRGB(0, 0, 0);
      //leds[1] = CRGB(0, 0, 0);
      //leds[2] = CRGB(0, 0, 0);
      FastLED.show();
    }
    /////////////////////////////////////////////////////////
    //Se refresca el tiempo de referencia de los LED
    /////////////////////////////////////////////////////////
    if((millis() - tRefL) > (thL + tlL)){
      tRefL = millis();
    }
    //////////////////////////////////////////////////////////////////
    //Enciende el motor durante el tiempo en alto del motor
    //Si Sound es igual a uno, enciende el parlante duante este tiempo
    //////////////////////////////////////////////////////////////////
    if((millis()- tRefM) < thM ){
      analogWrite(motor,153);
      if(Sound == 1){
        tone(parlante, 600);
      }
    }
    ////////////////////////////////////////////////////////////////////
    //Si se excede el tiempo en alto del motor se apaga junto con el mic
    ////////////////////////////////////////////////////////////////////
    if(((millis()- tRefM) > thM) && ((millis()-tRefM) < (thM + tlM))){
      analogWrite(motor,0);
      noTone(parlante);
    }
    if((millis() - tRefM) > (thM + tlM)){
      tRefM = millis();
    }
  }
  ///////////////////////////////////////////////
  //Cuando sale del while apaga todas las salidas
  ///////////////////////////////////////////////
  leds[0] = CRGB(0, 0, 0);
  //leds[1] = CRGB(0, 0, 0);
  //leds[2] = CRGB(0, 0, 0);
  FastLED.show();
  noTone(parlante);
  analogWrite(motor,0);
}



 /////////////////////////////////////////////////////////////////////////
 /// Funcion de alarma despertadora
 /////////////////////////////////////////////////////////////////////////
int despertador(int color1, int color2, int color3, int thL, int tlL, int thM, int tlM, int Sound) {
  tRef = millis();
  tRefL = millis();
  tRefM = millis();
  while(despertar == 1){
    ////////////////////////////////////////////////////////
    // Enciende los LED durante el tiempo en alto de los LED
    ////////////////////////////////////////////////////////
    buttonState = digitalRead(boton);
    if(buttonState == HIGH){
      despertar = 0;
    }
    if((millis()- tRefL) < thL ){ 
      leds[0] = CRGB(color1, color2, color3);
      FastLED.show();
    }
    ////////////////////////////////////////////////////////
    // Si se excede el tiempo en alto de los LED se apagan
    ////////////////////////////////////////////////////////
    if(((millis()- tRefL) > thL) && ((millis()-tRefL) < (thL + tlL))){
      leds[0] = CRGB(0, 0, 0);
      FastLED.show();
    }
    /////////////////////////////////////////////////////////
    //Se refresca el tiempo de referencia de los LED
    /////////////////////////////////////////////////////////
    if((millis() - tRefL) > (thL + tlL)){
      tRefL = millis();
    }
    //////////////////////////////////////////////////////////////////
    //Enciende el motor durante el tiempo en alto del motor
    //Si Sound es igual a uno, enciende el parlante duante este tiempo
    //////////////////////////////////////////////////////////////////
    if((millis()- tRefM) < thM ){
      analogWrite(motor,sensitividad);
      if(Sound == 1){
        tone(parlante, 600);
      }
    }
    ////////////////////////////////////////////////////////////////////
    //Si se excede el tiempo en alto del motor se apaga junto con el mic
    ////////////////////////////////////////////////////////////////////
    if(((millis()- tRefM) > thM) && ((millis()-tRefM) < (thM + tlM))){
      analogWrite(motor,0);
      noTone(parlante);
    }
    if((millis() - tRefM) > (thM + tlM)){
      tRefM = millis();
      if(sensitividad < 133){
        sensitividad = sensitividad + 20;
      }
    }
  }
  ///////////////////////////////////////////////
  //Cuando sale del while apaga todas las salidas
  ///////////////////////////////////////////////
  leds[0] = CRGB(0, 0, 0);
  //leds[1] = CRGB(0, 0, 0);
  //leds[2] = CRGB(0, 0, 0);
  FastLED.show();
  noTone(parlante);
  analogWrite(motor,0);
}
