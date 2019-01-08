#include "pitches.h"
static int win[] = {NOTE_A5, NOTE_B5, NOTE_C5, NOTE_B5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_D5,
                    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_E5};

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int p1pin = 6, p2pin = 7, piezo = 8, vr = 9, setting = 10;

int p1stat, p2stat, p1win = 0, p2win = 0;
unsigned long start, current, p1time, p2time, timer;

void setup() {
  for (int i = 6; i <= 8; i++)
    pinMode(i, OUTPUT);

  lcd.begin(16, 2);

  Serial.begin(9600);
  Serial.println("Ready Steady BANG!! ver 2.0");
}

void loop() {  
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

  while(1) {
    Serial.println("");
    lcd.clear();
    p1stat = false;
    p2stat = false;

    lcd.print("Press buttons");
    lcd.setCursor(0, 1);
    lcd.print("when ready.");
    lcd.blink();
  
    while(!p1stat || !p2stat) {
      if (digitalRead(p1pin) && !p1stat) {
        p1stat = true;
        lcd.setCursor(12, 1);
        lcd.print("P1");
        lcd.setCursor(10, 1);
        tone(piezo, NOTE_G6, 500);
        Serial.println("P1 Ready");
      }
      if (digitalRead(p2pin) && !p2stat) {
        p2stat = true;
        lcd.setCursor(14, 1);
        lcd.print("P2");
        lcd.setCursor(10, 1);
        tone(piezo, NOTE_G6, 500);
        Serial.println("P2 Ready");
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
    Serial.println("Game Start\n");
    delay(1000);
    
    lcd.clear();
    p1stat = false;
    p2stat = false;

    timer = random(6000);
    Serial.print("The time will be ");
    Serial.print(timer / 1000);
    Serial.print(".");
    Serial.print(timer % 1000);
    Serial.println("s.\n");
    
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
    Serial.println("BANG!!");

    while (!p1stat || !p2stat) {
      current = millis();
      
      lcd.setCursor(0, 1);
      lcd.print("time: ");
      lcd.print(current - start);

      if (digitalRead(p1pin) && !p1stat) {
        p1time = current - start;
        p1stat = true;
        
        Serial.print("P1 time: ");
        Serial.print(p1time);
        Serial.println("ms.");
      }

      if (digitalRead(p2pin) && !p2stat) {
        p2time = current - start;
        p2stat = true;
        
        Serial.print("P2 time: ");
        Serial.print(p2time);
        Serial.println("ms.");
      }
    }  

    if (p1time < p2time) {
      Serial.println("\nP1 won!");
      p1win++;
    }
    else {
      Serial.println("\nP2 won!");
      p2win++;
    }
    Serial.println("P1 : P2 ");
    Serial.print(p1win);
    Serial.print(" : ");
    Serial.println(p2win);
        
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
