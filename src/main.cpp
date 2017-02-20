#include "Arduino.h"

// because it's c and not c++ - don't call get(int, int) just call get(int)
// don't modify keymap

typedef int pin;
typedef int key;
typedef int time;
pin inputs[] {6,  7,  8,  9};
pin outputs[] {10, 11, 12, 15, 16, 17, 18, 19, 20, 21, 22, 23};
key states[48] = {0};
time times[48] = {0};
const int inputsLength = sizeof(inputs) / sizeof(pin);
const int outputsLength = sizeof(outputs) / sizeof(pin);
const int statesLength = sizeof(states) / sizeof(key);
const int timesLength = sizeof(times) / sizeof(time);

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

static const int keyMapLength = 4;
static int *keymap[keyMapLength] {modifiers, dvorak, nullptr, nullptr};
int get(int layer, int key)
{
    if(layer < 0) return 0;
    if(keymap[layer] == nullptr) return get(layer - 1, key);
    if(keymap[layer][key] > 0)
    {
        return keymap[layer][key];
    } else return get(layer - 1, key);
}
int get(int key)
{
    return get(keyMapLength, key);
}
void action(int key, int action)
{
    if(get(key) > 0) if(action) Keyboard.press(get(key)); else Keyboard.release(get(key));
}


void setup()
{
//    memset(states, 0, 48 * sizeof(char));
    Serial.begin(9600);
    delay(1000);
    Keyboard.begin();
//    Mouse.begin();
    for(char i = 0; i < inputsLength; i++)
    {
        pinMode(inputs[i], INPUT_PULLDOWN);
    }
    for(char i = 0; i < outputsLength; i++)
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
//    for (auto c : states) {
//        Serial.print(c);
//        Serial.print(" ");
//    }
//    Serial.println();
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
                        action(key, 1);
                    }
                } else {
                    if(millis() - times[key] > 20) {
                        times[key] = millis();
                        states[key] = 0;
                        action(key, 0);
                    }
                }
                Serial.print(o);
                Serial.print(" ");
                Serial.println(i);
            }
        }
        digitalWrite(outputs[o], LOW);
    }
//    delay(1000);
}

//https://github.com/PaulStoffregen/cores/blob/master/teensy/keylayouts.h
