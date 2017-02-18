#include "Arduino.h"

//#define KEY_LEFT_CTRL '0x80'
////#define KEY_LEFT_SHIFT '0x81'
//#define KEY_LEFT_ALT '0x82'
//#define KEY_LEFT_GUI '0x83'
//#define KEY_RIGHT_CTRL '0x84'
//#define KEY_RIGHT_SHIFT '0x85'
//#define KEY_RIGHT_ALT '0x86'
//#define KEY_RIGHT_GUI '0x87'
//#define KEY_UP_ARROW '0xDA'
//#define KEY_DOWN_ARROW '0xD9'
//#define KEY_LEFT_ARROW '0xD8'
//#define KEY_RIGHT_ARROW '0xD7'
//#define KEY_BACKSPACE '0xB2'
//#define KEY_TAB '0xB3'
//#define KEY_RETURN '0xB0'
//#define KEY_ESC '0xB1'
//#define KEY_INSERT '0xD1'
//#define KEY_DELETE '0xD4'
//#define KEY_PAGE_UP '0xD3'
//#define KEY_PAGE_DOWN '0xD6'
//#define KEY_HOME '0xD2'
//#define KEY_END '0xD5'
//#define KEY_CAPS_LOCK '0xC1'
//#define KEY_F1 '0xC2'
//#define KEY_F2 '0xC3'
//#define KEY_F3 '0xC4'
//#define KEY_F4 '0xC5'
//#define KEY_F5 '0xC6'
//#define KEY_F6 '0xC7'
//#define KEY_F7 '0xC8'
//#define KEY_F8 '0xC9'
//#define KEY_F9 '0xCA'
//#define KEY_F10 '0xCB'
//#define KEY_F11 '0xCC'
//#define KEY_F12 '0xCD'


//uint16_t KEY_LEFT_SHIFT = 0xff << 8 || 0xe1;
char inputs[] = {14, 15, 16, 17};
char outputs[] = {23, 18, 19, 20, 21, 22, 7, 8, 9, 10, 11, 12};
int keymap[] = {KEY_TAB, '\'', ',', '.', 'p', 'y', 'f', 'g', 'c', 'r', 'l', '/',
KEY_ESC, 'a', 'o', 'e', 'u', 'i', 'd', 'h', 't', 'n', 's', '-',
KEY_LEFT_SHIFT, ';', 'q', 'j', 'k', 'x', 'b', 'm', 'w', 'v', 'z', KEY_RIGHT_SHIFT,
MODIFIERKEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, MODIFIERKEY_LEFT_CTRL, KEY_BACKSPACE, ' ', ' ', KEY_SPACE, KEY_ENTER, KEY_RIGHT_ARROW, KEY_RIGHT_ALT, KEY_RIGHT_CTRL};
bool matrix[48] = {false}; // state of keys last scanned (pressed on not pressed) // 12 * 4
int times[48] = {0}; // state of keys last scanned (pressed on not pressed) // 12 * 4
// in 14, 15, 16, 17
// out  7,  8,  9, 10, 11, 12, 18, 19, 20, 21, 22
void setup()
{

//    memset(matrix, 0, 48 * sizeof(char));
    Serial.begin(9600);
    delay(1000);
    Serial.print("test print");
    Keyboard.begin();
//    Mouse.begin();
    for(char i = 0; i < sizeof(inputs) / sizeof(char); i++)
    {
        pinMode(inputs[i], INPUT_PULLDOWN);
    }
    for(char i = 0; i < sizeof(outputs) / sizeof(char); i++)
    {
        pinMode(outputs[i], OUTPUT);
        digitalWrite(outputs[i], LOW);
    }

    delay(1000);
}
void loop()
{
//    Mouse.move(4, 0);
//    delay(25);
//    Mouse.move(-4, 0);
//    delay(25);
//    Serial.println("loop");
//    delay(200);
//    for (auto c : matrix) {
//        Serial.print(c);
//        Serial.print(" ");
//    }
//    Serial.println();
    for(int i = 0; i < sizeof(outputs) / sizeof(char); i++)
    {
        digitalWrite(outputs[i], HIGH);
        for(int j = 0; j < sizeof(inputs) / sizeof(char); j++)
        {
            bool state = digitalRead(inputs[j]);
//            Serial.print("state ");
//            Serial.println(state);
            int location = (sizeof(outputs) / sizeof(char)) * j + i;
            if(state != matrix[location]) // if there is a change
            {
                if(state)
                {
                    if(millis() - times[location] > 30) {
                        times[location] = millis();
                        matrix[location] = 1;
                        Keyboard.press(keymap[location]);
                    }
                } else {
                    if(millis() - times[location] > 30) {
                        times[location] = millis();
                        matrix[location] = 0;
                        Keyboard.release(keymap[location]);
                    }
                }
//                Serial.print(i);
//                Serial.print(" ");
//                Serial.println(j);
            }
        }
        digitalWrite(outputs[i], LOW);
    }
//    delay(1000);
}

