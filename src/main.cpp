#include "Arduino.h"

char inputs[] {14, 15, 16, 17};
char outputs[] {7,  8,  9, 10, 11, 12, 18, 19, 20, 21, 22, 23};
char matrix[48]; // state of keys last scanned (pressed on not pressed) // 12 * 4
// in 14, 15, 16, 17
// out  7,  8,  9, 10, 11, 12, 18, 19, 20, 21, 22

void setup()
{

    memset(matrix, 0, 12 * 4 * sizeof(char));
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
    Serial.print("inputs ");
    Serial.println((int)sizeof(inputs));
    Serial.print("outputs ");
    Serial.println((int)sizeof(outputs));
    Serial.print("matrix ");
    Serial.println((int)sizeof(outputs));
//    Mouse.move(4, 0);
//    delay(25);
//    Mouse.move(-4, 0);
//    delay(25);
//    Serial.println("loop");
    for(char i = 0; i < sizeof(outputs) / sizeof(char); i++)
    {
        digitalWrite(outputs[i], HIGH);
        for(char j = 0; j < sizeof(inputs) / sizeof(char); j++)
        {
            char state = digitalRead(inputs[j]);
            if(state != matrix[i*j]) // if there is a change
            {
                if(state)
                {
                    matrix[i*j] = 1;
                } else {
                    matrix[i*j] = 0;
                }
                Serial.println((i+1)*(i+1)*(j+1));
            }
        }
        digitalWrite(outputs[i], LOW);
    }
//    delay(1000);
}
