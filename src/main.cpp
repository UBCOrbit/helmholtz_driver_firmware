#include <Arduino.h>
#include <RingBuf.h>
#define BUFFER_SIZE 1000

typedef struct hVector {
    uint8_t x;
    uint8_t y;
    uint8_t z;
} hVector;

RingBuf *buf = RingBuf_new(sizeof(hVector), BUFFER_SIZE);

void setup() {
    Serial.begin(115200);
    while(!Serial); 
    if(!buf) {
        Serial.println("Failed to initialize buffer");
        while(1);
    }

    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function below
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
}

void loop()
{
    Serial.println("loop");
    String str = Serial.readStringUntil('\n');
    Serial.println(str);
}

// Interrupt is called once a millisecond, 
SIGNAL(TIMER0_COMPA_vect) 
{
}