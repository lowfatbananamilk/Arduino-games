// Wirings ---------------------------------------------
#include <LiquidCrystal.h>
enum lcd {D7 = 2, D6, D5, D4, E = 11, RS = 12};
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

#include "pitches.h"
const int PIZO = 9;

const int BLUE = 6;
const int GREEN = 7;
const int WHITE = 8;

const int LIGHT = 13;

// Switches --------------------------------------------
bool blue = false;
bool green = false;
bool white = false;

int select = 0;

// Games List ------------------------------------------
String title[] = {"ReadySteadyBang", "TEST"};
int num = 2;

class Game {
public:
  virtual void intro() = 0;
};
Game* game;

// Global Functions ------------------------------------
void play(int* pitchArr, int* lenghtArr, int size) {
  for (int i = 0; i < size; i++) {
    tone(PIZO, pitchArr[i]);
    delay(lenghtArr[i]);
  }
  noTone(PIZO);
}

// Games -----------------------------------------------
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
    //noTone(PIZO);

    lcd.print(" Steady");
    play(introM2, introM2L, 5); //2sec
    //noTone(PIZO);

    lcd.setCursor(0, 1);
    lcd.print("BANG!");
    lcd.setCursor(12, 1);
    lcd.print("V2.0");
    
    play(introM3, introM3L, 2); //4sec
    //noTone(PIZO);    
    }
    
};






// -----------------------------------------------------
void setup() {
  pinMode(BLUE, INPUT);
  pinMode(GREEN, INPUT);
  pinMode(WHITE, INPUT);

  pinMode(LIGHT, OUTPUT);

  lcd.begin(16, 2);
}

// -----------------------------------------------------
void loop() {
  blue = false;
  green = false;
  white = false;
  lcd.clear();

  lcd.print("Select Game!");
  lcd.setCursor(0, 1);
  lcd.print(title[select]);

  do {
    if (digitalRead(GREEN)) {
      select++;
      green = true;
      if (select > num - 1)
        select = 0;
    }
    if (digitalRead(BLUE)) {
      select--;
      blue = true;
      if (select < 0)
        select = num - 1;
    }
    if (digitalRead(WHITE))
      white = true;

    delay(150);
  } while(!blue && !green && !white);

  if (white) {
    switch(select) {
    case 0:
      game = new RSB; break;
    case 1:
      //game = new TEST;
      lcd.clear();
      lcd.print("TEST intro");
      delay(1000);
      return;
    }

    game->intro();
    delay(1000);
    delete game;
  }
}
