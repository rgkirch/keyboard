#ifndef KEYBOARD_REGEX_H
#define KEYBOARD_REGEX_H

#include "Arduino.h"
#include <regex>
#include <iostream>
#include <vector>
#include <cassert>

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
#define k36p 0x5c,0x24
#define k37p 0x25
#define k38p 0x26
#define k39p 0x27
#define k40p 0x5c,0x28
#define k41p 0x5c,0x29
#define k42p 0x5c,0x2a
#define k43p 0x5c,0x2b
#define k44p 0x2c
#define k45p 0x2d
#define k46p 0x5c,0x2e
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
#define k15r 0x5c,0x3f
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
#define k43r 0x5c,0x5b
#define k44r 0x5c,0x5c
#define k45r 0x5c,0x5d
#define k46r 0x5c,0x5e
#define k47r 0x5f

//enum {KEY_ENTER, KEY_CTRL, KEY_ALT, KEY_DELETE, KEY_BACKSPACE, KEY_SPACE};
//std::string keyStrings[] {"KEY_ENTER", "KEY_CTRL", "KEY_ALT", "KEY_DELETE", "KEY_BACKSPACE", "KEY_SPACE"};

void press(int key);
void release(int key);
void send(int key);
void push(int key);

#endif //KEYBOARD_REGEX_H
