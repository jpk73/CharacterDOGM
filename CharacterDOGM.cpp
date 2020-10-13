#include "CharacterDOGM.h"
#include "Arduino.h"

CharacterDOGM::CharacterDOGM(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
  _rs_pin = rs;
  _en_pin = en;
  _data_pins[0] = d4;
  _data_pins[1] = d5;
  _data_pins[2] = d6;
  _data_pins[3] = d7;
  _displayfunction = 0x28 | 0x00;
  begin(20, 4);
}

void CharacterDOGM::begin(uint8_t cols, uint8_t lines) {
  _numlines = lines;

  pinMode(_rs_pin, OUTPUT); digitalWriteFast(_rs_pin, LOW);
  pinMode(_en_pin, OUTPUT); digitalWriteFast(_en_pin, LOW);
  for (int i = 0; i < 4; i++) {
    pinMode(_data_pins[i], OUTPUT);
    digitalWriteFast(_data_pins[i], LOW);
  }

  delayMicroseconds(50); command(0x33);         // switch to 8 bit data length
  delayMicroseconds(50); command(0x32);         // switch to 4 bit data length
  delayMicroseconds(50); command(0x2A);         // 4-Bit data length extension Bit RE=1; REV=0
  delayMicroseconds(50); command(0x09);         // 4 line display
  delayMicroseconds(50); command(0x05);         // Bottom view: 0x06 / Top view: 0x05
  delayMicroseconds(50); command(0x1E);         // Bias setting BS1=1
  delayMicroseconds(50); command(0x29);         // 4-Bit data length extension Bit RE=0; IS=1
  delayMicroseconds(50); command(0x1B);         // BS0=1 -> Bias=1/6
  delayMicroseconds(50); command(0x6E);         // Devider on and set value
  delayMicroseconds(50); command(0x57);         // Booster on and set contrast (BB1=C5, DB0=C4)
  delayMicroseconds(50); command(0x72);         // Set contrast (DB3-DB0=C3-C0)
  delayMicroseconds(50); command(0x28);         // 4-Bit data length extension Bit RE=0; IS=0
  clear(); display();
}

void CharacterDOGM::clear(void) {
  delayMicroseconds(50);
  command(0x01);
  home();
}

void CharacterDOGM::home() {
  delayMicroseconds(50);
  command(0x80);
  delayMicroseconds(50);
}

void CharacterDOGM::setCursor(uint8_t col, uint8_t row) {
  uint8_t row_offsets[] = { 0x00, 0x20, 0x40, 0x60 };
  if ( row >= _numlines ) {
    row = 0;
  }
  command(0x80 | (col + row_offsets[row]));
}

void CharacterDOGM::display() {
  _displaycontrol |= 0x04;
  command(0x08 | _displaycontrol);
}

void CharacterDOGM::noDisplay() {
  _displaycontrol &= ~0x04;
  command(0x08 | _displaycontrol);
}

void CharacterDOGM::createChar(unsigned char postion, unsigned char *data) {
  unsigned char i = 0;
  command(0x40 + 8 * postion);
  for (i = 0; i < 8; i++) {
    write(data[i]);
  }
  clear();
}

void CharacterDOGM::setContrast(unsigned char contr) { // sets contrast to 0..63
  command(0x29);
  command(0x54 | (contr >> 4));
  command(0x70 | (contr & 0x0F));
  command(0x28);
}

void CharacterDOGM::setLocal(unsigned char rom) { // sets character table to LCD_EUROPEAN, LCD_CYRILLIC or LCD_ENGLISHJAPANESE
  command(0x2A);
  command(0x72);
  write(rom);
  command(0x28);
  clear();
}

void CharacterDOGM::setView(unsigned char view) { // sets display orientation to LCD_TOPVIEW or LCD_BOTTOMVIEW
  command(0x2A);
  command(view);
  command(0x28);
}

inline void CharacterDOGM::command(uint8_t value) {
  send(value, LOW);
}

inline size_t CharacterDOGM::write(uint8_t value) {
  send(value, HIGH);
  return 1;
}

void CharacterDOGM::send(uint8_t value, uint8_t mode) {
  digitalWriteFast(_rs_pin, mode);
  write4bits(value >> 4);
  write4bits(value);
}

void CharacterDOGM::write4bits(uint8_t value) {
  for (int i = 0; i < 4; i++) {
    digitalWriteFast(_data_pins[i], (value >> i) & 0x01);
  }
  pulseEnable();
}

void CharacterDOGM::pulseEnable(void) {
  digitalWriteFast(_en_pin, HIGH);
  digitalWriteFast(_en_pin, LOW);
}
