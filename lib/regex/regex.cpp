#include "regex.h"

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

void push(int key) {
    stack.push(key);
    // space and backspace
    try {
        if (std::regex_match(inputString, std::regex {k42p,k42r} ))
        {
            send(KEY_SPACE); stack.pop(2); assert(stack.empty());
        }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
        if (std::regex_match(inputString, std::regex {k41p,k41r} ))
        {
            send(KEY_BACKSPACE); stack.pop(2); assert(stack.empty());
        }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
        // enter and delete
        if (std::regex_match(inputString, std::regex {k41p,k42p,k42r} ))
        {
            send(KEY_ENTER);
        }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
        if (std::regex_match(inputString, std::regex {k41p,'(',k42p,k42r,')','{','2','}'} )) {
            send(KEY_ENTER); stack.pop(2);
        }
    } catch (std::regex_error& e) {
        std::cout << e.what() << std::endl;
    } try {
        if (std::regex_match(inputString, std::regex { k41p,k42p,k42r,k41r } )) {
            std::clog << "stack.pop(4); assert(stack.empty());" << std::endl;
            stack.pop(4); assert(stack.empty());
        }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
        if (std::regex_match(inputString, std::regex {k42p,k41p,k41r} )) {
            send(KEY_DELETE);
        }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
        if (std::regex_match(inputString, std::regex {k42p,'(',k41p,k41r,')','{','2','}'} )) {
            send(KEY_DELETE); stack.pop(2);
        }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
        if (std::regex_match(inputString, std::regex {k42p,k41p,k41r,k42r} )) {
            std::clog << "stack.pop(4); assert(stack.empty());" << std::endl;
            stack.pop(4); assert(stack.empty());
        }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } /*try {
        // ctrl alt other_key
        //if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|',k42p,k41p,')',KEYp} )) {
            //press(KEY_CTRL); press(KEY_ALT);// press(stack.back());
        //}
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
//            if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', '(',KEYp,')', ('?',':',k41r'|',k42r,')',* \1r} )) {
//                //release(stack.back());
//            }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
//            if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', '(',KEYp,')', ('?',':',k41r'|',k42r,')',* \1r ('?',':',k41r'|',k42r,')',* KEYp} )) {
//                //press(stack.back());// int t = stack.back(); stack.pop(3); stack.push_back(t);
//            }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
//            if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', ('?',':',KEYp ('?',':',k41r'|',k42r,')',*,')','+', KEYp} )) {
//                //press(stack.back());
//            }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
//            if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', ('?',':','?',=('?',':',KEYp ('?',':',k41r'|',k42r,')',*,')','+', KEYp,')', ('?',':',KEYp* ,'(',KEYp,')', KEYp*,')', \1r} )) {
//                //release(stack.back());// stack.remove(p(stack.back()));
//            }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
//            // ctrl alt done
//            if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k41r} )) {
//                release(KEY_CTRL);
//            }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
//            if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k42r} )) {
//                release(KEY_ALT);
//            }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
//            if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k41r,k42r} )) {
//                release(KEY_CTRL); release(KEY_ALT);// stack.pop(2); stack.pop_front(2);
//            }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
//            if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k42r,k41r} )) {
//                release(KEY_ALT); release(KEY_CTRL);// stack.pop(2); stack.pop_front(2);
//            }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
//            if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k42r,k42p} )) {
//                press(KEY_ALT);// stack.pop(2);
//            }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    } try {
//            if (std::regex_match(inputString, std::regex {'(','?',':',k41p,k42p,'|', k42p,k41p,')', KEYp,'+', k41r,k41p} )) {
//                press(KEY_CTRL);// stack.pop(2);
//            }
    } catch (std::regex_error e) {
        std::cout << e.what() << std::endl;
    }
    */
}
