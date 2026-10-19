void affichage_partiel ()
{
  // les variables sont : Tset,T1,T2,auto_,Puissance,auto_
  // pas d'affichage si les variables n ont pas changé :
  if (!(oldTset!=Tset || oldT1!=T1 || oldT2!=T2 || oldPuissance!=Puissance || oldauto_!= auto_ )) {return;}
  else {
    oldTset = Tset ;
    oldT1 = T1 ;
    oldT2 = T2 ;
    oldPuissance = Puissance;
    oldauto_ = auto_;
  }
   // AFFICHAGE ECRAN   ///////////////////
   // TRIANGLES
   if (Puissance == 0) {     // OFF
    M5.Lcd.fillTriangle( 20,30,5,50,20,70, 0x7800);  // triangle gauche
    M5.Lcd.drawTriangle( 20,30,5,50,20,70, WHITE);  // triangle gauche
    M5.Lcd.fillTriangle( 40,30,25,50,40,70, 0x7800);  // triangle centre
    M5.Lcd.drawTriangle( 40,30,25,50,40,70, WHITE);  // triangle centre
    M5.Lcd.fillTriangle( 60,30,45,50,60,70, 0x7800);  // triangle a droite
    M5.Lcd.drawTriangle( 60,30,45,50,60,70, WHITE);  // triangle a droite
   }
      if (Puissance == 1) {   // LOW
    M5.Lcd.fillTriangle( 20,30,5,50,20,70, 0x7800);  // triangle gauche
    M5.Lcd.drawTriangle( 20,30,5,50,20,70, WHITE);  // triangle gauche
    M5.Lcd.fillTriangle( 40,30,25,50,40,70, 0x7800);  // triangle centre
    M5.Lcd.drawTriangle( 40,30,25,50,40,70, WHITE);  // triangle centre
    M5.Lcd.fillTriangle( 60,30,45,50,60,70, WHITE);  // triangle a droite
   }
      if (Puissance == 2) {   // MED
    M5.Lcd.fillTriangle( 20,30,5,50,20,70, 0x7800);  // triangle gauche
    M5.Lcd.drawTriangle( 20,30,5,50,20,70, WHITE);  // triangle gauche
    M5.Lcd.fillTriangle( 40,30,25,50,40,70, WHITE);  // triangle centre
    M5.Lcd.fillTriangle( 60,30,45,50,60,70, WHITE);  // triangle a droite
   }
      if (Puissance == 3) {   // MAX
    M5.Lcd.fillTriangle( 20,30,5,50,20,70, WHITE);  // triangle gauche
    M5.Lcd.fillTriangle( 40,30,25,50,40,70, WHITE);  // triangle centre
    M5.Lcd.fillTriangle( 60,30,45,50,60,70, WHITE);  // triangle a droite
   }
   // PARTIE DU HAUT
     M5.Lcd.fillRect (140, 21, 120, 60, 0xc36e50);
   // M5.Lcd.drawRoundRect (140, 21, 120, 60,5,WHITE);
  // valeur OFF/LOW/MED/MAX
     M5.Lcd.setTextColor(TFT_WHITE);    // COULEUR TOUJOURS BLANC
     if (auto_ == true) {M5.Lcd.setTextSize(3);M5.Lcd.setCursor(170,38);}
     else {M5.Lcd.setTextSize(5);    M5.Lcd.setCursor(155,32);}
    if (Puissance == 0) {
    M5.Lcd.fillRect (145, 25, 110, 50, 0xc36e50);
    M5.Lcd.println("OFF");
    // 166, 38, "LOW", lcd.FONT_DejaVu24, 0xFFFFFF, rotate=0
  }
if (Puissance == 1) {
    M5.Lcd.fillRect (145, 25, 110, 50, 0xc36e50);
    M5.Lcd.println("LOW");
    // 166, 38, "LOW", lcd.FONT_DejaVu24, 0xFFFFFF, rotate=0
  }
  if (Puissance == 2) {
    M5.Lcd.fillRect (145, 25, 110, 50, 0xc36e50);
    M5.Lcd.println("MED");
    // 166, 38, "LOW", lcd.FONT_DejaVu24, 0xFFFFFF, rotate=0
  }
  if (Puissance == 3) {
    M5.Lcd.fillRect (145, 25, 110, 50, 0xc36e50);
    M5.Lcd.println("MAX");
    // 166, 38, "LOW", lcd.FONT_DejaVu24, 0xFFFFFF, rotate=0
  }
    //   partie centrale /////////////////
    M5.Lcd.fillRect (10,100,195,65,0x7800);  // background texte en  0x7800
  if (auto_ == true) {
    M5.Lcd.setTextColor(CYAN);
    M5.Lcd.setCursor(125,105); 
    M5.Lcd.setTextSize(7);
    Tsetint = int (Tset) ;   // transforme un float en integer
    M5.Lcd.println (Tsetint);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.drawCircle (215, 105, 6,WHITE);
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(225,115);
    M5.Lcd.println("C");   
    }
    else // sinon afficher en couleur fond d'ecran
    {
    M5.Lcd.setTextColor(0x7800);
    M5.Lcd.drawCircle (215, 105, 6,0x7800);
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(225,115);
    M5.Lcd.println("C");   
    M5.Lcd.setCursor(147,168);   
    M5.Lcd.println("SET"); 
    }
//  partie du bas     //////////////////////
if (auto_==true) {
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(147,168);   
    M5.Lcd.println("SET");
    }
    else {
    M5.Lcd.setTextColor(0x7800);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(147,168);   
    M5.Lcd.println("SET"); 
    }
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setCursor(20,138); 
    M5.Lcd.setTextSize(3);
    M5.Lcd.println(T1int);
    M5.Lcd.fillRect (258, 128, 55, 35,0x7800);  // background texte en  0x7800
    M5.Lcd.setTextColor(GREEN);
    if (T2 >= 70) {M5.Lcd.setTextColor(ORANGE);} ;
    if (T2 >= 75) {M5.Lcd.setTextColor(RED);} ;
    M5.Lcd.setCursor(265,138); 
    M5.Lcd.println(T2int);  
    M5.Lcd.setTextSize(2);  
  
      if (auto_ == true) {
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(127,210); 
    M5.Lcd.fillRect (122, 202, 80, 30,0x7800);  // background texte en  0x7800  
    M5.Lcd.println("AUTO");
    }    
    else {
    M5.Lcd.setTextColor(CYAN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.fillRect (122, 202, 80, 30,0x7800);  // background texte en  0x7800 
    M5.Lcd.setCursor(130,210);   
    M5.Lcd.println("MAN");      
    }
        

}
