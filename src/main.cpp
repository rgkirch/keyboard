#include <Arduino.h>
#undef min
#undef max
#undef abs
#include <vector>

int inputs[] {14, 15, 16, 17};
int outputs[] {7,  8,  9, 10, 11, 12, 18, 19, 20, 21, 22, 23};
// in 14, 15, 16, 17
// out  7,  8,  9, 10, 11, 12, 18, 19, 20, 21, 22

void setup()
{
    Serial.begin(9600);
    delay(1000);
    Serial.print("test print");
    Keyboard.begin();
    Mouse.begin();

    for(int i = 0; i < sizeof(inputs) / sizeof(int); i++)
    {
        pinMode(inputs[i], INPUT_PULLDOWN);
    }
    for(int i = 0; i < sizeof(outputs) / sizeof(int); i++)
    {
        pinMode(outputs[i], OUTPUT);
        digitalWrite(outputs[i], LOW);
    }

    delay(1000);
}
void loop()
{
    for(int i = 0; i < sizeof(outputs) / sizeof(int); i++)
    {
        digitalWrite(outputs[i], HIGH);
        for(int j = 0; j < sizeof(inputs) / sizeof(int); j++)
        {
            if(digitalRead(inputs[j]))
            {
                Serial.println((i+1)*(i+1)*(j+1));
            }
        }
        digitalWrite(outputs[i], LOW);
    }
}
