#include <regex>
#include <iostream>
#include <vector>
#include <cassert>

#define 0p 0x00
#define 1p 0x01
#define 2p 0x02
#define 3p 0x03
#define 4p 0x04
#define 5p 0x05
#define 6p 0x06
#define 7p 0x07
#define 8p 0x08
#define 9p 0x09
#define 10p 0x0a
#define 11p 0x0b
#define 12p 0x0c
#define 13p 0x0d
#define 14p 0x0e
#define 15p 0x0f
#define 16p 0x10
#define 17p 0x11
#define 18p 0x12
#define 19p 0x13
#define 20p 0x14
#define 21p 0x15
#define 22p 0x16
#define 23p 0x17
#define 24p 0x18
#define 25p 0x19
#define 26p 0x1a
#define 27p 0x1b
#define 28p 0x1c
#define 29p 0x1d
#define 30p 0x1e
#define 31p 0x1f
#define 32p 0x20
#define 33p 0x21
#define 34p 0x22
#define 35p 0x23
#define 36p 0x24
#define 37p 0x25
#define 38p 0x26
#define 39p 0x27
#define 40p 0x28
#define 41p 0x29
#define 42p 0x2a
#define 43p 0x2b
#define 44p 0x2c
#define 45p 0x2d
#define 46p 0x2e
#define 47p 0x2f
#define 0r 0x30
#define 1r 0x31
#define 2r 0x32
#define 3r 0x33
#define 4r 0x34
#define 5r 0x35
#define 6r 0x36
#define 7r 0x37
#define 8r 0x38
#define 9r 0x39
#define 10r 0x3a
#define 11r 0x3b
#define 12r 0x3c
#define 13r 0x3d
#define 14r 0x3e
#define 15r 0x3f
#define 16r 0x40
#define 17r 0x41
#define 18r 0x42
#define 19r 0x43
#define 20r 0x44
#define 21r 0x45
#define 22r 0x46
#define 23r 0x47
#define 24r 0x48
#define 25r 0x49
#define 26r 0x4a
#define 27r 0x4b
#define 28r 0x4c
#define 29r 0x4d
#define 30r 0x4e
#define 31r 0x4f
#define 32r 0x50
#define 33r 0x51
#define 34r 0x52
#define 35r 0x53
#define 36r 0x54
#define 37r 0x55
#define 38r 0x56
#define 39r 0x57
#define 40r 0x58
#define 41r 0x59
#define 42r 0x5a
#define 43r 0x5b
#define 44r 0x5c
#define 45r 0x5d
#define 46r 0x5e
#define 47r 0x5f

#define KEYp [0x00-0x2f]
#define KEYr [0x2e-0x5f]

enum {KEY_ENTER, KEY_CTRL, KEY_ALT, KEY_DELETE, KEY_BACKSPACE, KEY_SPACE};
std::string keyStrings[] {"KEY_ENTER", "KEY_CTRL", "KEY_ALT", "KEY_DELETE", "KEY_BACKSPACE", "KEY_SPACE"};

void press(int key) {
    std::cout << "press " << keyStrings[key] << std::endl;
}
void release(int key) {
    std::cout << "release " << keyStrings[key] << std::endl;
}
void send(int key) {
    press(key);
    release(key);
}

template <typename T>
class Stack {
public:
    void push_back(T key) { stack.push_back(key); }
    void pop(int number) { for(int i=0; i < number; i++) stack.pop_back(); }
    bool empty() { return stack.empty(); }
    T& back() { return stack.back(); }
private:
    std::vector<T> stack;
};

Stack<int> stack;

int main() {
    std::string inputString;
    while(std::getline(std::cin, inputString)) {
        // space and backspace
        try {
            if (std::regex_match(inputString, std::regex(R"(42p 42r)"))) {
                send(KEY_SPACE);// stack.pop(2); assert(stack.empty());
            }
            if (std::regex_match(inputString, std::regex(R"(41p 41r)"))) {
                send(KEY_BACKSPACE);// stack.pop(2); assert(stack.empty());
            }
            // enter and delete
            if (std::regex_match(inputString, std::regex(R"(41p 42p 42r)"))) {
                send(KEY_ENTER);//
            }
            if (std::regex_match(inputString, std::regex(R"(41p (42p 42r){2})"))) {
                send(KEY_ENTER);// stack.pop(2);
            }
            if (std::regex_match(inputString, std::regex(R"(41p 42p 42r 41r)"))) {
                //stack.pop(4); assert(stack.empty());
            }
            if (std::regex_match(inputString, std::regex(R"(42p 41p 41r)"))) {
                send(KEY_DELETE);//
            }
            if (std::regex_match(inputString, std::regex(R"(42p (41p 41r){2})"))) {
                send(KEY_DELETE);// stack.pop(2);
            }
            if (std::regex_match(inputString, std::regex(R"(42p 41p 41r 42r)"))) {
                //stack.pop(4); assert(stack.empty());
            }
            // ctrl alt other_key
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) KEYp)"))) {
                press(KEY_CTRL); press(KEY_ALT);// press(stack.back());
            }
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) (KEYp) (?:41r|42r)* \1r)"))) {
                //release(stack.back());
            }
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) (KEYp) (?:41r|42r)* \1r (?:41r|42r)* KEYp)"))) {
                //press(stack.back());// int t = stack.back(); stack.pop(3); stack.push_back(t);
            }
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) (?:KEYp (?:41r|42r)*)+ KEYp)"))) {
                //press(stack.back());
            }
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) (?:?=(?:KEYp (?:41r|42r)*)+ KEYp) (?:KEYp* (KEYp) KEYp*) \1r)"))) {
                //release(stack.back());// stack.remove(p(stack.back()));
            }
            // ctrl alt done
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) KEYp+ 41r)"))) {
                release(KEY_CTRL);
            }
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) KEYp+ 42r)"))) {
                release(KEY_ALT);
            }
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) KEYp+ 41r 42r)"))) {
                release(KEY_CTRL); release(KEY_ALT);// stack.pop(2); stack.pop_front(2);
            }
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) KEYp+ 42r 41r)"))) {
                release(KEY_ALT); release(KEY_CTRL);// stack.pop(2); stack.pop_front(2);
            }
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) KEYp+ 42r 42p)"))) {
                press(KEY_ALT);// stack.pop(2);
            }
            if (std::regex_match(inputString, std::regex(R"((?:41p 42p | 42p 41p) KEYp+ 41r 41p)"))) {
                press(KEY_CTRL);// stack.pop(2);
            }
        } catch (std::regex_error e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
