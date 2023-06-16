
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/21);


void setup(void)
{
    Serial.begin(9600);
    u8g2.begin();
    u8g2.enableUTF8Print();        // enable UTF8 support for the Arduino print() function
    pinMode(18,INPUT);
    pinMode(19,INPUT);
    pinMode(23,INPUT);
    pinMode(25,INPUT);
    pinMode(26,INPUT);
    pinMode(27,INPUT);
    pinMode(32,INPUT);
    pinMode(33,INPUT);
}

void loop(void)
{
    int a = GetFre();
    int b = GetNum();
    u8g2.setFont(u8g2_font_unifont_t_chinese2);  // use chinese2 for all the glyphs of "你好世界"
    u8g2.setFontDirection(0);
    u8g2.clearBuffer();
    u8g2.setCursor(0, 15);
    u8g2.print("频点:");
    u8g2.print(a);
    u8g2.setCursor(0, 40);
    u8g2.print("车号:");        // Chinese "Hello World"
    u8g2.print(b);
    u8g2.sendBuffer();
    uint8_t buffer[2];
    buffer[0] =0xf0 + a;
    buffer[1] =0xa0 + b;
    Serial.write(buffer,2);
    delay(100);
}

int GetFre(){
  return digitalRead(26)*8+digitalRead(25)*4+digitalRead(33)*2+digitalRead(32);
}

int GetNum(){
  return digitalRead(27)*8+digitalRead(19)*4+digitalRead(23)*2+digitalRead(18);
}
