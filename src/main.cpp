#include "Arduino.h"
#include <vector>

int numKeys = 48;

extern "C" {
    int _getpid(){ return -1;}
    int _kill(int pid, int sig){ return -1; }
    int _write(){ return -1; }
}

enum actions {
    k00p, k01p, k02p, k03p, k04p, k05p, k06p, k07p, k08p, k09p, k10p, k11p,
    k12p, k13p, k14p, k15p, k16p, k17p, k18p, k19p, k20p, k21p, k22p, k23p,
    k24p, k25p, k26p, k27p, k28p, k29p, k30p, k31p, k32p, k33p, k34p, k35p,
    k36p, k37p, k38p, k39p, k40p, k41p, k42p, k43p, k44p, k45p, k46p, k47p,
    k00r, k01r, k02r, k03r, k04r, k05r, k06r, k07r, k08r, k09r, k10r, k11r,
    k12r, k13r, k14r, k15r, k16r, k17r, k18r, k19r, k20r, k21r, k22r, k23r,
    k24r, k25r, k26r, k27r, k28r, k29r, k30r, k31r, k32r, k33r, k34r, k35r,
    k36r, k37r, k38r, k39r, k40r, k41r, k42r, k43r, k44r, k45r, k46r, k47r
};
const char* actionStrings[] {
    "k00p", "k01p", "k02p", "k03p", "k04p", "k05p", "k06p", "k07p", "k08p", "k09p", "k10p", "k11p",
    "k12p", "k13p", "k14p", "k15p", "k16p", "k17p", "k18p", "k19p", "k20p", "k21p", "k22p", "k23p",
    "k24p", "k25p", "k26p", "k27p", "k28p", "k29p", "k30p", "k31p", "k32p", "k33p", "k34p", "k35p",
    "k36p", "k37p", "k38p", "k39p", "k40p", "k41p", "k42p", "k43p", "k44p", "k45p", "k46p", "k47p",
    "k00r", "k01r", "k02r", "k03r", "k04r", "k05r", "k06r", "k07r", "k08r", "k09r", "k10r", "k11r",
    "k12r", "k13r", "k14r", "k15r", "k16r", "k17r", "k18r", "k19r", "k20r", "k21r", "k22r", "k23r",
    "k24r", "k25r", "k26r", "k27r", "k28r", "k29r", "k30r", "k31r", "k32r", "k33r", "k34r", "k35r",
    "k36r", "k37r", "k38r", "k39r", "k40r", "k41r", "k42r", "k43r", "k44r", "k45r", "k46r", "k47r"
};

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
        KEY_LEFT_SHIFT, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
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
        -1, -1, -1, -1, -1, -1, -1, -1, KEY_BACKSLASH, -1, -1, -1
};
int numbers[] {
        KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F11, KEY_F12, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10,
        -1, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, -1,
        -1, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_UP, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_PAGE_DOWN, KEY_PAGE_UP, KEY_HOME, KEY_END, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};
int utils[] {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, KEY_MEDIA_VOLUME_DEC, KEY_MEDIA_VOLUME_INC, KEY_MEDIA_MUTE, KEY_MEDIA_NEXT_TRACK, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
//       0   1   2   3   4   5 | 6   7   8   9  10  11
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
    if (action >= 0 and action < numKeys) {
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
bool layer(int action)
{
    bool consumed = false;
    enum {start, numberLayer, utilLayer};
    static int state = start;
    switch (state) {
        case start:
            if (action == k43p)
            {
                keymapLayers.push_back(numbers);
                // todo - release all keys of the layer getting replaced
                state = numberLayer;
                consumed = true;
            } else if (action == k40p) {
                keymapLayers.push_back(utils);
                state = utilLayer;
                consumed = true;
            }
            break;
        case numberLayer:
            if (action == k43r)
            {
                if (keymapLayers.back() == numbers)
                {
                    keymapLayers.pop_back();
                    state = start;
                } else Serial.println("error: 1488939791"); // todo - a more robust layering scheme
                consumed = true;
            }
            break;
        case utilLayer:
            if (action == k40r) {
                if (keymapLayers.back() == utils)
                {
                    keymapLayers.pop_back();
                    state = start;
                } else Serial.println("error: 1488939792");
                consumed = true;
            }
            break;
    }
    return consumed;
}
bool shiftEquals(int action)
{
    bool consumed = false;
    enum {start, pressed, shift};
    static int state = start;
    switch (state)
    {
        case start:
            if (action == k35p)
            {
                consumed = true;
                state = pressed;
            }
            break;
        case pressed:
            if (action == k35r)
            {
                Keyboard.press(KEY_EQUAL);
                Keyboard.release(KEY_EQUAL);
                consumed = true;
                state = start;
            } else if (isPress(action)) {
                Keyboard.press(KEY_RIGHT_SHIFT);
                state = shift;
            }
            break;
        case shift:
            if (action == k35r)
            {
                Keyboard.release(KEY_RIGHT_SHIFT);
                consumed = true;
                state = start;
            }
            break;
    }
    return consumed;
}
bool thumbs(int action)
{
    bool consumed = false;
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
                consumed = true;
                state = one_thumb;
            } else if (action == k42p) {
                k42pressed = true;
                consumed = true;
                state = one_thumb;
            }
            break;
        case one_thumb:
            if (action == k41r and k41pressed)
            {
                k41pressed = false;
                Keyboard.press(KEY_BACKSPACE);
                Keyboard.release(KEY_BACKSPACE);
                consumed = true;
                state = start;
            } else if (action == k42r and k42pressed) {
                k42pressed = false;
                Keyboard.press(KEY_SPACE);
                Keyboard.release(KEY_SPACE);
                consumed = true;
                state = start;
            } else if (action == k41p and k42pressed) {
                k41pressed = true;
                consumed = true;
                state = both_thumb;
            } else if (action == k42p and k41pressed) {
                k42pressed = true;
                consumed = true;
                state = both_thumb;
            } else if (isPress(action) and k41pressed) {
                Keyboard.press(MODIFIERKEY_CTRL);
                state = one_mod;
            } else if(isPress(action) and k42pressed) {
                Keyboard.press(MODIFIERKEY_ALT);
                state = one_mod;
            }
            break;
        case both_thumb:
            if (not k41pressed or not k42pressed) Serial.println("something wrong 1488853974");
            if (action == k41r) {
                k41pressed = false;
                Keyboard.press(KEY_DELETE);
                Keyboard.release(KEY_DELETE);
                consumed = true;
                state = one_thumb_prime;
            } else if (action == k42r) {
                k42pressed = false;
                Keyboard.press(KEY_ENTER);
                Keyboard.release(KEY_ENTER);
                consumed = true;
                state = one_thumb_prime;
            } else {
                Keyboard.press(MODIFIERKEY_CTRL);
                Keyboard.press(MODIFIERKEY_ALT);
                state = both_mod;
            }
            break;
        case both_mod:
            okp = otherKeysPressed();
            if (not okp and action == k41r)
            {
                k41pressed = false;
                Keyboard.release(MODIFIERKEY_CTRL);
                consumed = true;
                state = one_thumb_prime;
            } else if (not okp and action == k42r) {
                k42pressed = false;
                Keyboard.release(MODIFIERKEY_ALT);
                consumed = true;
                state = one_thumb_prime;
            } else if (okp and action == k41r)
            {
                k41pressed = false;
                Keyboard.release(MODIFIERKEY_CTRL);
                consumed = true;
                state = one_mod;
            } else if (okp and action == k42r) {
                k42pressed = false;
                Keyboard.release(MODIFIERKEY_ALT);
                consumed = true;
                state = one_mod;
            }
            break;
        case one_mod:
            if (not (not k41pressed and k42pressed or k41pressed and not k42pressed)) Serial.println("problem 1488855253");
            if (action == k41p and !k41pressed) {
                k41pressed = true;
                Keyboard.press(MODIFIERKEY_CTRL);
                consumed = true;
                state = both_mod;
            } else if (action == k42p and !k42pressed) {
                k42pressed = true;
                Keyboard.press(MODIFIERKEY_ALT);
                consumed = true;
                state = both_mod;
            } else if (action == k41r and k41pressed) {
                k41pressed = false;
                Keyboard.release(MODIFIERKEY_CTRL);
                consumed = true;
                state = start;
            } else if (action == k42r and k42pressed) {
                k42pressed = false;
                Keyboard.release(MODIFIERKEY_ALT);
                consumed = true;
                state = start;
            }
            break;
        case one_thumb_prime:
            if (not (not k41pressed and k42pressed or k41pressed and not k42pressed)) Serial.println("problem 1488856884");
            if (action == k41p and not k41pressed)
            {
                k41pressed = true;
                consumed = true;
                state = both_thumb;
            } else if (action == k42p and not k42pressed) {
                k42pressed = true;
                consumed = true;
                state = both_thumb;
            } else if (action == k41r and k41pressed) {
                k41pressed = false;
                consumed = true;
                state = start;
            } else if (action == k42r and k42pressed) {
                k42pressed = false;
                consumed = true;
                state = start;
            } else if (k41pressed) {
                Keyboard.press(MODIFIERKEY_CTRL);
                state = one_mod;
            } else if (k42pressed) {
                Keyboard.press(MODIFIERKEY_ALT);
                state = one_mod;
            }
            break;
    }
    return consumed;
}
bool(*listeners[])(int action) = {shiftEquals, thumbs, layer};
void push(int action)
{
    bool consumed = false;
    for(auto f:listeners)
    {
        if (f(action))
        {
            consumed = true;
        }
    }
    if (not consumed)
    {
        send(action);
    }
    Serial.println(actionStrings[action]);
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
                        push(key);
                    }
                } else {
                    if(millis() - times[key] > 20) {
                        times[key] = millis();
                        states[key] = 0;
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

// current problem. there's a way for the ctrl key to get stuck, probably the same for the alt key as well
// the ctrl alt mod keys happen at the lowest level. they work off of the raw inputs before they get mapped at all which means that they can't get mapped to anything later
// need better debuging
// todo - i broke it so that on alt tab, the first tab doesn't go through
// todo - idea - sticky keys - press alt, press other key, release alt, press space, sends alt space

//https://github.com/PaulStoffregen/cores/blob/master/teensy/keylayouts.h
