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


void setup() {
  // Se definen los I/O del sistema incluyendo el puerto serial
  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}


// Este loop contiene las instrucciones que se ejecutaran segun la instruccion leida a traves del puerto serial
void loop() {
  if (Serial.available()) {
    char dato = Serial.read(); // Se lee cada cada numero del mensaje
    switch(dato){
    case 'w':{ // Whatsapp
      alarma(20, 181, 17, 3, 300);
    }
    break;
    case 'f':{ // Facebook
      alarma(19, 67, 179, 2, 300);
    }
    break;
    case 'g':{ // Gmail
      alarma(200, 0, 0, 2, 300);
    }
    break;
    case 'm':{ // Movimiento
      alarma(240, 0, 0, 6, 800);
    }
    break;
    case 'b':{ // bebe
      alarma(243, 64, 189, 4, 500);
    }
    break;
    case 'i':{ // incendio || gases
      alarma(225, 91, 14, 8, 800);
    }
    break;
    }
    delay(500);
  }
}


int alarma(int color1, int color2, int color3, int ciclos, int td) {
  for (int i = 0; i < ciclos; i++) {
    leds[0] = CRGB(color1, color2, color3);
    leds[1] = CRGB(color1, color2, color3);
    leds[2] = CRGB(color1, color2, color3);
    FastLED.show();
    delay(td);
    leds[0] = CRGB(0, 0, 0);
    leds[1] = CRGB(0, 0, 0);
    leds[2] = CRGB(0, 0, 0);
    FastLED.show();
    delay(td);
    //clean();
  }
}
