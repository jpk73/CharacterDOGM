#ifndef CharacterDOGM_h
#define CharacterDOGM_h
#include "Print.h"

#define LCD_TOPVIEW             0x05
#define LCD_BOTTOMVIEW          0x06
#define LCD_EUROPEAN            0x00
#define LCD_CYRILLIC            0x04
#define LCD_ENGLISHJAPANESE     0x0C

class CharacterDOGM: public Print {
  public:
    CharacterDOGM(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    void begin(uint8_t cols, uint8_t rows);
    void clear();
    void home();
    void setCursor(uint8_t, uint8_t);
    void noDisplay();
    void display();
    void createChar(uint8_t, uint8_t[]);
    void setContrast(unsigned char contr);
    void setLocal(unsigned char rom);
    void setView(unsigned char view);
    void command(uint8_t);
    virtual size_t write(uint8_t);

  private:
    void send(uint8_t, uint8_t);
    void pulseEnable();
    void write4bits(uint8_t);
    uint8_t _rs_pin;
    uint8_t _en_pin;
    uint8_t _data_pins[4];
    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;
    uint8_t _numlines;
};

#endif
