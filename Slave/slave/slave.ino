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
#define NUM_LEDS 3
#define DATA_PIN 13

// Variables
CRGB leds[NUM_LEDS];
String Datos[6];
String Msg;


void setup() {
  // Se definen los I/O del sistema incluyendo el puerto serial
  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}


// Este loop contiene las instrucciones que se ejecutaran segun la instruccion leida a traves del puerto serial
void loop(){
  if (Serial.available()){
    //Msg = Serial.read(); //Se lee el mensaje que ha llegado
    int j = 0;
    for(int i=0; i<=5; i++){
      Datos[j] = Serial.readStringUntil(',');
      j++;
    }
    //j++;
    //Datos[j] = Serial.readStringUntil('\0');

    //Se procede a convertir los datos a numeros enteros
    int Red = Datos[0].toInt();
    int Green = Datos[1].toInt();
    int Blue = Datos[2].toInt();
    int Ciclos = Datos[3].toInt();
    int th = Datos[4].toInt();
    int tl = Datos[5].toInt();

    //Se llama la funcion alarma con los datos leídos
    alarma(Red,Green,Blue,Ciclos,th,tl);
    
  }
}

int alarma(int color1, int color2, int color3, int ciclos, int th, int tl) {
  for (int i = 0; i < ciclos; i++) {
    leds[0] = CRGB(color1, color2, color3);
    leds[1] = CRGB(color1, color2, color3);
    leds[2] = CRGB(color1, color2, color3);
    FastLED.show();
    delay(th);
    leds[0] = CRGB(0, 0, 0);
    leds[1] = CRGB(0, 0, 0);
    leds[2] = CRGB(0, 0, 0);
    FastLED.show();
    delay(tl);
    //clean();
  }
}
