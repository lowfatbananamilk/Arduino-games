#include "pitches.h"
const int win[] = {NOTE_A5, NOTE_B5, NOTE_C5, NOTE_B5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_D5,
                    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_E5};

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int BLUE = 6, GREEN = 7, piezo = 8, vr = 9, setting = 10;

int p1stat, p2stat, p1win = 0, p2win = 0;
unsigned long start, current, p1time, p2time, timer;

void intro() {
  lcd.clear();
  lcd.print("Ready");
  tone(piezo, NOTE_A5); delay(125);
  tone(piezo, NOTE_D6); delay(125);
  tone(piezo, NOTE_A5); delay(125);
  tone(piezo, NOTE_D6); delay(125);

  tone(piezo, NOTE_A5); delay(500); //1sec
  lcd.print(" Steady");
  tone(piezo, NOTE_A5); delay(500);
  noTone(piezo); delay(125);

  tone(piezo, NOTE_F5); delay(500);
  tone(piezo, NOTE_G5); delay(500);

  tone(piezo, NOTE_D5); delay(375); //2sec
  lcd.setCursor(0, 1);
  lcd.print("BANG!");
  lcd.setCursor(12, 1);
  lcd.print("V2.0");
  
  tone(piezo, NOTE_D5); delay(375);
  noTone(piezo); delay(1625); //4sec
}

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
      /*
      //SETTINGS
      if (digitalRead(setting)) {
        setting = tmp;
        lcd.clear();
        lcd.print("Timer Setting:");
        lcd.setCursor(0,1);  
      
     }
     */
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

    for (int i = 0; i < 2; i++)
      for (int TONE = 0; TONE < 12; TONE++) {
        tone(piezo, win[TONE]);
        delay(41);
      }
    noTone(piezo);
    delay(16); //1sec

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
