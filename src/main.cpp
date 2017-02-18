#include "Arduino.h"

char inputs[] = {6,  7,  8,  9};
char outputs[] = {10, 11, 12, 15, 16, 17, 18, 19, 20, 21, 22, 23};
int keymap[] = {KEY_TAB, '\'', ',', '.', 'p', 'y', 'f', 'g', 'c', 'r', 'l', KEY_SLASH,
KEY_ESC, 'a', 'o', 'e', 'u', 'i', 'd', 'h', 't', 'n', 's', '-',
KEY_LEFT_SHIFT, ';', 'q', 'j', 'k', 'x', 'b', 'm', 'w', 'v', 'z', KEY_RIGHT_SHIFT,
, KEY_LEFT_GUI, KEY_LEFT_ALT, MODIFIERKEY_LEFT_CTRL, KEY_BACKSPACE, ' ', ' ', KEY_SPACE, KEY_ENTER, KEY_RIGHT_ARROW, KEY_RIGHT_ALT, KEY_RIGHT_CTRL};
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

