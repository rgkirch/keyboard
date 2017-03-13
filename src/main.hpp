#include "Arduino.h"
#include <vector>
#include <functional>
#include <map>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
bool shiftEquals(int action);
bool thumbs(int action);
bool layer(int action);
bool mouse(int action);
bool leader(int action);
int get(int layer, int key);
int get(int key);
bool isPress(int action);
bool isRelease(int action);
bool isLetter(int key);
bool isNumber(int key);
bool otherKeysPressed();
void KeyboardPress(int action);
void KeyboardRelease(int action);
void MouseMoveTo(int x, int y);
void send(int action);
void MouseMove(int x, int y);
bool leader(int action);
bool mouse(int action);
bool layer(int action);
bool shiftEquals(int action);
bool thumbs(int action);
void reset();
void push(int action);
