/*    DOCUMENTATION DU CIRCUIT ET DU LOGICIEL
but: controler un ventilateur pour chauffage d une chambre depuis la sortie air chaud de l insert de cheminée
comprend Un ventilateur 230V piloté par un circuit à triac, deux sondes de temperature T1 et T2, un ecran et controleur M5stack core, gris.

//// on va utiliser les pins ;
// pin 21  ZC  entree dimmer signal zero crossing
// pin 22  T2  temperature 2, Input, coté cheminée
// pin 2  PSM Sortie vers Dimmer commande PSM , pin sur le coté, choisie apres soucis avec la pin 23
// pin 19  T1  temperature 1, coté chambre


// Car ces pins sont sur le dessus du boitier ...
// Plus les Alim 5V et Gnd ... et le retour d alim 3.3 V vers le module de commande
//
// deux capteurs de temperature :  DS18B20
// Vcc rouge,  Data jaune  , Ground noir
// Pull up resistor 4,7 K
// declarations :
// #include <OneWire.h>
// #include <DallasTemperature.h>
//
// OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance 
// DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library
// sensors.begin();    // initialize the sensor
// sensors.requestTemperatures();
// tempCelsius = sensors.getTempCByIndex(0);
//
// Dimmer robotdynn dimmer module
// triac BTA16 600B  (snubberless)
//  brochage :  A1 / A2 / gate
// pour ajouter un snubber, mettre une resistance de 100 ohm (1W) / capa de 10 nf, reviennent souvent...   entre A1 et A2  
//  ou une resistance de 1K2  / capa de 220 nf pour courant de gachette <15ma
//  ou encore 2K4/100 nf  pour courant de gachette > 15 ma

// pilotage par MOC3021 (15ma)  a travers d une resistance 470 ohm - broche PCM
// signal zero crossing - une resistance de 10K le connecte à VCC sur la carte, via un optocoupleur EL817  - broche ZC
// VCC est de 3.3 ou 5V 
// librairie RBDDimmer installée (voir doc ci-jointe)  https://github.com/RobotDynOfficial/RBDDimmer
// mais le moteur fonctionne assez mal avec le module, ce pourquoi on ne choisit que quatre valeurs, OFF, LOW (24), MED (33)  et MAX (64)

// LIENS UTILES
//  https://docs.m5stack.com/en/api/core/lcd

Sleep :#include <M5Stack.h>

void setup() {
  M5.Lcd.begin();  //Initialize M5Stack
  M5.Lcd.sleep();    //Switch to sleep mode  but display(0) needed
}

void loop() {
}
wakeup
M5.Lcd.wakeup();    //Restore display from energy saving mode

Pour le debug :
#define DEBUG 1
at the top of the source (sketch) file. Where you have debug code, surround it with another preprocessor directive:

#ifdef DEBUG
Serial.print("Some debug stuff follows");
// More debug code...
#endif

*/
