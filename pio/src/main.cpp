#include "Arduino.h"
#include "keyboard.hpp"
#include <algorithm>
#include <cstdarg>
#include <functional>
#include <map>
#include <vector>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

void reset() {
  Keyboard.releaseAll();
  // _reboot_Teensyduino_();
}
void setup() {
  configuration =
      Configuration::Builder()
          .i(6)
          .i(7)
          .i(8)
          .i(9)
          .o(10)
          .o(11)
          .o(12)
          .o(15)
          .o(16)
          .o(17)
          .o(18)
          .o(19)
          .o(20)
          .o(21)
          .o(22)
          .o(23)
          .f([](int i, int o, int inputsLength, int outputsLength) -> int {
            return outputsLength * i + o;
          })
          .build();
  Serial.begin(9600);
  Serial.println("hello from keyboard");
  Keyboard.begin();
  Mouse.begin();
  keymapLayers.push_back(modifiers);
  keymapLayers.push_back(dvorak);
  for (unsigned int i = 0; i < configuration->inputs.size(); i++) {
    pinMode(configuration->inputs[i], INPUT_PULLDOWN);
  }
  for (unsigned int i = 0; i < configuration->outputs.size(); i++) {
    pinMode(configuration->outputs[i], OUTPUT);
    digitalWrite(configuration->outputs[i], LOW);
  }
}
void alive() {
  static uint32_t lastPrint = millis();
  if (millis() - lastPrint > 1000) {
    Serial.println("alive");
    lastPrint = millis();
  }
}
void loop() {
  alive();
  for (unsigned int o = 0; o < configuration->outputs.size(); o++) {
    digitalWrite(configuration->outputs[o], HIGH);
    for (unsigned int i = 0; i < configuration->inputs.size(); i++) {
      int state = digitalRead(configuration->inputs[i]);
      int key = configuration->outputs.size() * i + o;
      if (state != states[key] &&
          millis() - times[key] > 20) // if there is a change and debounce
      {
        if (state) {
          times[key] = millis();
          states[key] = 1;
          push(KeyEvent(layout[key], Action::PRESS));
        } else {
          times[key] = millis();
          states[key] = 0;
          push(KeyEvent(layout[key], Action::RELEASE));
        }
      }
    }
    digitalWrite(configuration->outputs[o], LOW);
  }
  //    delay(1000);
}

// current problem. there's a way for the ctrl key to get stuck, probably the
// same for the alt key as well

// the ctrl alt mod keys happen at the lowest level. they work off of the raw
// inputs before they get mapped at all which means that they can't get mapped
// to anything later

// need better debuging

// todo - i broke it so that on alt tab, the first tab doesn't go through

// todo - idea - sticky keys - press alt, press other key, release alt, press
// space, sends alt space

// todo - alt+page down+release alt - doesn't stop painging down

// todo - make macro recording time sensitive - example, if i hold a key, it
// records one event for it but windows might have repeated the key

// todo - put limit on macro record size

// https://github.com/PaulStoffregen/cores/blob/master/teensy/keylayouts.h
// https://www.pjrc.com/teensy/usb_keyboard.html