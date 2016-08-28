/* Proyecto Eléctrico IE-0502
 *  Diseño e implementación de un sistema de alarmas multisensoriales
 *  Estudiante: Esteban Vargas Arrieta
 *  Carné: A96486
 *  Profesor guía: MSc. Fabian Abarca Calderón
 *  Lectores: Lic. Carlos Nájera Guadamuz
 *            Dr. Jaime Cascante Vindas
 */

#include <SoftwareSerial.h>
 // Variables
 SoftwareSerial Serie2(10,11);
void setup() {
  Serie2.begin(9600);
}

void loop() {
  Serie2.write("a");
  delay(3000);
  Serie2.write("b");
  delay(3000);
}
