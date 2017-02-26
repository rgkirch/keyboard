#include "Arduino.h"
#include "regex.h"

//#undef isascii
//#undef toascii
//#define isascii(__c)	((unsigned)(__c)<=0177)
//#define toascii(__c)	((__c)&0177)
#include <ctype.h>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <bitset>
#include <functional>

extern "C" {
    int _getpid(){ return -1;}
    int _kill(int pid, int sig){ return -1; }
    int _write(){ return -1; }
}

typedef int pin;
typedef int key;
typedef int time;
pin inputs[] {6,  7,  8,  9};
pin outputs[] {10, 11, 12, 15, 16, 17, 18, 19, 20, 21, 22, 23};
key states[48] = {0};
time times[48] = {0};
const int inputsLength = sizeof(inputs) / sizeof(pin);
const int outputsLength = sizeof(outputs) / sizeof(pin);

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

//https://github.com/PaulStoffregen/cores/blob/master/teensy/keylayouts.h

// you don't press and release the alt key much, you could use press and release to be a space but when it's used in a combo, it works like the al
