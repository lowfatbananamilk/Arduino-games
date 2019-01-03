#include "game.h"
#include "namespace.h"
using namespace globalVar;

// Wirings ---------------------------------------------
#include <LiquidCrystal.h>
//enum lcd {D7 = 2, D6, D5, D4, E = 11, RS = 12};
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

#include "pitches.h"
const int PIZO = 9;

const int BLUE = 6;
const int GREEN = 7;
const int WHITE = 8;

const int LIGHT = 13;

// Games -----------------------------------------------
#include "ready_steady_bang.cpp"
String title[] = {"ReadySteadyBang", "TEST"};
int num = 2;
Game *game;

// Switches --------------------------------------------
bool blue = false;
bool green = false;
bool white = false;
int select = 0;

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
      if (select > num)
        select = 0;
    }
    if (digitalRead(BLUE)) {
      select--;
      blue = true;
      if (select < 0)
        select = num;
    }
    if (digitalRead(WHITE))
      white = true;
  } while(!blue && !green && !white);

  if (white)
    switch(select) {
    case 0:
      game = new RSB; break;
    case 1:
      //game = new TEST;
      break;
    }

  if (game) {
    game->intro();
    delay(1000);
    delete game;
  }
}
