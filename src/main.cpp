#include "Arduino.h"
#include "regex.h"

extern "C" {
    int _getpid(){ return -1;}
    int _kill(int pid, int sig){ return -1; }
    int _write(){ return -1; }
}

int inputs[] {6,  7,  8,  9};
int outputs[] {10, 11, 12, 15, 16, 17, 18, 19, 20, 21, 22, 23};
int states[48] = {0};
int times[48] = {0};
const int inputsLength = sizeof(inputs) / sizeof(int);
const int outputsLength = sizeof(outputs) / sizeof(int);

int layerModifiers[] {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -7, -6, -1, -2, -3, -4, -5
//       0   1   2   3   4   5 | 6   7   8   9  10  11
};
int modifiers[] {
        KEY_TAB, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        KEY_ESC, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        KEY_LEFT_SHIFT, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, KEY_RIGHT_SHIFT,
        -1, -1, -1, -1, MODIFIERKEY_LEFT_CTRL, KEY_BACKSPACE, KEY_SPACE, KEY_LEFT_ALT, -2, -3, -4, -5
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
int numberFunction[] {
        KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12,
        -1, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, -1,
        -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,      -1,      -1,
        -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,      -1,      -1
};

void setup()
{
    Serial.begin(9600);
    Keyboard.begin();
    for(int i = 0; i < inputsLength; i++)
    {
        pinMode(inputs[i], INPUT_PULLDOWN);
    }
    for(int i = 0; i < outputsLength; i++)
    {
        pinMode(outputs[i], OUTPUT);
        digitalWrite(outputs[i], LOW);
    }
}
void loop()
{
    for(int o = 0; o < outputsLength; o++)
    {
        digitalWrite(outputs[o], HIGH);
        for(int i = 0; i < inputsLength; i++)
        {
            int state = digitalRead(inputs[i]);
            int key = outputsLength * i + o;
            if(state != states[key]) // if there is a change
            {
                if(state)
                {
                    if(millis() - times[key] > 20) {
                        times[key] = millis();
                        states[key] = 1;
                        Serial.println("push");
                        push(key);
                    }
                } else {
                    if(millis() - times[key] > 20) {
                        times[key] = millis();
                        states[key] = 0;
                        Serial.println("anti-push");
                        push(key + 48);
                    }
                }
//                Serial.print(o);
//                Serial.print(" ");
//                Serial.println(i);
            }
        }
        digitalWrite(outputs[o], LOW);
    }
//    delay(1000);
}

//https://github.com/PaulStoffregen/cores/blob/master/teensy/keylayouts.h

// you don't press and release the alt key much, you could use press and release to be a space but when it's used in a combo, it works like the al
