#include <regex>
#include <iostream>
#include <vector>
#include <cassert>

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
char keys[] = {
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b,
    0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43,
    0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,

    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b,
    0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73,
    0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f
};
char ascii[] = {
    ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+',
    ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C',
    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',

    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[',
    '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
    't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', 0x7F};

int main() {
    for(int i = 0; i < 96; i++)
        std::cout << keys[i];

    std::string rawInputString;
    //while(std::getline(std::cin, rawInputString))
    if(false)
    {
        std::string inputString;
        
        // space and backspace
        try {
            if (std::regex_match(inputString, std::regex("Jz"))) {
                send(KEY_SPACE);// stack.pop(2); assert(stack.empty());
            }
            if (std::regex_match(inputString, std::regex("Iy"))) {
                send(KEY_BACKSPACE);// stack.pop(2); assert(stack.empty());
            }
            // enter and delete
            if (std::regex_match(inputString, std::regex("IJz"))) {
                send(KEY_ENTER);//
            }
            if (std::regex_match(inputString, std::regex("I(Jz){2}"))) {
                send(KEY_ENTER);// stack.pop(2);
            }
            if (std::regex_match(inputString, std::regex("IJzy"))) {
                //stack.pop(4); assert(stack.empty());
            }
            if (std::regex_match(inputString, std::regex("JIy"))) {
                send(KEY_DELETE);//
            }
            if (std::regex_match(inputString, std::regex("J(Iy){2}"))) {
                send(KEY_DELETE);// stack.pop(2);
            }
            if (std::regex_match(inputString, std::regex("JIyz"))) {
                //stack.pop(4); assert(stack.empty());
            }
            // ctrl alt other_key
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)KEYp"))) {
                press(KEY_CTRL); press(KEY_ALT);// press(stack.back());
            }
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)(KEYp)(?:y|z)* \1r"))) {
                //release(stack.back());
            }
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)(KEYp)(?:y|z)* \1r (?:y|z)* KEYp"))) {
                //press(stack.back());// int t = stack.back(); stack.pop(3); stack.push_back(t);
            }
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)(?:KEYp (?:y|z)*)+ KEYp"))) {
                //press(stack.back());
            }
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)(?:?=(?:KEYp(?:y|z)*)+ KEYp)(?:KEYp*(KEYp)KEYp*)\1r"))) {
                //release(stack.back());// stack.remove(p(stack.back()));
            }
            // ctrl alt done
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)KEYp+y"))) {
                release(KEY_CTRL);
            }
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)KEYp+z"))) {
                release(KEY_ALT);
            }
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)KEYp+yz"))) {
                release(KEY_CTRL); release(KEY_ALT);// stack.pop(2); stack.pop_front(2);
            }
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)KEYp+zy"))) {
                release(KEY_ALT); release(KEY_CTRL);// stack.pop(2); stack.pop_front(2);
            }
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)KEYp+zJ"))) {
                press(KEY_ALT);// stack.pop(2);
            }
            if (std::regex_match(inputString, std::regex("(?:IJ|JI)KEYp+yI"))) {
                press(KEY_CTRL);// stack.pop(2);
            }
        } catch (std::regex_error e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
