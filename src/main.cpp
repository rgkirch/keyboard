#include "Arduino.h"

char inputs[] {6,  7,  8,  9};
char outputs[] {10, 11, 12, 15, 16, 17, 18, 19, 20, 21, 22, 23};
int modifiers[] {
        KEY_TAB,        -1,            -1,            -1,                    -1,           -1,            -1,        -1,        -1,        -1,              -1, -1,
        KEY_ESC,        -1,            -1,            -1,                    -1,           -1,            -1,        -1,        -1,        -1,              -1, -1,
        KEY_LEFT_SHIFT, -1,            -1,            -1,                    -1,           -1,            -1,        -1,        -1,        -1,              -1, KEY_RIGHT_SHIFT,
        KEY_ESC,        KEY_LEFT_GUI,  KEY_LEFT_GUI,  MODIFIERKEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_BACKSPACE, KEY_ENTER, KEY_SPACE, -2, -3, -4, -5
};
int qwerty[] {
        -1, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I,     KEY_O,      KEY_P,         KEY_LEFT_BRACE
        -1, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K,     KEY_L,      KEY_SEMICOLON, KEY_QUOTE,
        -1, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH,     -1,
        -1, -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,        -1,         -1,             -1
};
int dvorak[] {
        -1, KEY_QUOTE,     KEY_COMMA, KEY_PERIOD, KEY_P, KEY_Y, KEY_F, KEY_G, KEY_C, KEY_R, KEY_L, KEY_SLASH,
        -1, KEY_A,         KEY_O,     KEY_E,	  KEY_U, KEY_I, KEY_D, KEY_H, KEY_T, KEY_N, KEY_S, KEY_MINUS,
        -1, KEY_SEMICOLON, KEY_Q,	  KEY_J,      KEY_K, KEY_X, KEY_B, KEY_M, KEY_W, KEY_V, KEY_Z, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};
int function[] {
        KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12,
        -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,      -1,      -1,
        -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,      -1,      -1,
        -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,      -1,      -1
};
void(*customFunctions[4])() {};
bool matrix[48] = {false}; // state of keys last scanned (pressed on not pressed) // 12 * 4
int times[48] = {0}; // state of keys last scanned (pressed on not pressed) // 12 * 4
int getKey()
{
}
void release(int location)
{
    Keyboard.release(keymap[location]);
}
void press(int location)
{
    Keyboard.press(keymap[location]);
}
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
                    if(millis() - times[location] > 20) {
                        times[location] = millis();
                        matrix[location] = 1;
                        press(location);
                    }
                } else {
                    if(millis() - times[location] > 20) {
                        times[location] = millis();
                        matrix[location] = 0;
                        release(location);
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

//https://github.com/PaulStoffregen/cores/blob/master/teensy/keylayouts.h
