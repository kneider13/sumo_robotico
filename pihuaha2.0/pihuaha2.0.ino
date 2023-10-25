//  _______ _________                   _______           _______    _______     _______
// (  ____ )\__   __/|\     /||\     /|(  ___  )|\     /|(  ___  )  / ___   )   (  __   )
// | (    )|   ) (   | )   ( || )   ( || (   ) || )   ( || (   ) |  \/   )  |   | (  )  |
// | (____)|   | |   | (___) || |   | || (___) || (___) || (___) |      /   )   | | /   |
// |  _____)   | |   |  ___  || |   | ||  ___  ||  ___  ||  ___  |    _/   /    | (/ /) |
// | (         | |   | (   ) || |   | || (   ) || (   ) || (   ) |   /   _/     |   / | |
// | )      ___) (___| )   ( || (___) || )   ( || )   ( || )   ( |  (   (__/\ _ |  (__) |
// |/       \_______/|/     \|(_______)|/     \||/     \||/     \|  \_______/(_)(_______)
//

long cm = 0;

void setup() {
  
  Serial.begin(9600);

  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, INPUT);
  pinMode(4, INPUT);
  pinMode(2, INPUT);
} 

// Función que retorna la distancia en "cm" del sensor de ultrasonido.
long lecturaDisUltrasonido(int triggerPin, int echoPin) {
  
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);

  return (pulseIn(echoPin, HIGH)*0.01723);
}

// Función de movimiento para el puente H: ambos motores avanzan.
void avanza() {

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(11, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}
  
// Función de movimiento para el puente H: ambos motores retroceden.
void retrocede() {

  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(9, LOW);
  digitalWrite(11,HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

// Función de movimiento para el puente H:
// un motor gire hacia un sentido y el otro al sentido contrario (giro hacia la derecha).
void derecha() {

  digitalWrite(5, HIGH);                       
  digitalWrite(6, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

// Función de movimiento para el puente H:
// un motor gire hacia un sentido y el otro al sentido contrario (giro hacia la izquierda).
void izquierda() {

  digitalWrite(5, HIGH);                               
  digitalWrite(6, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}
  
// Función para los sensores infrarrojos, al detectar blanco retrocede y gira hacia la derecha.
void gris_1 () {
    
  retrocede();
  delay(900);
  derecha();
  delay(800);
}

// Función para los sensores infrarrojos, al detectar blanco retrocede y gira hacia la izquierda.
void gris_2 () {                      

  retrocede();
  delay(900);
  izquierda();                        
  delay(800);
}
   
void loop() {
  
  cm = lecturaDisUltrasonido(A5, A4);
  Serial.print(cm);
  Serial.println("cm");
  
  if (digitalRead(2) == LOW) {
    gris_1 ();
    delay(10); 
  }
  
  else if (digitalRead(4) == LOW) {
    gris_2 ();
    delay(10); 
  }
 
  else if(cm <= 45) {
    avanza();
  }
 
  else if (digitalRead(10) == LOW) {
    retrocede();
    delay(10); 
  }

  else {
    izquierda();
    delay(10);
  }
}
