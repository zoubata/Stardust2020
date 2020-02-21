/*
  Ce programme permet de déployer ou replier le phare et commander l'affichage.

  A la mise sous tension, il faut appuyer sur la porte de détection (a gauche : phare replié, à droite phare déployé.
  Pour indiquer au programme quelle est la situation de départ et éviter des mouvements brusques des servos.

  Au bout de 1 seconde, le programme attend qu'un contact (gauche ou droit) déclenche le mouvement du phare vers l'autre position.
  Lorsque le phare est en haut, il commande l'amllumage du feu.
  C'est une carte ATtiny qui commande la rampe de led APA102 à sa mise sous tension.

  Pour changer le phare de position, il faut couper l'alimentation puis la remettre, et recommencer le processus
  (initialisation, puis déclenchement).

  Laurent  Coutelier
  15/02/2020

*/

#include <Servo.h>

#define SerialSpeed 115200       // vitesse communication bus série
#define pinBp1 2                 // Pin bouton gauche 
#define pinBp2 3                 // Pin bouton droit
#define pinPower 4               // Pin Puissance servo
#define pinLight 5               // pin Leds Phare (ATtiny85)
#define pinServoBas 9            // pin servo bas
#define pinServoHaut 10          // pin servo haut
#define pauseMouvt 100           // vitesse du mouvement 

Servo servo1, servo2;  // create servo object to control a servo

int  bp1, bp2, posPhare, posCible, sensMouv;

//####################################################################################################
void setup() {
  Serial.begin(SerialSpeed);
  pinMode(pinBp1, INPUT_PULLUP);
  pinMode(pinBp2, INPUT_PULLUP);
  pinMode(pinPower, OUTPUT);
  pinMode(pinLight, OUTPUT);
  digitalWrite(pinPower, LOW);
  digitalWrite(pinLight, LOW);

  // Attente de la définition de la position initiale du phare
  Serial.println("Attente initialisation position");
  Serial.println("Un coup à gauche : phare replié");
  Serial.println("Un coup à droite : phare Déployé");
  bp1 = digitalRead(pinBp1);
  bp2 = digitalRead(pinBp2);
  while (bp1 == 1 & bp2 == 1) {
    bp1 = digitalRead(pinBp1); //(a gauche pour en phare replié)
    bp2 = digitalRead(pinBp2);//(a gauche pour en phare déployé)
  }

  //reprise de la position de référence actuelle
  Serial.print("bp1 : "); Serial.print(bp1);
  Serial.print(" bp2 : "); Serial.print(bp2); Serial.println(" ");
  Serial.print("Phare en position : ");
  servo1.attach(pinServoBas);  // attaches the servo on pin 9 to the servo object
  servo2.attach(pinServoHaut);  // attaches the servo on pin 9 to the servo object
  if (bp1 == 0 & bp2 == 1) {
    posPhare = 40;
    posCible = 40;
    servo1.write(posCible);            // sets the servo position according to the scaled value
    servo2.write(posCible);            // sets the servo position according to the scaled value

    Serial.print("replié");
  }
  if (bp1 == 1 & bp2 == 0) {
    posPhare = 180;
    posCible = 180;
    servo1.write(posCible);            // sets the servo position according to the scaled value
    servo2.write(posCible);            // sets the servo position according to the scaled value
    Serial.println("Déployé");
    Serial.println("Allumage du feu");
    digitalWrite(pinLight, HIGH);
  }
  digitalWrite(pinPower, HIGH);               // mise en puissance des servo
  Serial.println();

  delay(1000);                             // attente de stabilisation et relache du bouton d'initialisation
  digitalWrite(pinPower, LOW);             // servo à l'arrêt
  Serial.println("Attente contact robot");
  Serial.println("=====================");

  
  
  // attente du déclenchement
  bp1 = digitalRead(pinBp1);
  bp2 = digitalRead(pinBp2);
  while (bp1 == 1 & bp2 == 1) {
    bp1 = digitalRead(pinBp1); //(a gauche pour en phare replié)
    bp2 = digitalRead(pinBp2); //(a gauche pour en phare déployé)
  }

  // Mise en mouvement du phare
  if (posPhare == 40) {
    posCible = 180;
    sensMouv = 1;
    Serial.println("Montée du phare");
  }
  else {
    posCible = 40;
    Serial.println("Descente du phare");   
     Serial.println("Exctinction du feu");
    digitalWrite(pinLight, LOW);
    sensMouv = -1;
  }

  Serial.print("posPhare=");     Serial.print(posPhare);       Serial.print(" posCible=");     Serial.println(posCible);

digitalWrite(pinPower, HIGH);               // mise en puissance des servo

  //Montée du phare
  if (sensMouv == 1) {
      Serial.println("Montée tronçon 1");  
    for (int i = posPhare; i <= posCible; i = i + sensMouv) {
      servo1.write(i);                  // sets the servo position according to the scaled value
      Serial.println(i);
      delay(pauseMouvt);
    }
      Serial.println("Montée tronçon 2");
for (int i = posPhare; i <= posCible; i = i + sensMouv) {
      servo2.write(i);          // sets the servo position according to the scaled value
      Serial.println(i);
      delay(pauseMouvt);
      posPhare = i;
    }
   
    Serial.println("Phare Déployé");
    Serial.println("Allumage du feu");
    digitalWrite(pinLight, HIGH);
  } else {
    Serial.println("Descente tronçon 2");
    for (int i = posPhare; i >= posCible; i = i + sensMouv) {
      servo2.write(i);          // sets the servo position according to the scaled value
      Serial.println(i);
      delay(pauseMouvt);
    }
      Serial.println("Descente tronçon 1");
    for (int i = posPhare; i >= posCible; i = i + sensMouv) {
      servo1.write(i);                  // sets the servo position according to the scaled value
      Serial.println(i);
      delay(pauseMouvt);
      posPhare = i;
    }
  
    Serial.println("Phare replié");
  }
  digitalWrite(pinPower, LOW);             // servo à l'arrêt
  Serial.print("Position du phare = ");
  Serial.println(posPhare);
    Serial.println("=====================");
  Serial.println("Pour changer la position du phare, couper et remettre l'énergie (ARU)");
  Serial.println("refaire la même procédure, le phare changera de position");
}


//####################################################################################################
void loop() {}
