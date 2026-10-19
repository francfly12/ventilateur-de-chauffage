/*
 *********** programme principal
 * by FSA
 ***********
 Version 13 : premiere version fonctionelle
 modif du 14/12/23 : a faire
 - supprimer la lecture de T1 si on a la valeur -12   <--- fait
 - corrigé ecran et supprimé boite grise externe      <--- fait
 - reduire la tempo de filtrage                     <--- fait, passe a 6 secondes
 - modifier les valeurs de temperature mini pour 25 degres  <--- fait
 - ajouté securité high temp ; si T2 superieur a 60 degres, 80 degres, etc... et en manuel aussi  <--- fait
 - creer un fonctionnement correct de sortie de veille sans alterer les entrées   <--- fait
Version 14: corriger bugs mineurs:
 - corriger partie securite high temp  <--- fait
 - affichage rouge high temp   <--- fait
 - corriger bug mineur reset   <--- fait
 - corriger affichage T2 coté droit  <--- fait
 - introduire if DEF debug   <--- fait
 - filtrer erreur lecture T2 -127

 */
// #define DEBUG 1   // pour utiliser les fonctions print du debugging, sinon le commenter //

#include <M5Stack.h> 
#include <OneWire.h>  // necessaire pour le DS18B20
#include <DallasTemperature.h>  // pour DS18B20
#include <RBDdimmer.h>//  Pour le circuit de commande a triac

const int SENSOR_1_PIN = 19 ; // M5stack pin connected to DS18B20 sensor 1 data pin , temp chambre, "T1"
const int SENSOR_2_PIN = 22 ; // M5stack pin connected to DS18B20 sensor 2 data pin , temp coté insert, "T2"

OneWire oneWire1(SENSOR_1_PIN);         // setup a oneWire instance
OneWire oneWire2(SENSOR_2_PIN);         // setup another oneWire instance

DallasTemperature tempSensor1(&oneWire1); // pass oneWire to DallasTemperature library
DallasTemperature tempSensor2(&oneWire2); // pass oneWire to DallasTemperature library

float T1 = 19;    // temperature in Celsius 1, filtrée sur 10 secondes ; coté chambre
float oldT1 = 19;
float T2 = 21;    // temperature in Celsius 2, filtrée sur 10 secondes ; coté cheminée
float oldT2 = 21;
float Demande  ;   //  = Tset - T2
float tempCelsius1;    // temperature in Celsius 1
float oldTemp1 ,  oldTemp2 ;       // ancienne valeur de tempCelsius1 et 2
float tempCelsius2;    // temperature in Celsius 2
float DeltaT;       // Différence entre T1 et T2
float Tset = 18 ;        // Temperature Set, float value;  18 sera la temperature de depart

int T1int = 19;   // C est l integer de T1
int T2int = 21;   //C est l integer de T2
int Tsetint = 20;    // set temperature, integer for display
int oldTset = 20 ;
int Puissance = 0 ; // puissance moteur 0=OFF 1=LOW , 2=MED , 3=MAX 
int oldPuissance = 0; 
bool auto_ = true ;  //  mode AUTO=true ou mode MANuel = 0
bool oldauto_ = true ;
bool veille = false ;  // true si en veille
unsigned long  T   ;           // for counting millis
unsigned long NewMillis, temps1; 
unsigned long temps2 ; // pour compter la mise en veille 
                    // doivent etre des "unsigned long"
int outVal = 10;  // puissance demandée, de 0 à 100

// For Dimmer ;
 #define outputPin  2  //  remplace la pin 23, PSM 
 #define zerocross  21  // for boards with CHANGEABLE input pins
 dimmerLamp dimmer(outputPin, zerocross); //initialise port for dimmer for ESP8266, ESP32, 
 
void setup() {

  M5.begin();        // Init M5Core    // 
  M5.Speaker.begin();
  M5.Speaker.write(0);   // met la sortie DAC à 0, coupe le bruit
// couper le haut-parleur, supprime le grésillement
#ifdef DEBUG  Serial.begin(115200); // initialize serial
  Serial.println("Demarrage...");
#endif
  tempSensor1.begin();    // initialize sensor T1
  tempSensor2.begin();    // initialize sensor T2
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE) 

  // COMPTAGE DU TEMPS
  temps1 = millis();           //temps au startup
  temps2 = temps1;             //reference de temps pour la mise en veille
  
   // INITIALISATION DU FILTRE DE TEMPERATURE :
  tempSensor1.requestTemperatures();             // send the command to get temperature 1
  T1 = tempSensor1.getTempCByIndex(0);  // read temperature in Celsius
  tempSensor2.requestTemperatures();             // send the command to get temperature 2
  T2 = tempSensor2.getTempCByIndex(0);  // read temperature in Celsius

 //  AFFICHAGE COMPLET
    affichage ();  // voir tab affichage 
  M5.Lcd.setBrightness(100) ;  

}
void loop() {
  // AFFICHAGE PARTIEL
  affichage_partiel ();
  // TEMPERATURE TOUTE LES 10 SECONDES :
  temps1 = millis();
  if ((temps1 - NewMillis) >= 10000) {NewMillis = temps1; Every10s();}  // a faire toute les 10 secondes
  // MISE EN VEILLE DE L ECRAN
  if (!veille ) { 
                 if ((temps1 - temps2) > 300000UL) {    // 300000 ms Correspond a 5 Minutes 
                    M5.Lcd.setBrightness(0) ;
                    M5.Lcd.sleep();
                    veille = true ;
                   }
                }
                if (veille) { 
  M5.update();  // update keys
  if (M5.BtnA.isPressed() || M5.BtnB.isPressed() || M5.BtnC.isPressed() ) {M5.Lcd.wakeup() ; M5.Lcd.setBrightness(255) ;temps2 = temps1 ;veille = false ; }   // REVEIL
                } ;
// */
  //TEST DES BOUTONS
 M5.update();  // Read the press state of the key.
 if ((M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000,200)) && (temps1 - temps2) >= 1000)    ///  condition (temps1 - temps2) >=1000  pour la sortie de veille, reveil sans action
     {
      if (auto_ == true) {
      Tset--;
      if (Tset <= 14) {Tset = 14;}; }
      else {
      Puissance--;
      if (Puissance <=0) {Puissance = 0;}
      }            
      } 
    else if ((M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000,200) )&& (temps1 - temps2) >= 1000) 
    {
      auto_ = !auto_;
      Puissance = 0 ;  // pour demarrer à 0 en manuel
     }
    else if ((M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000,200) )&& (temps1 - temps2) >= 1000) 
    {
      if (auto_ == true) {
      Tset++;
      if (Tset >= 25) {Tset = 25;}; }
      else {
      Puissance++;
      if (Puissance >=3) {Puissance = 3;} 
      } 
    } 
    else if (M5.BtnB.pressedFor(3000)) 
    { delay (2000); M5.Power.reset();  } // reset apres 3 secondes  sur B
    //  CHOIX DE PUISSANCE
    if (auto_== true){    // CHOIX EN MODE AUTOMATIQUE 
    choix () ;    // prog de choix et retour
        }  // fin si
  // SECURITE HIGH TEMP 
      if (T2 > 70)      {Puissance = max(Puissance, 1);}   // minimum de ventilation par securite, meme en manuel
      if (T2 > 80)      {Puissance = max(Puissance, 2);}   // minimum de ventilation par securite, meme en manuel
      if (T2 > 85)      {Puissance = max(Puissance, 3);}   // minimum de ventilation par securite, meme en manuel
 // ORDRE DE PUISSANCE
   if (Puissance == 0) {dimmer.setPower(0); } //  OFF
   if (Puissance == 1) {dimmer.setPower(24); } //  LOW
   if (Puissance == 2) {dimmer.setPower(31); } //  MED
   if (Puissance == 3) {dimmer.setPower(60); } //  MAX

}  // end loop
void choix () {
  Demande = (Tset - T1);   // DEMANDE
     DeltaT = T2 - T1;   // DELTA T2 - T1
       Puissance = 0 ;   // dans tous les cas
     if (T1 > Tset) {Puissance = 0 ; return ;} ;                //  demande inférieure a temperature actuelle
     if (T2 < 20)   {Puissance = 0 ; return ;} ;                //  cheminée trop froide  
     if (Demande > 3 && DeltaT > 20 ) {Puissance = 3 ; return ;} ;   //  demande plus de trois degres et delta T plus de 10 degres
     if (Demande > 3 && DeltaT > 10 ) {Puissance = 2 ; return ; } ;   //  demande plus de trois degres et delta T plus de 5 degres
     if (Demande > 2 && DeltaT > 10 ) {Puissance = 2 ; return ;} ;  //   demande plus de trois degres et delta T faible   
     if (Demande >= 1 && DeltaT > 10 ) {Puissance = 1 ; return ;} ;   //  demande plus de un degres et delta T plus de 5 degres     

     if (DeltaT < 2)  {Puissance = 1 ; return ;} ;                 //  tres peu de chauffe
     if (DeltaT < 1)  {Puissance = 0 ; return ;} ;                 //  trop peu de chauffe
}
