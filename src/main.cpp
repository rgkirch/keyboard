#include "Arduino.h"

char inputs[] {14, 15, 16, 17};
char outputs[] {7,  8,  9, 10, 11, 12, 18, 19, 20, 21, 22, 23};
bool matrix[48] = {false}; // state of keys last scanned (pressed on not pressed) // 12 * 4
// in 14, 15, 16, 17
// out  7,  8,  9, 10, 11, 12, 18, 19, 20, 21, 22

void setup()
{

//    memset(matrix, 0, 48 * sizeof(char));
    Serial.begin(9600);
    delay(1000);
    Serial.print("test print");
//    Keyboard.begin();
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
//    Serial.print("inputs ");
//    Serial.println((int)sizeof(inputs));
//    Serial.print("outputs ");
//    Serial.println((int)sizeof(outputs));
//    Serial.print("matrix ");
//    Serial.println((int)sizeof(matrix));
//    Mouse.move(4, 0);
//    delay(25);
//    Mouse.move(-4, 0);
//    delay(25);
//    Serial.println("loop");
    delay(200);
    for (auto c :matrix) {
        Serial.print(c);
        Serial.print(" ");
    }
    Serial.println();
    for(int i = 0; i < sizeof(outputs) / sizeof(char); i++)
    {
        digitalWrite(outputs[i], HIGH);
        for(int j = 0; j < sizeof(inputs) / sizeof(char); j++)
        {
            bool state = digitalRead(inputs[j]);
//            Serial.print("state ");
//            Serial.println(state);
            int location = (sizeof(outputs) / sizeof(char)) * i + j;
            if(state != matrix[location]) // if there is a change
            {
                if(state)
                {
                    matrix[location] = 1;
                } else {
                    matrix[location] = 0;
                }
                Serial.print(i);
                Serial.print(" ");
                Serial.println(j);
            }
        }
        digitalWrite(outputs[i], LOW);
    }
//    delay(1000);
}
