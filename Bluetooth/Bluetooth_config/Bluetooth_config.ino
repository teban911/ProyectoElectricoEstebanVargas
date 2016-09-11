/* Proyecto Eléctrico IE-0502
    Diseño e implementación de un sistema de alarmas multisensoriales
    Estudiante: Esteban Vargas Arrieta
    Carné: A96486
    Profesor guía: MSc. Fabian Abarca Calderón
    Lectores: Lic. Carlos Nájera Guadamuz
              Dr. Jaime Cascante Vindas
*/
#include <SoftwareSerial.h>
SoftwareSerial BT(10,11);
void setup() {
  BT.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if(BT.available()){
    Serial.write(BT.read());
  }
  if(Serial.available()){
    BT.write(Serial.read());
  }
}
