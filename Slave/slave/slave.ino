/* Proyecto Eléctrico IE-0502
    Diseño e implementación de un sistema de alarmas multisensoriales
    Estudiante: Esteban Vargas Arrieta
    Carné: A96486
    Profesor guía: MSc. Fabian Abarca Calderón
    Lectores: Lic. Carlos Nájera Guadamuz
              Dr. Jaime Cascante Vindas
*/

// Variables
int rojo = 13;
int amarillo = 12;
int motor = 10;

void setup() {
  // Se definen los I/O del sistema incluyendo el puerto serial
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(motor, OUTPUT);
  Serial.begin(9600);
  digitalWrite(rojo, LOW);
  digitalWrite(amarillo, LOW);
  digitalWrite(amarillo, LOW);
}

// Este loop contiene las instrucciones que se ejecutaran segun la instruccion leida a traves del puerto serial
void loop() {
  while (Serial.available()) {
    char mensaje = Serial.read();
    // Se comprueba el dato y se selecciona el estado segun corresponda
    switch (mensaje) {
      case 'a':{ 
        for (int i = 0; i<=20; i++) {
          digitalWrite(rojo, HIGH);
          digitalWrite(motor, HIGH);
          delay(80);
          digitalWrite(rojo, LOW);
          digitalWrite(motor, LOW);
          delay(80);
        }
        break;
      }
      case 'b':{
        for (int i=0; i<=20; i++){
          digitalWrite(amarillo, HIGH);
          digitalWrite(motor, HIGH);
          delay(120);
          digitalWrite(amarillo, LOW);
          digitalWrite(motor, LOW);
          delay(60);
        }
        break;
      }
    }
  }
}