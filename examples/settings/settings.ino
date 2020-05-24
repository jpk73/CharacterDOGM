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

// special characters:
byte ascending[8] = {0b00100, 0b01001, 0b10010, 0b00100, 0b01001, 0b10010, 0b00100, 0b00000};
byte descending[8] = {0b00100, 0b10010, 0b01001, 0b00100, 0b10010, 0b01001, 0b00100, 0b00000};
byte arrowup[8] = {0b00100, 0b01110, 0b10101, 0b00100, 0b00100, 0b00100, 0b00100, 0b00000};
byte arrowdown[8] = {0b00100, 0b00100, 0b00100, 0b00100, 0b10101, 0b01110, 0b00100, 0b00000};
byte arrowleftup[8] = {B11100, B11000, B10100, B00010, B00001, B00000, B00000, B00000};
byte arrowleftdown[8] = {B00000, B00000, B00000, B00001, B00010, B10100, B11000, B11100};
byte arrowrightup[8] = {B00111, B00011, B00101, B01000, B10000, B00000, B00000, B00000};
byte arrowrightdown[8] = {B00000, B00000, B00000, B10000, B01000, B00101, B00011, B00111};

void setup()  {
  lcd.createChar(0, ascending);
  lcd.createChar(1, descending);
  lcd.createChar(2, arrowup);
  lcd.createChar(3, arrowdown);
  lcd.createChar(4, arrowleftup);
  lcd.createChar(5, arrowrightup);
  lcd.createChar(6, arrowleftdown);
  lcd.createChar(7, arrowrightdown);

  lcd.setContrast(63);            // sets contrast to 0..63
  lcd.setView(LCD_TOPVIEW);       // sets display orientation to LCD_TOPVIEW or LCD_BOTTOMVIEW
  lcd.setLocal(LCD_EUROPEAN);     // sets character table to LCD_EUROPEAN, LCD_CYRILLIC or LCD_ENGLISHJAPANESE
  delay(2500);                    // let the display settle

  lcd.print("hello world! DOGM204");
  lcd.setCursor(0, 2);
  lcd.print("8 custum characters:");

  lcd.setCursor(0, 3);
  lcd.write(0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
  lcd.write(6);
  lcd.write(7);
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}
