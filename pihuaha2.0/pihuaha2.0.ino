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

  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, INPUT);
  pinMode(4, INPUT);
  pinMode(2, INPUT);

  Serial.begin(9600);
} 

// Función que retorna la distancia en "cm" del sensor de ultrasonido
long ultrasonic_sensor (int triggerPin, int echoPin) {
  
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);

  return (pulseIn(echoPin, HIGH)*0.01723); // Función para medir la duración del pulso en el pin echoPin cuando el nivel lógico es alto (HIGH) y pasarlo a cm
}

// Función de movimiento para el puente H: ambos motores avanzan
void forward_robot() {

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(11, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}
  
// Función de movimiento para el puente H: ambos motores retroceden
void reverse_robot() {

  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(9, LOW);
  digitalWrite(11,HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

// Función de movimiento para el puente H:
// un motor gire hacia un sentido y el otro al sentido contrario (giro hacia la derecha)
void robot_right() {

  digitalWrite(5, HIGH);                       
  digitalWrite(6, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

// Función de movimiento para el puente H:
// un motor gire hacia un sentido y el otro al sentido contrario (giro hacia la izquierda)
void robot_left() {

  digitalWrite(5, HIGH);                               
  digitalWrite(6, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}
  
// Función para los sensores infrarrojos, al detectar blanco retrocede y gira hacia la derecha
void gray_sensor_1 () {
    
  reverse_robot();
  delay(900);
  robot_right();
  delay(800);
}

// Función para los sensores infrarrojos, al detectar blanco retrocede y gira hacia la izquierda
void gray_sensor_2 () {                      

  reverse_robot();
  delay(900);
  robot_left();                        
  delay(800);
}
   
void loop() {
  
  cm = ultrasonic_sensor(A5, A4); // Le enviamos la lectura de cm a los pines analógicos/digitales A5/A4 19/18 respectivamente
  Serial.print(cm);
  Serial.println("cm");
  
  if (digitalRead(2) == LOW) {
    gray_sensor_1 ();
    delay(10); 
  }
  
  else if (digitalRead(4) == LOW) {
    gray_sensor_2 ();
    delay(10); 
  }
 
  else if (cm <= 45) {
    forward_robot();
  }
 
  else if (digitalRead(10) == LOW) {
    reverse_robot();
    delay(10); 
  }

  else {
    robot_left();
    delay(10);
  }
}
