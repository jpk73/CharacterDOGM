// https://forum.arduino.cc/index.php?topic=48508.msg347241#msg347241

#include <CharacterDOGM.h>

// display pins (all pins output only):
#define lcd_rs 1
#define lcd_en 2
#define lcd_d4 8
#define lcd_d5 10
#define lcd_d6 9
#define lcd_d7 0
// connect lcd_rw to GND
// connect lcd_reset to a MCP100-315
// this library does not poll the busy flag on d7

CharacterDOGM lcd(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7); // init library

// define integers for the cursor location
int x = 0;
int y = 0;
int j = 0;

void setup() {}

void customclear() {
  // ensures all custom character slots are clear before new custom
  // characters can be defined.
  byte blank[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
  for (int i = 0; i < 8; i++) {
    lcd.createChar(i, blank);
  }
}

// filles a segment one line at a time from left to right.
void customset1() {
  customclear();
  j = 4;
  // arrays to form one set of custom characters
  byte line1[8] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000};
  byte line2[8] = {B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000};
  byte line3[8] = {B11100, B11100, B11100, B11100, B11100, B11100, B11100, B11100};
  byte line4[8] = {B11110, B11110, B11110, B11110, B11110, B11110, B11110, B11110};

  // assignes each segment a write number
  lcd.createChar(0, line1);
  lcd.createChar(1, line2);
  lcd.createChar(2, line3);
  lcd.createChar(3, line4);
}

// fills a segment one line at a time from top to bottom.
void customset2() {
  customclear();
  j = 7;
  // arrays to form one set of custom characters
  byte line1[8] = {B11111, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
  byte line2[8] = {B11111, B11111, B00000, B00000, B00000, B00000, B00000, B00000};
  byte line3[8] = {B11111, B11111, B11111, B00000, B00000, B00000, B00000, B00000};
  byte line4[8] = {B11111, B11111, B11111, B11111, B00000, B00000, B00000, B00000};
  byte line5[8] = {B11111, B11111, B11111, B11111, B11111, B00000, B00000, B00000};
  byte line6[8] = {B11111, B11111, B11111, B11111, B11111, B11111, B00000, B00000};
  byte line7[8] = {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B00000};

  // assignes each segment a write number
  lcd.createChar(0, line1);
  lcd.createChar(1, line2);
  lcd.createChar(2, line3);
  lcd.createChar(3, line4);
  lcd.createChar(4, line5);
  lcd.createChar(5, line6);
  lcd.createChar(6, line7);
}

void mediaChar() {
  customclear();

  byte play[8] = {B00000, B01000, B01100, B01110, B01100, B01000, B00000, B00000};
  byte fastforward[8] = {B00000, B10100, B01010, B00101, B01010, B10100, B00000, B00000};
  byte forward[8] = {B00000, B01000, B00100, B00010, B00100, B01000, B00000, B00000};
  byte fastback[8] = {B00000, B00101, B01010, B10100, B01010, B00101, B00000, B00000};
  byte back[8] = {B00000, B00010, B00100, B01000, B00100, B00010, B00000, B00000};
  byte Stop[8] = {B00000, B11111, B11111, B11111, B11111, B11111, B00000, B00000};
  byte record[8] = {B00000, B01110, B11111, B11111, B11111, B01110, B00000, B00000};
  byte pause[8] = {B00000, B11011, B11011, B11011, B11011, B11011, B00000, B00000};

  // assignes each segment a write number
  lcd.createChar(2, play);
  lcd.createChar(4, fastforward);
  lcd.createChar(3, forward);
  lcd.createChar(0, fastback);
  lcd.createChar(1, back);
  lcd.createChar(6, Stop);
  lcd.createChar(7, record);
  lcd.createChar(5, pause);
}

void cardChar() {
  customclear();

  byte heart[8] = {B00000, B01010, B11111, B11111, B01110, B00100, B00000, B00000};
  byte diamond[8] = {B00000, B00100, B01110, B11111, B01110, B00100, B00000, B00000};
  byte spade[8] = {B00000, B00100, B01110, B11111, B11111, B01110, B00100, B01110};
  byte club[8] = {B00000, B01110, B10101, B11111, B10101, B00100, B01110, B00000};

  // assignes each segment a write number
  lcd.createChar(0, heart);
  lcd.createChar(1, diamond);
  lcd.createChar(2, spade);
  lcd.createChar(3, club);
}

void boarderChar() {
  customclear();

  byte topleft[8] = {B11111, B10000, B10000, B10000, B10000, B10000, B10000, B10000};
  byte topright[8] = {B11111, B00001, B00001, B00001, B00001, B00001, B00001, B00001};
  byte bottomleft[8] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B11111};
  byte bottomright[8] = {B00001, B00001, B00001, B00001, B00001, B00001, B00001, B11111};
  byte leftside[8] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000};
  byte rightside[8] = {B00001, B00001, B00001, B00001, B00001, B00001, B00001, B00001};
  byte top[8] = {B11111, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
  byte bottom[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B11111};

  // assignes each segment a write number
  lcd.createChar(0, topleft);
  lcd.createChar(1, topright);
  lcd.createChar(2, bottomleft);
  lcd.createChar(3, bottomright);
  lcd.createChar(4, leftside);
  lcd.createChar(5, rightside);
  lcd.createChar(6, top);
  lcd.createChar(7, bottom);
}

void arrowChar() {
  customclear();

  byte up[8] = {B00000, B00100, B01110, B10101, B00100, B00100, B00100, B00000};
  byte down[8] = {B00000, B00100, B00100, B00100, B10101, B01110, B00100, B00000};
  byte lowleftcorner[8] = {B00000, B00000, B00001, B10010, B10100, B11000, B11110, B00000,};
  byte lowrightcorner[8] = {B00000, B00000, B10000, B01001, B00101, B00011, B01111, B00000,};
  byte upleftcorner[8] = {B00000, B11110, B11000, B10100, B10010, B00001, B00000, B00000};
  byte uprightcorner[8] = {B00000, B01111, B00011, B00101, B01001, B10000, B00000, B00000};
  byte updown[8] = {B00100, B01110, B10101, B00100, B00100, B10101, B01110,  B00100};

  // assignes each segment a write number
  lcd.createChar(0, up);
  lcd.createChar(1, down);
  lcd.createChar(2, lowleftcorner);
  lcd.createChar(3, lowrightcorner);
  lcd.createChar(4, upleftcorner);
  lcd.createChar(5, uprightcorner);
  lcd.createChar(6, updown);
}

void fillset() {
  for (int i = 0; i < j; i++) {
    lcd.setCursor(x, y);
    lcd.write(i);
    delay(100);
  }
  lcd.setCursor(x, y);
  lcd.write(255);
  delay(100);
  x++;
  if (x < 8) { // cols
    fillset();
  }
  if (x > 7) { // cols - 1
    x = 0;
    y++;
    if (y < 2) { // lines
      fillset();
    }
  }
  if (y > 1) {
    x = 0;
    y = 0;
    lcd.clear();
  }
}

void display_charSet() {
  for (int i = 0; i < 8; i++) {
    lcd.setCursor(x, y);
    lcd.write(i);
    x++;
  }
  x = 0;
}

void loop() {
  mediaChar();
  display_charSet();
  delay(2000);

  cardChar();
  display_charSet();
  delay(2000);

  arrowChar();
  display_charSet();
  delay(2000);

  lcd.clear();
  boarderChar();
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.setCursor(0, 1);
  lcd.write(2);
  lcd.setCursor(15, 0);
  lcd.write(1);
  lcd.setCursor(15, 1);
  lcd.write(3);
  lcd.setCursor(6, 0);
  lcd.write(0);
  lcd.setCursor(9, 0);
  lcd.write(1);
  lcd.setCursor(6, 1);
  lcd.write(2);
  lcd.setCursor(9, 1);
  lcd.write(3);
  lcd.setCursor(7, 0);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(7, 1);
  lcd.write(7);
  lcd.write(7);
  delay(2000);

  lcd.clear();
  x = 0;
  customset1();
  fillset();
  customset2();
  fillset();
  customclear();
  display_charSet();
}
