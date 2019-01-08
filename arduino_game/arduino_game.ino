// Wirings ---------------------------------------------
#include <LiquidCrystal.h>
enum lcd {D7 = 2, D6, D5, D4, E = 11, RS = 12};
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

#include "pitches.h"
const int PIZO = 9;

const int BLUE = 6;
const int GREEN = 7;
const int WHITE = 8;

const int LIGHT = 13; // Onboard LED

// Switches --------------------------------------------
bool blue;
bool green;
bool white;

int select = 0;

// Game List -------------------------------------------
String title[] = {"ReadySteadyBang", "TEST"}; // <= 16 char
int num = 2;

class Game {
protected:
  int p1win, p2win;
public:
  Game() : p1win(0), p2win(0) {}

  virtual void intro() = 0;
  virtual void playGame() = 0;
  virtual void score() = 0;
};
Game* game;

// Global Functions ------------------------------------
  // The LCD display makes buzzing sounds and flickers when the PIZO is in use...
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
    unsigned long start, current, timer;
    unsigned long p1time, p2time;

public:
    // ---------------------------------------------------------------------------------------------
    void intro() override {
    lcd.clear();
    lcd.print("Ready");
    play(introM1, introM1L, 5); // 1sec

    lcd.print(" Steady");
    play(introM2, introM2L, 5); // 2sec

    lcd.setCursor(0, 1);
    lcd.print("BANG!");
    lcd.setCursor(12, 1);
    lcd.print("V2.0");
    
    play(introM3, introM3L, 2); // 4sec
    }

    // ---------------------------------------------------------------------------------------------
    void playGame() override {
      lcd.clear();
      lcd.print("Press buttons");
      lcd.setCursor(0, 1);
      lcd.print("when ready.");
      lcd.blink();

      do { // game queue
        if (digitalRead(BLUE) && !blue) {
          blue = true;

          lcd.setCursor(12, 1);
          lcd.print("P1");

          lcd.setCursor(11, 1);
          tone(PIZO, NOTE_G6, 500);
        }
        if (digitalRead(GREEN) && !green) {
          green = true;

          lcd.setCursor(14, 1);
          lcd.print("P2");

          lcd.setCursor(11, 1);
          tone(PIZO, NOTE_G6, 500);
        }
      } while (!blue || !green);
      
      blue = green = false;
      timer = random(6000); // Set radomized time - control Max. here

      delay(1000);
      lcd.clear();
      lcd.print("Ready");
      tone(PIZO, NOTE_C5, 500);
      delay(2000);
      
      lcd.clear();
      lcd.print("Steady");
      tone(PIZO, NOTE_C5, 500);
      delay(timer);

      lcd.clear();
      lcd.print("BANG!!");
      start = millis(); // Start timer
      tone(PIZO, NOTE_G5, 500);

      do {
        current = millis();
        
        lcd.setCursor(0, 1);
        lcd.print("time: ");
        lcd.print(current - start); // past time

        if (digitalRead(BLUE) && !blue) {
          p1time = current - start;
          blue = true;
        }

        if (digitalRead(GREEN) && !green) {
          p2time = current - start;
          green = true;
        }
      }  while (!blue || !green);
      blue = green = false;

      if (p1time < p2time)
        p1win++;
      else if (p1time > p2time)
        p2win++;
      else {
        p1win++;
        p2win++;
      }

      lcd.noBlink();
      delay(2000);
    }

    // ---------------------------------------------------------------------------------------------
    void score() override {
      lcd.clear();
      if (p1win)
        lcd.print(p1win); // if p1 have score, display it
      lcd.setCursor(1, 0);
      lcd.print("  P1: ");
      lcd.print(p1time / 1000);
      lcd.print(".");
      lcd.print(p1time % 1000);
      
      delay(1000);
      lcd.setCursor(0, 1);
      if (p2win)
        lcd.print(p2win); // if p2 have score, display it
      lcd.setCursor(1, 1);
      lcd.print("  P2: ");
      lcd.print(p2time / 1000);
      lcd.print(".");
      lcd.print(p2time % 1000);

      play(winM, winML, 12);
      delay(16); //1sec

      if (p1time < p2time) {
        for (int i = 0; i < 4; i++) { // Blink "P1: TIME" 4 times
          lcd.home(); // setCursor(0, 0);
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

      else if (p1time > p2time){
        for (int i = 0; i < 4; i++) { // Blink "P2: TIME" 4 times
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

      else {
        for (int i = 0; i < 4; i++) { // Blink both 4 times
          lcd.home(); // setCursor(0, 0);
          lcd.print(p1win);
          lcd.setCursor(1, 0);
          lcd.print("            TIE");
          lcd.setCursor(0, 1);
          lcd.print(p2win);
          lcd.setCursor(1, 1);
          lcd.print("            TIE");
          delay(500);

          lcd.setCursor(1, 0);
          lcd.print("  P1: ");
          lcd.print(p1time / 1000);
          lcd.print(".");
          lcd.print(p1time % 1000);    
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
};






// -----------------------------------------------------
void setup() {
  pinMode(BLUE, INPUT);
  pinMode(GREEN, INPUT);
  pinMode(WHITE, INPUT);

  //pinMode(LIGHT, OUTPUT); // Not in use

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

    delay(140);
  } while(!blue && !green && !white);

  blue = false;
  green = false;

  if (white) {
    white = false;

    switch(select) {
    case 0:
      game = new RSB; break;
    case 1:
      //game = new TEST; // Example
      lcd.clear();
      lcd.print("TEST intro");
      delay(1000);
      return; // Restart loop()
    }

    if (!game) { // Fail to allocate dynamic memory
      lcd.clear();
      lcd.print("Could not load");
      lcd.setCursor(0, 1);
      lcd.print("the game.");

      delay(2000);
      return;
    }

    game->intro();
    do {
      game -> playGame();

      game -> score();
    } while(true); // Program does not pass this line.. yet!

    delete game;
    return; // Restart loop()
  }
}
