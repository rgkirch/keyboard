#include "Arduino.h"

char inputs[] = {14, 15, 16, 17};
char outputs[] = {23, 18, 19, 20, 21, 22, 7, 8, 9, 10, 11, 12};
int keymap[] = {'\'', ',', '.', 'p', 'y', 'y', 'f', 'g', 'c', 'r', 'l', '/',
'key_esc', 'a', 'o', 'e', 'u', 'i', 'd', 'h', 't', 'n', 's', '-',
'key_left_shift', ';', 'q', 'j', 'k', 'x', 'b', 'm', 'w', 'v', 'z', 'key_right_shift',
'key_left_ctrl', 'key_left_gui', 'key_left_alt', 'key_left_arrow', 'key_down_arrow', ' ', ' ', ' ', 'key_up_arrow', 'key_right_arrow', 'key_right_alt', 'key_right_ctrl'};
bool matrix[48] = {false}; // state of keys last scanned (pressed on not pressed) // 12 * 4
int times[48] = {0}; // state of keys last scanned (pressed on not pressed) // 12 * 4
// in 14, 15, 16, 17
// out  7,  8,  9, 10, 11, 12, 18, 19, 20, 21, 22

void setup()
{

//    memset(matrix, 0, 48 * sizeof(char));
    Serial.begin(9600);
    delay(1000);
    Serial.print("test print");
    Keyboard.begin();
//    Mouse.begin();

    for(char i = 0; i < sizeof(inputs) / sizeof(char); i++)
    {
        pinMode(inputs[i], INPUT_PULLDOWN);
    }
    for(char i = 0; i < sizeof(outputs) / sizeof(char); i++)
    {
        pinMode(outputs[i], OUTPUT);
        digitalWrite(outputs[i], LOW);
    }

    delay(1000);
}
void loop()
{
//    Mouse.move(4, 0);
//    delay(25);
//    Mouse.move(-4, 0);
//    delay(25);
//    Serial.println("loop");
//    delay(200);
//    for (auto c : matrix) {
//        Serial.print(c);
//        Serial.print(" ");
//    }
//    Serial.println();
    for(int i = 0; i < sizeof(outputs) / sizeof(char); i++)
    {
        digitalWrite(outputs[i], HIGH);
        for(int j = 0; j < sizeof(inputs) / sizeof(char); j++)
        {
            bool state = digitalRead(inputs[j]);
//            Serial.print("state ");
//            Serial.println(state);
            int location = (sizeof(outputs) / sizeof(char)) * j + i;
            if(state != matrix[location]) // if there is a change
            {
                if(state)
                {
                    if(millis() - times[location] > 30) {
                        matrix[location] = 1;
                        Keyboard.press(keymap[location]);
                    }
                } else {
                    times[location] = millis();
                    matrix[location] = 0;
                    Keyboard.release(keymap[location]);
                }
//                Serial.print(i);
//                Serial.print(" ");
//                Serial.println(j);
            }
        }
        digitalWrite(outputs[i], LOW);
    }
//    delay(1000);
}
