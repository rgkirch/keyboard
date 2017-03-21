#include "Arduino.h"
#include "keyboard.hpp"
void setup()
{
    Serial.begin(9600);
    Serial.println("hello from keyboard");
    Keyboard.begin();
    Mouse.begin();
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
void alive()
{
    static uint32_t lastPrint = millis();
    if (millis() - lastPrint > 1000) {
        Serial.println("alive");
        lastPrint = millis();
    }
}
void loop()
{
    alive();
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
// todo - alt+page down+release alt - doesn't stop painging down
// todo - make macro recording time sensitive - example, if i hold a key, it records one event for it but windows might have repeated the key
// todo - put limit on macro record size

//https://github.com/PaulStoffregen/cores/blob/master/teensy/keylayouts.h
//https://www.pjrc.com/teensy/usb_keyboard.html
