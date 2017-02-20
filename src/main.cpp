#include "Arduino.h"
#include <vector>
#include <algorithm>
#include <unordered_set>

std::unordered_set<int> keysCurrentlyPressed;
std::vector<int*>keymapLayers;
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
        -1, KEY_ESC,        KEY_LEFT_GUI,  KEY_LEFT_GUI, MODIFIERKEY_LEFT_CTRL, KEY_BACKSPACE, KEY_SPACE, KEY_LEFT_ALT, -2, -3, -4, -5
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
int numberRow[] {
        -1, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, -1,
        -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,      -1,      -1,
        -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,      -1,      -1,
        -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,     -1,      -1,      -1
};


int get(int layer, int key)
{
    if(layer < 0) return 0;
//    if(keymapLayers[layer] == nullptr) return get(layer - 1, key);
    if(keymapLayers[layer][key] != -1)
    {
        return keymapLayers[layer][key];
    } else {
        return get(layer - 1, key);
    }
}

void action(int key, int action)
{
    int val = get(keymapLayers.size() - 1, key);
    switch (val) {
        case -1: // wont happen
            break;
        case -2:
            if (action)
            {
                keymapLayers.push_back(numberRow);
            } else {
                auto it = std::find(keymapLayers.begin(), keymapLayers.end(), numberRow);
                if (it != keymapLayers.end()) keymapLayers.erase(it);
            }
            break;
        case -3:
            if (action)
            {
                keymapLayers.push_back(function);
            } else {
                auto it = std::find(keymapLayers.begin(), keymapLayers.end(), function);
                keymapLayers.erase(it);
            }
            break;
            // bug, if you press shift, press space, release shift, release space it will have added a delete to the set and try to remove a backspace from the set
        case KEY_BACKSPACE:
            if (keysCurrentlyPressed.find(KEY_LEFT_SHIFT) != keysCurrentlyPressed.end() || keysCurrentlyPressed.find(KEY_RIGHT_SHIFT) != keysCurrentlyPressed.end()) {
                if(action)
                {
                    keysCurrentlyPressed.insert(KEY_DELETE);
                    Keyboard.press(KEY_DELETE);
                } else {
                    auto it = keysCurrentlyPressed.find(KEY_DELETE);
                    if (it != keysCurrentlyPressed.end()) keysCurrentlyPressed.erase(it);
                    Keyboard.release(KEY_DELETE);
                }
            }
            break;
        default:
            if (action) {
                keysCurrentlyPressed.insert(val);
                Keyboard.press(val);
            } else {
                auto it = keysCurrentlyPressed.find(val);
                if (it != keysCurrentlyPressed.end()) keysCurrentlyPressed.erase(it);
                Keyboard.release(val);
            }
            break;
    }
}

void setup()
{
    keymapLayers.push_back(modifiers);
    keymapLayers.push_back(dvorak);
    Serial.begin(9600);
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
}
void loop()
{
//    Serial.println("loop");
//    Mouse.move(4, 0);
//    delay(25);
//    Mouse.move(-4, 0);
//    delay(25);
//    Serial.println("loop");
//    delay(200);
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
