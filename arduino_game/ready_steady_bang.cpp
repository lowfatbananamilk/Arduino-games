#include <LiquidCrystal.h>
#include "game.h"
#include "pitches.h"
#include "namespace.h"
using namespace globalVar;

class RSB : public Game {
    // Melodies ------------------------------------------------------------------------------------
    const int introM1[5] = {NOTE_A5, NOTE_D6, NOTE_A5, NOTE_D6, NOTE_A5};
    const int introM1L[5] = {125, 125, 125, 125, 500};

    const int introM2[5] = {NOTE_A5, 0, NOTE_F5, NOTE_G5, NOTE_D5};
    const int introM2L[5] = {500, 125, 500, 500, 375};

    const int introM3[2] = {NOTE_D5, 0};
    const int introM3L[2] = {375, 1625};

    const int winM[12] = {NOTE_A5, NOTE_B5, NOTE_C5, NOTE_B5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_D5,
                    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_E5};
    const int winML[12] = {41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41};

    // var -----------------------------------------------------------------------------------------
    int p1stat, p2stat;
    int p1win, p2win;
    unsigned long start, current, timer;
    unsigned long p1time, p2time;

public:
    void intro() override {
    lcd.clear();
    lcd.print("Ready");
    play(introM1, introM1L, 5); // 1sec

    lcd.print(" Steady");
    play(introM2, introM2L, 5); //2sec

    lcd.setCursor(0, 1);
    lcd.print("BANG!");
    lcd.setCursor(12, 1);
    lcd.print("V2.0");
    
    play(introM3, introM3L, 2); //4sec
    }

};

/*
void game() { 
  while(true) {
    lcd.clear();
    p1stat = false;
    p2stat = false;

    lcd.print("Press buttons");
    lcd.setCursor(0, 1);
    lcd.print("when ready.");
    lcd.blink();
  
    while(!p1stat || !p2stat) {
      if (digitalRead(BLUE) && !p1stat) {
        p1stat = true;
        lcd.setCursor(12, 1);
        lcd.print("P1");
        lcd.setCursor(10, 1);
        tone(piezo, NOTE_G6, 500);
      }
      if (digitalRead(GREEN) && !p2stat) {
        p2stat = true;
        lcd.setCursor(14, 1);
        lcd.print("P2");
        lcd.setCursor(10, 1);
        tone(piezo, NOTE_G6, 500);
      }

    }
    delay(1000);
    
    lcd.clear();
    p1stat = false;
    p2stat = false;

    timer = random(6000);
    
    lcd.print("Ready");
    tone(piezo, NOTE_C5, 500);
    delay(2000);
    
    lcd.clear();
    lcd.print("Steady");
    tone(piezo, NOTE_C5, 500);
    delay(timer);

    lcd.clear();
    lcd.print("BANG!!");
    start = millis();
    tone(piezo, NOTE_G5, 500);

    while (!p1stat || !p2stat) {
      current = millis();
      
      lcd.setCursor(0, 1);
      lcd.print("time: ");
      lcd.print(current - start);

      if (digitalRead(BLUE) && !p1stat) {
        p1time = current - start;
        p1stat = true;
      }

      if (digitalRead(GREEN) && !p2stat) {
        p2time = current - start;
        p2stat = true;
      }
    }  

    if (p1time < p2time) {
      p1win++;
    }
    else {
      p2win++;
    }
        
    lcd.noBlink();
    delay(2000);

    lcd.clear();
    if (p1win)
      lcd.print(p1win);
    lcd.setCursor(1, 0);
    lcd.print("  P1: ");
    lcd.print(p1time / 1000);
    lcd.print(".");
    lcd.print(p1time % 1000);
    
    delay(1000);
    lcd.setCursor(0, 1);
    if (p2win)
      lcd.print(p2win);
    lcd.setCursor(1, 1);
    lcd.print("  P2: ");
    lcd.print(p2time / 1000);
    lcd.print(".");
    lcd.print(p2time % 1000);

    play(winM, winML, 12); delay(16); //1sec

    if (p1time < p2time) {
      for (int i = 0; i < 4; i++) {
        lcd.home();
        lcd.print(p1win);
        
        lcd.setCursor(1, 0);
        lcd.print("            WON");
        delay(500);

        lcd.setCursor(1, 0);
        lcd.print("  P1: ");
        lcd.print(p1time / 1000);
        lcd.print(".");
        lcd.print(p1time % 1000);
        delay(500);
      }
    }

    else {
      for (int i = 0; i < 4; i++) {
        lcd.setCursor(0, 1);
        lcd.print(p2win);
        
        lcd.setCursor(1, 1);
        lcd.print("            WON");
        delay(500);

        lcd.setCursor(1, 1);
        lcd.print("  P2: ");
        lcd.print(p2time / 1000);
        lcd.print(".");
        lcd.print(p2time % 1000);
        delay(500);
      }
    }
      
    delay(1000);
  }  
  
}


*/
