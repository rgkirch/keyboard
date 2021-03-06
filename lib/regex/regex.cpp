#include "regex.h"

void push(std::string, int key)
{
    if(key < 0)
    {
        Serial.println("pushed a negative char onto the buffer");
    }
    buffer.push_back((char)key);
}
void pop(std::string,int number)
{
    for(int i=0; i < number; i++)
    { Serial.println("pop"); data.pop_back();
}
}
bool empty() { return data.empty(); }
const char& back() { return data.back(); }
std::string buffer;

void press(int key) {
    Serial.print("keyboard press ");
    Serial.println(key);
    Keyboard.press(key);
}
void release(int key) {
    Serial.print("keyboard release ");
    Serial.println(key);
    Keyboard.release(key);
}
void send(int key) {
    press(key);
    release(key);
}

void Serialprintln(std::string s)
{
    for(char c:s)
    {
        Serial.print(c);
    }
    Serial.println();
}

void push(int key) {
    stack.push(key);
    for(char c:stack.getString()) Serial.print(c);
    Serial.println();
    // space and backspace
    if () {
        send(KEY_SPACE); stack.pop(2);// assert(stack.empty());
    } else if (std::regex_match(stack.getString(), std::regex {k41p,k41r} )) {
        send(KEY_BACKSPACE); stack.pop(2);// assert(stack.empty());
    } else if (std::regex_match(stack.getString(), std::regex {k41p,k42p,k42r} )) { // enter and delete
        send(KEY_ENTER);
    } else if (std::regex_match(stack.getString(), std::regex {k41p,'(',k42p,k42r,')','{','2','}'} )) {
        send(KEY_ENTER); stack.pop(2);
    } else if (std::regex_match(stack.getString(), std::regex {k41p,k42p,k42r,k41r} )) {
        stack.pop(4);// assert(stack.empty());
    } else if (std::regex_match(stack.getString(), std::regex {k42p,k41p,k41r} )) {
        send(KEY_DELETE);
    } else if (std::regex_match(stack.getString(), std::regex {k42p,'(',k41p,k41r,')','{','2','}'} )) {
        send(KEY_DELETE); stack.pop(2);
    } else if (std::regex_match(stack.getString(), std::regex {k42p,k41p,k41r,k42r} )) {
//        std::clog << "stack.pop(4); assert(stack.empty());" << std::endl;
        stack.pop(4);// assert(stack.empty());
    } else {
        Serial.println("reched end of cascading if else");
    }


//    // ctrl alt other_key
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|',k42p,k41p,')',KEYp} )) {
//        press(KEY_CTRL); press(KEY_ALT);// press(stack.back());
//    }
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', '(',KEYp,')', ('?',':',k41r'|',k42r,')',* \1r} )) {
//        //release(stack.back());
//    }
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', '(',KEYp,')', ('?',':',k41r'|',k42r,')',* \1r ('?',':',k41r'|',k42r,')',* KEYp} )) {
//        //press(stack.back());// int t = stack.back(); stack.pop(3); stack.push_back(t);
//    }
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', ('?',':',KEYp ('?',':',k41r'|',k42r,')',*,')','+', KEYp} )) {
//        //press(stack.back());
//    }
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', ('?',':','?',=('?',':',KEYp ('?',':',k41r'|',k42r,')',*,')','+', KEYp,')', ('?',':',KEYp* ,'(',KEYp,')', KEYp*,')', \1r} )) {
//        //release(stack.back());// stack.remove(p(stack.back()));
//    }
//    // ctrl alt done
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k41r} )) {
//        release(KEY_CTRL);
//    }
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k42r} )) {
//        release(KEY_ALT);
//    }
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k41r,k42r} )) {
//        release(KEY_CTRL); release(KEY_ALT);// stack.pop(2); stack.pop_front(2);
//    }
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k42r,k41r} )) {
//        release(KEY_ALT); release(KEY_CTRL);// stack.pop(2); stack.pop_front(2);
//    }
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k42r,k42p} )) {
//        press(KEY_ALT);// stack.pop(2);
//    }
//    if (std::regex_match(stack.getString(), std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k41r,k41p} )) {
//        press(KEY_CTRL);// stack.pop(2);
//    }
}
