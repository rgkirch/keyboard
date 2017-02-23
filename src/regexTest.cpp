#include <regex>
#include <iostream>
#include <vector>
#include <cassert>

#define byte 0x41

#define range [0x00-0x2f]

int main() {
    std::string hello("hello");
    const char c = byte;
    //printf("the byte as a char %c\n", byte);
    //printf("the char as a char %c\n", c);
    const char* ptr = &c;
    try {
        char str[] = {'o',byte};
        if (std::regex_match("oA", std::regex { str } )) {
            std::cout << "we got a match" << std::endl;
        }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
