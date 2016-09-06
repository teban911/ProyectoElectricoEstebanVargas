/* Proyecto Eléctrico IE-0502
 *  Diseño e implementación de un sistema de alarmas multisensoriales
 *  Estudiante: Esteban Vargas Arrieta
 *  Carné: A96486
 *  Profesor guía: MSc. Fabian Abarca Calderón
 *  Lectores: Lic. Carlos Nájera Guadamuz
 *            Dr. Jaime Cascante Vindas
 */

//#include <SoftwareSerial.h>
// Se definen los nuevos puertos seriales en el orden Rx, Tx
//SoftwareSerial MySerial(4,5); //Rx,Tx

void setup() {
  //Se inicializa el puerto serial
  Serial.begin(9600);
  //MySerial.begin(9600);
}

void loop() {
  Serial.write('a');
  delay(5000);
  Serial.write('b');
  delay(5000);
}
