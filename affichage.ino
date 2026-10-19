void affichage ()
{
   // AFFICHAGE ECRAN   ///////////////////
    M5.Lcd.fillScreen(0x7800);  // Set the screen background dark brown
   // M5.Lcd.drawRect(0,0,319,239, LIGHTGREY);
    M5.Lcd.fillTriangle( 20,30,5,50,20,70, WHITE);
    M5.Lcd.fillTriangle( 40,30,25,50,40,70, WHITE);
    M5.Lcd.fillTriangle( 60,30,45,50,60,70, WHITE);
    M5.Lcd.fillRect (100, 10, 170, 80, 0x7830);
    M5.Lcd.drawRect (100, 10, 170, 80, WHITE);
    M5.Lcd.drawLine (70, 20, 100, 18, WHITE);
    M5.Lcd.drawLine (70, 80, 100, 82, WHITE);
    M5.Lcd.drawLine (270, 82, 300, 80,WHITE);
    M5.Lcd.drawLine (270, 18, 300, 20,WHITE);
    M5.Lcd.fillRect (100, 19, 170, 62,0x7830);
    M5.Lcd.drawLine (120, 50, 140, 50,WHITE);
    M5.Lcd.fillCircle (120, 35, 15,WHITE);
    M5.Lcd.fillCircle (120, 65, 15,WHITE);
    M5.Lcd.fillRect (140, 21, 120, 60, 0xc36e50);
    M5.Lcd.drawRoundRect (140, 21, 120, 60,5,WHITE);
  // valeur OFF/LOW/MED/MAX
  if (Puissance == 0) {
    M5.Lcd.fillRect (145, 25, 110, 50, 0xc36e50);
    M5.Lcd.setCursor(176,38);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println("OFF");
    // 166, 38, "LOW", lcd.FONT_DejaVu24, 0xFFFFFF, rotate=0
  }
if (Puissance == 1) {
    M5.Lcd.fillRect (145, 25, 110, 50, 0xc36e50);
    M5.Lcd.setCursor(176,38);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println("LOW");
    // 166, 38, "LOW", lcd.FONT_DejaVu24, 0xFFFFFF, rotate=0
  }
  if (Puissance == 2) {
    M5.Lcd.fillRect (145, 25, 110, 50, 0xc36e50);
    M5.Lcd.setCursor(176,38);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println("MED");
    // 166, 38, "LOW", lcd.FONT_DejaVu24, 0xFFFFFF, rotate=0
  }
  if (Puissance == 3) {
    M5.Lcd.fillRect (145, 25, 110, 50, 0xc36e50);
    M5.Lcd.setCursor(176,38);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println("MAX");
    // 166, 38, "LOW", lcd.FONT_DejaVu24, 0xFFFFFF, rotate=0
  }
    //   partie centrale /////////////////
    // seulement si en mode AUTO
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
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setCursor(20,138); 
    M5.Lcd.setTextSize(3);
    M5.Lcd.println(T1int);
    M5.Lcd.setCursor(265,138); 
    M5.Lcd.println(T2int);  
    M5.Lcd.setTextSize(2);  
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(5,168);   
    M5.Lcd.println("CHAMBRE");
    M5.Lcd.setCursor(147,168);   
    M5.Lcd.println("SET");
    M5.Lcd.setCursor(220,168);   
    M5.Lcd.println("CHEMINEE"); 

    if (auto_ == true) {
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(127,210);   
    M5.Lcd.println("AUTO");
    }    
    else {
    M5.Lcd.setTextColor(CYAN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(130,210);   
    M5.Lcd.println("MAN");      
    }
    M5.Lcd.setTextColor(ORANGE);
    M5.Lcd.setTextSize(7);
    M5.Lcd.setCursor(45,190);   
    M5.Lcd.println("-");
    M5.Lcd.setCursor(235,190);   
    M5.Lcd.println("+");      

}
