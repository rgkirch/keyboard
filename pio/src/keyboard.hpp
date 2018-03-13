#include "umm.hpp"
#include <algorithm>
#include <cstdarg>
#include <functional>
#include <map>
#include <vector>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

class Configuration {
public:
  class Builder;
  int layout[48] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
                    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
                    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47};
  const std::vector<uint8_t> outputs;
  const std::vector<uint8_t> inputs;
  int fun(int i, int o) { return f(i, o, inputs.size(), outputs.size()); };

private:
  Configuration(std::vector<uint8_t> outputs, std::vector<uint8_t> inputs,
                std::function<int(int, int, int, int)> fun)
      : outputs(outputs), inputs(inputs), f(fun){};
  std::function<int(int, int, int, int)> f; // todo - make const
};
class Configuration::Builder {
public:
  Configuration *build() {
    return new Configuration(outputs, inputs, function);
  };
  Builder &o(uint8_t n) {
    outputs.push_back(n);
    return *this;
  };
  Builder &i(uint8_t n) {
    inputs.push_back(n);
    return *this;
  };
  Builder &f(std::function<int(int, int, int, int)> fun) {
    function = fun;
    return *this;
  };

private:
  std::function<int(int, int, int, int)> function;
  std::vector<uint8_t> outputs;
  std::vector<uint8_t> inputs;
};
Configuration *configuration;

// clang-format off
enum class Key {
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11,
    k12, k13, k14, k15, k16, k17, k18, k19, k20, k21, k22, k23,
    k24, k25, k26, k27, k28, k29, k30, k31, k32, k33, k34, k35,
    k36, k37, k38, k39, k40, k41, k42, k43, k44, k45, k46, k47
};
Key layout[] = {
        Key::k00, Key::k01, Key::k02, Key::k03, Key::k04, Key::k05, Key::k06, Key::k07, Key::k08, Key::k09, Key::k10, Key::k11,
        Key::k12, Key::k13, Key::k14, Key::k15, Key::k16, Key::k17, Key::k18, Key::k19, Key::k20, Key::k21, Key::k22, Key::k23,
        Key::k24, Key::k25, Key::k26, Key::k27, Key::k28, Key::k29, Key::k30, Key::k31, Key::k32, Key::k33, Key::k34, Key::k35,
        Key::k36, Key::k37, Key::k38, Key::k39, Key::k40, Key::k41, Key::k42, Key::k43, Key::k44, Key::k45, Key::k46, Key::k47
};
// clang-format on

enum class Action { RELEASE, PRESS };
class KeyEvent {
public:
  KeyEvent(Key k, Action a) : key(k), action(a){};
  bool isPress() { return action == Action::PRESS; }
  bool isRelease() { return action == Action::RELEASE; }
  bool isKey(Key k) { return k == key; }
  bool isKeyPressed(Key k) { return isKey(k) and isPress(); }
  bool isKeyReleased(Key k) { return isKey(k) and isRelease(); }
  bool isOneOf(std::vector<Key> keys) {
    return std::find(keys.begin(), keys.end(), key) == keys.end();
  }
  Key getKey() { return key; }
  Action getAction() { return action; }

private:
  Key key;
  Action action;
};

bool shiftEquals(KeyEvent action);
bool thumbs(KeyEvent action);
bool layer(KeyEvent action);
bool mouse(KeyEvent action);
bool leader(KeyEvent action);

struct RecordActions {
public:
  void startRecording(int key) {
    // todo - isAlpha(key);
    actions[key].clear();
    rawKeys[key].clear();
    setCurrentMacroKey(key);
    setRecordingActions(true);
  }
  void stopRecording() { setRecordingActions(false); }
  void recordAction(std::function<void(void)> f) {
    if (isRecording()) {
      actions[currentMacroKey].push_back(f);
    }
  }
  void recordRawKey(KeyEvent key) {
    if (isRecording()) {
      rawKeys[currentMacroKey].push_back(key);
    }
  }
  void replayActions(int key) {
    for (auto &&f : actions[key]) {
      f();
    }
  }
  void replayRawKeys(int key) {
    // disallow playback of the currently recording macro to avoid infinite
    // playback loop todo - implement this
  }
  bool isRecording() { return recording; }
  //    friend bool leader(int action);
private:
  std::map<int, std::vector<std::function<void(void)>>> actions;
  std::map<int, std::vector<KeyEvent>> rawKeys;
  void setCurrentMacroKey(int key) { currentMacroKey = key; }
  void setRecordingActions(bool b) {
    recording = b;
  } // when set to true, the iterators must be valid
  int currentMacroKey;
  bool recording = false;
};
struct RecordActions recordActions;
int numKeys = 48;
std::vector<int *> keymapLayers;
bool (*listeners[])(KeyEvent action) = {shiftEquals, thumbs, layer, mouse,
                                        leader};
extern "C" {
int _getpid() { return -1; }
int _kill(int pid, int sig) { return -1; }
int _write() { return -1; }
}
struct ModifierKeysStates {
public:
  bool getLeftShiftPressed() { return leftShiftPressed; };
  bool getRightShiftPressed() { return rightShiftPressed; };
  bool getAnyShiftPressed() { return rightShiftPressed or leftShiftPressed; };
  friend void keyboardPress(int key);
  friend void keyboardRelease(int key);

private:
  void setLeftShift(bool b) { leftShiftPressed = b; };
  void setRightShift(bool b) { rightShiftPressed = b; };
  bool leftShiftPressed = false;
  bool rightShiftPressed = false;
};
struct ModifierKeysStates modifierKeysStates;
const char *actionStrings[]{
    "k00p", "k01p", "k02p", "k03p", "k04p", "k05p", "k06p", "k07p", "k08p",
    "k09p", "k10p", "k11p", "k12p", "k13p", "k14p", "k15p", "k16p", "k17p",
    "k18p", "k19p", "k20p", "k21p", "k22p", "k23p", "k24p", "k25p", "k26p",
    "k27p", "k28p", "k29p", "k30p", "k31p", "k32p", "k33p", "k34p", "k35p",
    "k36p", "k37p", "k38p", "k39p", "k40p", "k41p", "k42p", "k43p", "k44p",
    "k45p", "k46p", "k47p", "k00r", "k01r", "k02r", "k03r", "k04r", "k05r",
    "k06r", "k07r", "k08r", "k09r", "k10r", "k11r", "k12r", "k13r", "k14r",
    "k15r", "k16r", "k17r", "k18r", "k19r", "k20r", "k21r", "k22r", "k23r",
    "k24r", "k25r", "k26r", "k27r", "k28r", "k29r", "k30r", "k31r", "k32r",
    "k33r", "k34r", "k35r", "k36r", "k37r", "k38r", "k39r", "k40r", "k41r",
    "k42r", "k43r", "k44r", "k45r", "k46r", "k47r"};

char states[48] = {0};
long times[48] = {0};

// clang-format off
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
        -1, -1, -1, MODIFIERKEY_GUI, -1, -1, -1, -1, -1, -1, -1, -1,
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
int numbers[] { // todo - let it fall through to hit the equal key instead of catching that at a higher level
        KEY_F11, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F12,
        KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_BACKSLASH,
        -1, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_UP, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_PAGE_DOWN, KEY_PAGE_UP, KEY_END, KEY_HOME, KEY_EQUAL,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};
int utils[] {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, KEY_MEDIA_PREV_TRACK, KEY_MEDIA_NEXT_TRACK, KEY_MEDIA_VOLUME_DEC, KEY_MEDIA_VOLUME_INC, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
//       0   1   2   3   4   5 | 6   7   8   9  10  11
};
// clang-format on

int get(int layer, KeyEvent event) { // todo - move keymaplayers to a class with
                                     // private mutators
  if (layer < 0)
    return -1;
  //    if(keymapLayers[layer] == nullptr) return get(layer - 1,
  //    event.getKey());
  if (keymapLayers[layer][static_cast<int>(event.getKey())] != -1) {
    return keymapLayers[layer][static_cast<int>(event.getKey())];
  } else {
    return get(layer - 1, event);
  }
}
int get(KeyEvent event) { return get(keymapLayers.size() - 1, event); }

bool isLetter(int key) {
  return (key & ~0xF000) >= 4 and (key & ~0xF000) <= 29;
}
bool isNumber(int key) {
  return (key & ~0xF000) >= 30 and (key & ~0xF000) <= 39;
}
bool otherKeysPressed() {
  for (int i = 0; i < numKeys; ++i) {
    if (i != 41 and i != 42 and states[i] == 1)
      return true;
  }
  return false;
}
void keyboardPress(int key) {
  if (recordActions.isRecording()) {
    recordActions.recordAction(
        [=]() -> void { keyboardDotPress((uint16_t)key); });
  }
  switch (key) {
  case KEY_LEFT_SHIFT:
    modifierKeysStates.setLeftShift(true);
    break;
  case KEY_RIGHT_SHIFT:
    modifierKeysStates.setRightShift(true);
    break;
  }
  keyboardDotPress((uint16_t)key);
}
void keyboardRelease(int key) {
  if (recordActions.isRecording()) {
    recordActions.recordAction(
        [=]() -> void { keyboardDotRelease((uint16_t)key); });
  }
  switch (key) {
  case KEY_LEFT_SHIFT:
    modifierKeysStates.setLeftShift(false);
    break;
  case KEY_RIGHT_SHIFT:
    modifierKeysStates.setRightShift(false);
    break;
  }
  keyboardDotRelease((uint16_t)key);
}
void mouseMoveTo(int x, int y) {
  if (recordActions.isRecording()) {
    recordActions.recordAction(
        [=]() -> void { mouseDotMoveTo((uint16_t)x, (uint16_t)y); });
  }
  mouseDotMoveTo((uint16_t)x, (uint16_t)y);
}
void mouseMove(int x, int y) {
  int unit = 100;
  int xs = 1;
  int ys = 1;
  if (x < 0) {
    xs = -1;
    x *= -1;
  }
  if (y < 0) {
    ys = -1;
    y *= -1;
  }
  while (x > 0 or y > 0) {
    int xmove = min(unit, x);
    x = max(0, x - unit);
    int ymove = min(unit, y);
    y = max(0, y - unit);
    if (recordActions.isRecording())
      recordActions.recordAction([=]() -> void {
        mouseDotMove((uint8_t)(xmove * xs), (uint8_t)(ymove * ys));
      });
    mouseDotMove((uint8_t)(xmove * xs), (uint8_t)(ymove * ys));
  }
}
void send(KeyEvent event) {
  int key = get(event); // add the pressed key somewhere so that we aren't
                        // relying on finding the same on the next time that we
                        // look it up in the array
  if (event.isPress()) {
    keyboardPress(key);
  } else if (event.isRelease()) {
    keyboardRelease(key);
  }
}
bool leader(KeyEvent action) {
  enum { start, leading, recordToWhere, replayWhat };
  static int state = start;
  bool consumed = false;
  switch (state) {
  case start:
    if (action.isKeyPressed(Key::k38)) {
      state = leading;
      consumed = true;
    }
    break;
  case leading:
    if (action.isPress()) {
      int key = get(action);
      if (key == KEY_2 and modifierKeysStates.getAnyShiftPressed()) {
        state = replayWhat;
        consumed = true;
      } else if (key == KEY_Q) {
        if (recordActions.isRecording()) {
          recordActions.stopRecording();
          state = start;
          consumed = true;
        } else {
          state = recordToWhere;
          consumed = true;
        }
      } else {
        state = start;
      }
    }
    break;
  case replayWhat:
    if (action.isPress()) {
      int key = get(action);
      if (isLetter(key) /*and is lowercase*/) {
        recordActions.replayActions(key);
        consumed = true;
      } // todo - else it's capital replay raw
      state = start;
    }
    break;
  case recordToWhere:
    int resolvedAction = get(action);
    if (action.isPress()) {
      if (isLetter(resolvedAction)) {
        recordActions.startRecording(resolvedAction);
        state = start;
        consumed = true;
      } else {
        state = start;
      }
    }
    break;
  }
  return consumed;
}
bool mouse(KeyEvent action) {
  static bool centered = false;
  mouseDotScreenSize(3840, 2160);
  int xRes = 3840;
  int yRes = 2160;
  //    int xRes = 920;
  //    int yRes = 1080;
  //    int xRes = 100;
  //    int yRes = 100;
  static int xunit = 0;
  static int yunit = 0;
  bool consumed = false;
  enum { start, mouse };
  static int state = start;
  switch (state) {
  case start:
    if (action.isKeyPressed(Key::k40)) {
      xunit = xRes / 4;
      yunit = yRes / 4;
      state = mouse;
      consumed = true;
    }
    break;
  case mouse:
    if (not centered and action.isPress() and
        action.isOneOf({Key::k08, Key::k19, Key::k20, Key::k21})) {
      mouseMoveTo(xRes / 2, yRes / 2);
      centered = true;
    }
    if (action.isKeyPressed(Key::k08)) {
      mouseMove(0, -yunit);
      consumed = true;
      yunit /= 2;
    } else if (action.isKeyPressed(Key::k19)) {
      mouseMove(-xunit, 0);
      consumed = true;
      xunit /= 2;
    } else if (action.isKeyPressed(Key::k20)) {
      mouseMove(0, yunit);
      consumed = true;
      yunit /= 2;
    } else if (action.isKeyPressed(Key::k21)) {
      mouseMove(xunit, 0);
      consumed = true;
      xunit /= 2;
    } else if (action.isKeyPressed(Key::k31)) {
      mouseDotClick(1);
      consumed = true;
    } else if (action.isKeyPressed(Key::k32)) {
      mouseDotClick(4);
      consumed = true;
    } else if (action.isKeyPressed(Key::k33)) {
      mouseDotClick(2);
      consumed = true;
    } else if (action.isKeyReleased(Key::k40)) {
      state = start;
      centered = false;
    }
    break;
  }
  return consumed;
}
bool relativeMouse(KeyEvent action) {
  static int xunit = 0;
  static int yunit = 0;
  static bool divide = false;
  bool consumed = false;
  enum { start, mouse };
  static int state = start;
  switch (state) {
  case start:
    if (action.isKeyPressed(Key::k40)) {
      xunit = 1000;
      yunit = 1000;
      divide = false;
      state = mouse;
      consumed = true;
    }
    break;
  case mouse:
    if (action.isKeyPressed(Key::k07)) {
      divide = not divide;
      consumed = true;
    } else if (action.isKeyPressed(Key::k08)) {
      mouseMove(0, -yunit);
      consumed = true;
      if (divide)
        yunit /= 2;
    } else if (action.isKeyPressed(Key::k19)) {
      mouseMove(-xunit, 0);
      consumed = true;
      if (divide)
        xunit /= 2;
    } else if (action.isKeyPressed(Key::k20)) {
      mouseMove(0, yunit);
      consumed = true;
      if (divide)
        yunit /= 2;
    } else if (action.isKeyPressed(Key::k21)) {
      mouseMove(xunit, 0);
      consumed = true;
      if (divide)
        xunit /= 2;
    } else if (action.isKeyPressed(Key::k31)) {
      mouseDotClick(1);
      consumed = true;
    } else if (action.isKeyPressed(Key::k32)) {
      mouseDotClick(4);
      consumed = true;
    } else if (action.isKeyPressed(Key::k33)) {
      mouseDotClick(2);
      consumed = true;
    } else if (action.isKeyReleased(Key::k40)) {
      state = start;
    }
    break;
  }
  return consumed;
}
bool layer(KeyEvent action) {
  bool consumed = false;
  enum { start, numberLayer, utilLayer };
  static int state = start;
  switch (state) {
  case start:
    if (action.isKeyPressed(Key::k43)) {
      keymapLayers.push_back(numbers);
      // todo - release all keys of the layer getting replaced
      state = numberLayer;
      consumed = true;
    } else if (action.isKeyPressed(Key::k40)) {
      keymapLayers.push_back(utils);
      state = utilLayer;
      consumed = true;
    }
    break;
  case numberLayer:
    if (action.isKeyReleased(Key::k43)) {
      if (keymapLayers.back() == numbers) {
        keymapLayers.pop_back();
        state = start;
      } else
        Serial.println(
            "error: 1488939791"); // todo - a more robust layering scheme
      consumed = true;
    }
    break;
  case utilLayer:
    if (action.isKeyReleased(Key::k40)) {
      if (keymapLayers.back() == utils) {
        keymapLayers.pop_back();
        state = start;
      } else
        Serial.println("error: 1488939792");
      consumed = true;
    }
    break;
  }
  return consumed;
}
bool shiftEquals(KeyEvent action) {
  bool consumed = false;
  enum { start, pressed, shift };
  static int state = start;
  switch (state) {
  case start:
    if (action.isKeyPressed(Key::k35)) {
      consumed = true;
      state = pressed;
    }
    break;
  case pressed:
    if (action.isKeyReleased(Key::k35)) {
      keyboardPress(KEY_EQUAL);
      keyboardRelease(KEY_EQUAL);
      consumed = true;
      state = start;
    } else if (action.isPress()) {
      keyboardPress(KEY_RIGHT_SHIFT);
      state = shift;
    }
    break;
  case shift:
    if (action.isKeyReleased(Key::k35)) {
      keyboardRelease(KEY_RIGHT_SHIFT);
      consumed = true;
      state = start;
    }
    break;
  }
  return consumed;
}
bool thumbs(KeyEvent action) {
  bool consumed = false;
  bool okp;
  static bool k41pressed = false;
  static bool k42pressed = false;
  enum { start, one_thumb, one_thumb_prime, both_thumb, one_mod, both_mod };
  const char *enums[]{"start",      "one_thumb", "one_thumb_prime",
                      "both_thumb", "one_mod",   "both_mod"};
  static int state = start;
  switch (state) {
  case start:
    if (action.isKeyPressed(Key::k41)) {
      k41pressed = true;
      consumed = true;
      state = one_thumb;
    } else if (action.isKeyPressed(Key::k42)) {
      k42pressed = true;
      consumed = true;
      state = one_thumb;
    }
    break;
  case one_thumb:
    if (action.isKeyReleased(Key::k41) and k41pressed) {
      k41pressed = false;
      keyboardPress(KEY_BACKSPACE);
      keyboardRelease(KEY_BACKSPACE);
      consumed = true;
      state = start;
    } else if (action.isKeyReleased(Key::k42) and k42pressed) {
      k42pressed = false;
      keyboardPress(KEY_SPACE);
      keyboardRelease(KEY_SPACE);
      consumed = true;
      state = start;
    } else if (action.isKeyPressed(Key::k41) and k42pressed) {
      k41pressed = true;
      consumed = true;
      state = both_thumb;
    } else if (action.isKeyPressed(Key::k42) and k41pressed) {
      k42pressed = true;
      consumed = true;
      state = both_thumb;
    } else if (action.isPress() and k41pressed) {
      keyboardPress(MODIFIERKEY_CTRL);
      state = one_mod;
    } else if (action.isPress() and k42pressed) {
      keyboardPress(MODIFIERKEY_ALT);
      state = one_mod;
    }
    break;
  case both_thumb:
    if (not k41pressed or not k42pressed)
      Serial.println("something wrong 1488853974");
    if (action.isKeyReleased(Key::k41)) {
      k41pressed = false;
      keyboardPress(KEY_DELETE);
      keyboardRelease(KEY_DELETE);
      consumed = true;
      state = one_thumb_prime;
    } else if (action.isKeyReleased(Key::k42)) {
      k42pressed = false;
      keyboardPress(KEY_ENTER);
      keyboardRelease(KEY_ENTER);
      consumed = true;
      state = one_thumb_prime;
    } else {
      keyboardPress(MODIFIERKEY_CTRL);
      keyboardPress(MODIFIERKEY_ALT);
      state = both_mod;
    }
    break;
  case both_mod:
    okp = otherKeysPressed();
    if (not okp and action.isKeyReleased(Key::k41)) {
      k41pressed = false;
      keyboardRelease(MODIFIERKEY_CTRL);
      consumed = true;
      state = one_thumb_prime;
    } else if (not okp and action.isKeyReleased(Key::k42)) {
      k42pressed = false;
      keyboardRelease(MODIFIERKEY_ALT);
      consumed = true;
      state = one_thumb_prime;
    } else if (okp and action.isKeyReleased(Key::k41)) {
      k41pressed = false;
      keyboardRelease(MODIFIERKEY_CTRL);
      consumed = true;
      state = one_mod;
    } else if (okp and action.isKeyReleased(Key::k42)) {
      k42pressed = false;
      keyboardRelease(MODIFIERKEY_ALT);
      consumed = true;
      state = one_mod;
    }
    break;
  case one_mod:
    if (not((not k41pressed and k42pressed) or (k41pressed and not k42pressed)))
      Serial.println("problem 1488855253");
    if (action.isKeyPressed(Key::k41) and !k41pressed) {
      k41pressed = true;
      keyboardPress(MODIFIERKEY_CTRL);
      consumed = true;
      state = both_mod;
    } else if (action.isKeyPressed(Key::k42) and !k42pressed) {
      k42pressed = true;
      keyboardPress(MODIFIERKEY_ALT);
      consumed = true;
      state = both_mod;
    } else if (action.isKeyReleased(Key::k41) and k41pressed) {
      k41pressed = false;
      keyboardRelease(MODIFIERKEY_CTRL);
      consumed = true;
      state = start;
    } else if (action.isKeyReleased(Key::k42) and k42pressed) {
      k42pressed = false;
      keyboardRelease(MODIFIERKEY_ALT);
      consumed = true;
      state = start;
    }
    break;
  case one_thumb_prime:
    if (not((not k41pressed and k42pressed) or (k41pressed and not k42pressed)))
      Serial.println("problem 1488856884");
    if (action.isKeyPressed(Key::k41) and not k41pressed) {
      k41pressed = true;
      consumed = true;
      state = both_thumb;
    } else if (action.isKeyPressed(Key::k42) and not k42pressed) {
      k42pressed = true;
      consumed = true;
      state = both_thumb;
    } else if (action.isKeyReleased(Key::k41) and k41pressed) {
      k41pressed = false;
      keyboardRelease(MODIFIERKEY_CTRL);
      consumed = true;
      state = start;
    } else if (action.isKeyReleased(Key::k42) and k42pressed) {
      k42pressed = false;
      keyboardRelease(MODIFIERKEY_ALT);
      consumed = true;
      state = start;
    } else if (k41pressed) {
      keyboardPress(MODIFIERKEY_CTRL);
      state = one_mod;
    } else if (k42pressed) {
      keyboardPress(MODIFIERKEY_ALT);
      state = one_mod;
    }
    break;
  }
  return consumed;
}
void push(KeyEvent event) {
  if (recordActions.isRecording())
    recordActions.recordRawKey(event);
  bool consumed = false;
  for (auto &&f : listeners) {
    if (f(event)) {
      consumed = true;
    }
  }
  if (not consumed) {
    send(event);
  }
  //    Serial.println(actionStrings[action]);
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
  keyboardDotBegin();
  mouseDotBegin();
  keymapLayers.push_back(modifiers);
  keymapLayers.push_back(dvorak);
  for (unsigned int i = 0; i < configuration->inputs.size(); i++) {
    ummPinMode(configuration->inputs[i], INPUT_PULLDOWN);
  }
  for (unsigned int i = 0; i < configuration->outputs.size(); i++) {
    ummPinMode(configuration->outputs[i], OUTPUT);
    ummDigitalWrite(configuration->outputs[i], LOW);
  }
}