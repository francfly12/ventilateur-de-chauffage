// A faire toute les 10 secondes

void Every10s ()
{   // MESURE DE TEMPERATURE ET CORRECTION
  oldTemp1 = tempCelsius1 ;   // ancienne valeur de tempCelsius1
  tempSensor1.requestTemperatures();             // send the command to get temperature 1, dure 400 ms
  tempCelsius1 = tempSensor1.getTempCByIndex(0);  // read temperature in Celsius
  if (tempCelsius1 < 10) {tempCelsius1= oldTemp1;} ; // mis là car il existe une anomalie, le capteur transmet parfois -127

   oldTemp2 = tempCelsius2 ;   // ancienne valeur de tempCelsius1
   tempSensor2.requestTemperatures();             // send the command to get temperature 2, dure 400ms
  tempCelsius2 = tempSensor2.getTempCByIndex(0);  // read temperature in Celsius
  if (tempCelsius2 < 10) {tempCelsius2= oldTemp2;} ; // mis là car il existe une anomalie, le capteur transmet parfois -127
  
  // Filtrage valeur
  T1 = T1 +((tempCelsius1-T1)/6);   // filtre sur une minute environ : 6x10sec
  T2 = T2 +((tempCelsius2-T2)/6);
  T1int = abs(T1);   // T1int utilisé pour l'affichage
  T2int = abs(T2);   // idem T2int
//    // POUR AFFICHAGE EVENTUEL 

#ifdef DEBUG
  Serial.print("TempCelsius1 :  ");
  Serial.print(tempCelsius1);    // print the temperature in Celsius
  Serial.print("°C");
  Serial.print("   TempCelsius2 :  ");
  Serial.print(tempCelsius2);    // print the temperature in Celsius
  Serial.println("°C");  
  Serial.print("          T1 :  ");
  Serial.print(T1);    // print the temperature in Celsius
  Serial.print("°C");
  Serial.print("             T2 :  ");
  Serial.print(T2);    // print the temperature in Celsius
  Serial.print(" oldT2 :  ");
  Serial.print(oldT2);    //
  Serial.println("°C"); 
  Serial.print("DeltaT : ");
  Serial.print(DeltaT);    //
  Serial.print("  Demande : ");
  Serial.print(Demande);    //
  Serial.print("  Puissance : ");
  Serial.print(Puissance) ; 
  Serial.print("  outval : ");
  Serial.println(outVal);    //
   //
  if (auto_ == false) {Serial.print (" Manual ");} else {Serial.print (" AUTO ");} ;
  Serial.println(); 
  #endif
}
;
