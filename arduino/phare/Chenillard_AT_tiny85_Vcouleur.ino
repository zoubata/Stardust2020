/*
  Ce programme permet d'envoyer des octets sur le bus SPI de la carte ATtiny85.
  Il permet de piloter la rampe de LEDs APA102  (144 leds au mêtre)

  M Coutelier
  Lycée Monge La Chauvinière
  Nantes
  Le 9/11/19


  sur la carte ATTiny85
  MOSI pin : 1  (DIN LED  fil vert)
  MISO pin : 0
  SCK pin  : 2  (sck fil jaune)
  I2c : SDA:0  SCL:2
  PWM 0:504hz 1:504hz  4:1007hz
  pin 0,1,2 : 5V
  pin 3,4 : 3.6V
  pin 5 : 3V
  entrées analogiques a1:pin2, A3: pin3, A2:pin4, A0: pin5
  USB pin 3,4
*/

#include "tinySPI.h"

#define nbLed  29       // Nombre de led de la rampe
#define duree  300      // durée de changement de trame

unsigned long TimeRampe;
int led;                     // Led à allumer
int coul, red, green, blue;  // couleur de la led allumée

//################################################################################//
void setup (void)  {
  tinySPI::begin ();
  blue = green = red = 255;
}

//################################################################################//
void loop (void)  {
  while (1) {
    if (millis() > TimeRampe + duree) {     //  Toutes les  "duree" en milli-secondes
      TimeRampe = TimeRampe + duree;
      envoiTrame();                       // on rafraichi la rampe de led 
      led = led + 1;                      // Incrémentation de la LED à allumer
      if (led == nbLed) {                 // fin de ligne changement de la couleur et remise à zéro Led
        led = 0;
        coul = coul + 1;
        if (coul > 2) {
          coul = 0;
        }
        switch (coul) {
          case 0:
            blue = green = red = 255;
            break;
          case 1:
            blue = 0; green = 0; red = 255;
            break;
          case 2:
            blue = 0; green = 255; red = 0;
            break;
        }
      }
    }
  }
}

//################################################################################//
void envoiTrame(void) {
  // départ de trame
  tinySPI::transfer(0);
  tinySPI::transfer(0);
  tinySPI::transfer(0);
  tinySPI::transfer(0);

  for (int i = 0; i < nbLed+1; i++) {
    if (i == led) {  // Allumage de la LED i
      tinySPI::transfer(255);  //  intensité :  224 + 0 à 31
      tinySPI::transfer(blue);        //  bleu :  0 à 255
      tinySPI::transfer(green);        //  vert :  0 à 255
      tinySPI::transfer(red);        //  rouge :  0 à 255}
    }
    else {     // Extinction des autres LEDs
      tinySPI::transfer(224);  //  intensité :  224 + 0 à 31
      tinySPI::transfer(0);          //  bleu :  0 à 255
      tinySPI::transfer(0);          //  vert :  0 à 255
      tinySPI::transfer(0);          //  rouge :  0 à 255}
    }
  }
}
