#include "Arduino.h"
#include <vector>

int numKeys = 48;

extern "C" {
    int _getpid(){ return -1;}
    int _kill(int pid, int sig){ return -1; }
    int _write(){ return -1; }
}

#define k0p 0x00
#define k1p 0x01
#define k2p 0x02
#define k3p 0x03
#define k4p 0x04
#define k5p 0x05
#define k6p 0x06
#define k7p 0x07
#define k8p 0x08
#define k9p 0x09
#define k10p 0x0a
#define k11p 0x0b
#define k12p 0x0c
#define k13p 0x0d
#define k14p 0x0e
#define k15p 0x0f
#define k16p 0x10
#define k17p 0x11
#define k18p 0x12
#define k19p 0x13
#define k20p 0x14
#define k21p 0x15
#define k22p 0x16
#define k23p 0x17
#define k24p 0x18
#define k25p 0x19
#define k26p 0x1a
#define k27p 0x1b
#define k28p 0x1c
#define k29p 0x1d
#define k30p 0x1e
#define k31p 0x1f
#define k32p 0x20
#define k33p 0x21
#define k34p 0x22
#define k35p 0x23
#define k36p 0x24
#define k37p 0x25
#define k38p 0x26
#define k39p 0x27
#define k40p 0x28
#define k41p 0x29
#define k42p 0x2a
#define k43p 0x2b
#define k44p 0x2c
#define k45p 0x2d
#define k46p 0x2e
#define k47p 0x2f
#define k0r 0x30
#define k1r 0x31
#define k2r 0x32
#define k3r 0x33
#define k4r 0x34
#define k5r 0x35
#define k6r 0x36
#define k7r 0x37
#define k8r 0x38
#define k9r 0x39
#define k10r 0x3a
#define k11r 0x3b
#define k12r 0x3c
#define k13r 0x3d
#define k14r 0x3e
#define k15r 0x3f
#define k16r 0x40
#define k17r 0x41
#define k18r 0x42
#define k19r 0x43
#define k20r 0x44
#define k21r 0x45
#define k22r 0x46
#define k23r 0x47
#define k24r 0x48
#define k25r 0x49
#define k26r 0x4a
#define k27r 0x4b
#define k28r 0x4c
#define k29r 0x4d
#define k30r 0x4e
#define k31r 0x4f
#define k32r 0x50
#define k33r 0x51
#define k34r 0x52
#define k35r 0x53
#define k36r 0x54
#define k37r 0x55
#define k38r 0x56
#define k39r 0x57
#define k40r 0x58
#define k41r 0x59
#define k42r 0x5a
#define k43r 0x5b
#define k44r 0x5c
#define k45r 0x5d
#define k46r 0x5e
#define k47r 0x5f

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
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
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

std::vector<int*> keymapLayers;
int get(int layer, int key)
{
    if(layer < 0) return -1;
//    if(keymapLayers[layer] == nullptr) return get(layer - 1, key);
    if(keymapLayers[layer][key] != -1)
    {
        return keymapLayers[layer][key];
    } else {
        return get(layer - 1, key);
    }
}
int get(int key) {
    return get(keymapLayers.size() - 1, key);
}

bool isPress(int action)
{
    return action >= 0 and action < numKeys;
}
bool isRelease(int action)
{
    return action > numKeys and action < 2 * 48;
}
void send(int action)
{
    int key;
    if (action >= 0 and action < numKeys)
    {
        key = get(action);
        Keyboard.press(key);
    } else if (action < 2 * 48) {
        key = get(action - 48);
        Keyboard.release(key);
    }
}
bool otherKeysPressed()
{
    for (int i = 0; i < numKeys; ++i) {
        if(i != 41 and i != 42 and states[i] == 1) return true;
    }
    return false;
}
void push(int action)
{
    bool okp;
    static bool k41pressed = false;
    static bool k42pressed = false;
    enum {start, one_thumb, one_thumb_prime, both_thumb, one_mod, both_mod};
    const char* enums[] {"start", "one_thumb", "one_thumb_prime", "both_thumb", "one_mod", "both_mod"};
    static int state;
    switch (state) {
        case start:
            if (action == k41p)
            {
                k41pressed = true;
                state = one_thumb;
            } else if (action == k42p) {
                k42pressed = true;
                state = one_thumb;
            } else send(action);
            break;
        case one_thumb:
            if (action == k41r and k41pressed)
            {
                k41pressed = false;
                Keyboard.press(KEY_BACKSPACE);
                Keyboard.release(KEY_BACKSPACE);
                state = start;
            } else if (action == k42r and k42pressed) {
                k42pressed = false;
                Keyboard.press(KEY_SPACE);
                Keyboard.release(KEY_SPACE);
                state = start;
            } else if (action == k41p and k42pressed) {
                k41pressed = true;
                state = both_thumb;
            } else if (action == k42p and k41pressed) {
                k42pressed = true;
                state = both_thumb;
            } else if (isPress(action) and k41pressed) {
                Keyboard.press(MODIFIERKEY_CTRL);
                send(action);
                state = one_mod;
            } else if(isPress(action) and k42pressed) {
                Keyboard.press(MODIFIERKEY_ALT);
                send(action);
                state = one_mod;
            } else send(action);
            break;
        case both_thumb:
            if (!k41pressed or !k42pressed) Serial.println("something wrong 1488853974");
            if (action == k41r) {
                k41pressed = false;
                Keyboard.press(KEY_DELETE);
                Keyboard.release(KEY_DELETE);
                state = one_thumb_prime;
            } else if (action == k42r) {
                k42pressed = false;
                Keyboard.press(KEY_ENTER);
                Keyboard.release(KEY_ENTER);
                state = one_thumb_prime;
            } else {
                Keyboard.press(MODIFIERKEY_CTRL);
                Keyboard.press(MODIFIERKEY_ALT);
                state = both_mod;
                send(action);
            }
            break;
        case both_mod:
            okp = otherKeysPressed();
            if (not okp and action == k41r)
            {
                k41pressed = false;
                Keyboard.release(MODIFIERKEY_CTRL);
                state = one_thumb_prime;
            } else if (not okp and action == k42r) {
                k42pressed = false;
                Keyboard.release(MODIFIERKEY_ALT);
                state = one_thumb_prime;
            } else if (okp and action == k41r)
            {
                k41pressed = false;
                Keyboard.release(MODIFIERKEY_CTRL);
                state = one_mod;
            } else if (okp and action == k42r) {
                k42pressed = false;
                Keyboard.release(MODIFIERKEY_ALT);
                state = one_mod;
            } else send(action);
            break;
        case one_mod:
            if (not (not k41pressed and k42pressed or k41pressed and not k42pressed)) Serial.println("problem 1488855253");
            if (action == k41p and !k41pressed) {
                k41pressed = true;
                Keyboard.press(MODIFIERKEY_CTRL);
                state = both_mod;
            } else if (action == k42p and !k42pressed) {
                k42pressed = true;
                Keyboard.press(MODIFIERKEY_ALT);
                state = both_mod;
            } else if (action == k41r and k41pressed) {
                k41pressed = false;
                Keyboard.release(MODIFIERKEY_CTRL);
                state = start;
            } else if (action == k42r and k42pressed) {
                k42pressed = false;
                Keyboard.release(MODIFIERKEY_ALT);
                state = start;
//            } else if (not otherKeysPressed()) {
//                send(action);
//                if (k41pressed) Keyboard.release(MODIFIERKEY_CTRL);
//                if (k42pressed) Keyboard.release(MODIFIERKEY_ALT);
//                state = one_thumb_prime;
            } else send(action);
            break;
        case one_thumb_prime:
            if (not (not k41pressed and k42pressed or k41pressed and not k42pressed)) Serial.println("problem 1488856884");
            if (action == k41p and not k41pressed)
            {
                k41pressed = true;
                state = both_thumb;
            } else if (action == k42p and not k42pressed) {
                k42pressed = true;
                state = both_thumb;
            } else if (action == k41r and k41pressed) {
                k41pressed = false;
                state = start;
            } else if (action == k42r and k42pressed) {
                k42pressed = false;
                state = start;
            } else if (k41pressed) {
                Keyboard.press(MODIFIERKEY_CTRL);
                send(action);
                state = one_mod;
            } else if (k42pressed) {
                Keyboard.press(MODIFIERKEY_ALT);
                send(action);
                state = one_mod;
            }
            break;
    }
    if(k41pressed) Serial.println("k41pressed");
    if(k42pressed) Serial.println("k42pressed");
    Serial.println(enums[state]);
    Serial.println();
}

void setup()
{
    Serial.begin(9600);
    Keyboard.begin();
    keymapLayers.push_back(modifiers);
    keymapLayers.push_back(dvorak);
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
