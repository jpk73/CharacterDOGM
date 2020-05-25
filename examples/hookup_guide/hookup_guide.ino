#include <CharacterDOGM.h>


/*

DOGM204 pin connections:

the bottom row of pins has 3 pins left and 3 pins right, these are pins 1-3 and 20-22:

01 +LED R47 -> 5V or R18 -> 3V3 (these R values fit are for amber LED panel, for other LED colors see data sheet)
02 +LED R47 -> 5V or R18 -> 3V3
03 +LED R47 -> 5V or R18 -> 3V3

20 -LED -> GND (solder all 6 top row pins also from above to the LED panel!)
21 -LED -> GND
22 -LED -> GND

the top row of pins has 22 pins, these are pins 23-44, numbered from right to left:

23 1uF -> GND
24 1uF -> GND
25 1uF -> GND
26 1uF -> GND
27 1uF -> GND
28 1uF -> GND
29 -> 3V3
30 -> 3V3
31 -> 3V3, with 1uF -> GND
32 -> GND
33 -> D7
34 -> D6
35 -> D5
36 -> D4
37 -> 3V3
38 -> 3V3
39 -> 3V3
40 -> 3V3
41 -> EN
42 -> RW -> GND
43 -> RS
44 -> RESET (drive with something like an MCP100-315 or actively with an mcu pin, see data sheet)

*/


// display pins (all pins output only):
#define lcd_rs 1
#define lcd_en 2
#define lcd_d4 8
#define lcd_d5 10
#define lcd_d6 9
#define lcd_d7 0
// this library does not poll the busy flag on d7

CharacterDOGM lcd(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7); // init library

void setup()  {
  lcd.print("hello world! DOGM204");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}

