#include "Arduino.h"
//#undef isascii
//#undef toascii
//#define isascii(__c)	((unsigned)(__c)<=0177)
//#define toascii(__c)	((__c)&0177)

extern "C" {
    int _getpid(){ return -1;}
    int _kill(int pid, int sig){ return -1; }
    int _write(){ return -1; }
}

#include <regex>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

void setup()
{
    Serial.begin(9600);
}
void loop()
{
    {
        std::string testString{'Z'};

        Serial.print("testString ");
        for (char c:testString)
            Serial.print(c);
        Serial.println();
        if (std::regex_match(testString, std::regex {'Z'}))
            Serial.println("matched");
        else Serial.println("didn't match");
    }
    {
        std::string testString{'Z', 'Z'};

        Serial.print("testString ");
        for (char c:testString)
            Serial.print(c);
        Serial.println();
        if (std::regex_match(testString, std::regex {'Z', '*'}))
            Serial.println("matched");
        else Serial.println("didn't match");
    }
    {
        std::string testString{'Z', 'Z'};

        Serial.print("testString ");
        for (char c:testString)
            Serial.print(c);
        Serial.println();
        if (std::regex_match(testString, std::regex {'Z', '{', '2', '}'}))
            Serial.println("matched");
        else Serial.println("didn't match");
    }

    delay(3000);
}
