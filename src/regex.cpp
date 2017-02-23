#include <regex>
#include <iostream>
#include <vector>
#include <cassert>

enum {KEY_ENTER, KEY_CTRL, KEY_ALT, KEY_DELETE, KEY_BACKSPACE, KEY_SPACE};
std::string keyStrings[] {"KEY_ENTER", "KEY_CTRL", "KEY_ALT", "KEY_DELETE", "KEY_BACKSPACE", "KEY_SPACE"};

void press(int key) {
    std::cout << "press" << keyStrings[key] << std::endl;
}
void release(int key) {
    std::cout << "release" << keyStrings[key] << std::endl;
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
    while(std:: cin >> inputString) {
        // space and backspace
        if (std::regex_match(inputString, std::regex("42p 42r"))) {
            send(KEY_SPACE); stack.pop(2); assert(stack.empty());
        }
        if (std::regex_match(inputString, std::regex("41p 41r"))) {
            send(KEY_BACKSPACE); stack.pop(2); assert(stack.empty());
        }
        // enter and delete
        if (std::regex_match(inputString, std::regex("41p 42p 42r"))) {
            send(KEY_ENTER);
        }
        if (std::regex_match(inputString, std::regex("41p (42p 42r){2}"))) {
            send(KEY_ENTER); stack.pop(2);
        }
        if (std::regex_match(inputString, std::regex("41p 42p 42r 41r"))) {
            stack.pop(4); assert(stack.empty());
        }
        if (std::regex_match(inputString, std::regex("42p 41p 41r"))) {
            send(KEY_DELETE);
        }
        if (std::regex_match(inputString, std::regex("42p (41p 41r){2}"))) {
            send(KEY_DELETE); stack.pop(2);
        }
        if (std::regex_match(inputString, std::regex("42p 41p 41r 42r"))) {
            stack.pop(4); assert(stack.empty());
        }
        // ctrl alt other_key
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) KEYp"))) {
            press(KEY_CTRL); press(KEY_ALT); press(stack.back());
        }
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) (KEYp) (?:41r|42r)* \1r"))) {
            release(stack.back());
        }
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) (KEYp) (?:41r|42r)* \1r (?:41r|42r)* KEYp"))) {
            press(stack.back()); int t = stack.back(); stack.pop(3); stack.push_back(t);
        }
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) (?:KEYp (?:41r|42r)*)+ KEYp"))) {
            press(stack.back());
        }
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) (?:?=(?:KEYp (?:41r|42r)*)+ KEYp) (?:KEYp* (KEYp) KEYp*) \1r"))) {
            release(stack.back()); stack.remove(p(stack.back()));
        }
        // ctrl alt done
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) KEYp+ 41r"))) {
            release(KEY_CTRL);
        }
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) KEYp+ 42r"))) {
            release(KEY_ALT);
        }
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) KEYp+ 41r 42r"))) {
            release(KEY_CTRL); release(KEY_ALT); stack.pop(2); stack.pop_front(2);
        }
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) KEYp+ 42r 41r"))) {
            release(KEY_ALT); release(KEY_CTRL); stack.pop(2); stack.pop_front(2);
        }
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) KEYp+ 42r 42p"))) {
            press(KEY_ALT); stack.pop(2);
        }
        if (std::regex_match(inputString, std::regex("(?:41p 42p | 42p 41p) KEYp+ 41r 41p"))) {
            press(KEY_CTRL); stack.pop(2);
        }
    }
}
