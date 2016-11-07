#include <Arduino.h>
#undef min
#undef max
#undef abs
#include <vector>

int inputs[] {14, 15, 16, 17};
int outputs[] {7,  8,  9, 10, 11, 12, 18, 19, 20, 21, 22};
// in 14, 15, 16, 17
// out  7,  8,  9, 10, 11, 12, 18, 19, 20, 21, 22

void setup()
{
    Serial.begin(9600);
    delay(1000);
    Serial.print("test print");
    Keyboard.begin();
    Mouse.begin();

    pinMode(14, INPUT_PULLDOWN);  // pin 14
    pinMode(15, INPUT_PULLDOWN);  // pin 15
    pinMode(16, INPUT_PULLDOWN);  // pin 16
    pinMode(17, INPUT_PULLDOWN);  // pin 17
    pinMode( 7, OUTPUT); // pin  7
    pinMode( 8, OUTPUT); // pin  8
    pinMode( 9, OUTPUT); // pin  9
    pinMode(10, OUTPUT); // pin 10
    pinMode(11, OUTPUT); // pin 11
    pinMode(12, OUTPUT); // pin 12
    pinMode(18, OUTPUT); // pin 18
    pinMode(19, OUTPUT); // pin 19
    pinMode(20, OUTPUT); // pin 20
    pinMode(21, OUTPUT); // pin 21
    pinMode(22, OUTPUT); // pin 22

    digitalWrite( 7, HIGH); // pin  7
    digitalWrite( 8, HIGH); // pin  8
    digitalWrite( 9, HIGH); // pin  9
    digitalWrite(10, HIGH); // pin 10
    digitalWrite(11, HIGH); // pin 11
    digitalWrite(12, HIGH); // pin 12
    digitalWrite(18, HIGH); // pin 18
    digitalWrite(19, HIGH); // pin 19
    digitalWrite(20, HIGH); // pin 20
    digitalWrite(21, HIGH); // pin 21
    digitalWrite(22, HIGH); // pin 22

    // pinMode(PIN_B5, INPUT); // pin 14
    // pinMode(PIN_B6, INPUT); // pin 15
    // pinMode(PIN_F7, INPUT); // pin 16
    // pinMode(PIN_F6, INPUT); // pin 17
    // pinMode(PIN_D2, OUTPUT); // pin 7
    // pinMode(PIN_D3, OUTPUT); // pin 8
    // pinMode(PIN_C6, OUTPUT); // pin 9
    // pinMode(PIN_C7, OUTPUT); // pin 10
    // pinMode(PIN_D6, OUTPUT); // pin 11
    // pinMode(PIN_D7, OUTPUT); // pin 12
    // pinMode(PIN_F5, OUTPUT); // pin 18
    // pinMode(PIN_F4, OUTPUT); // pin 19
    // pinMode(PIN_F1, OUTPUT); // pin 20
    // pinMode(PIN_F0, OUTPUT); // pin 21
    // pinMode(PIN_D4, OUTPUT); // pin 22

    delay(1000);
}
void loop()
{
    // if(digitalRead(14) || digitalRead(15) || digitalRead(16) || digitalRead(17))
    if(digitalRead(14)) Serial.println("pin 14");
    if(digitalRead(15)) Serial.println("pin 15");
    if(digitalRead(16)) Serial.println("pin 16");
    if(digitalRead(17)) Serial.println("pin 17");
    delay(200);
}
