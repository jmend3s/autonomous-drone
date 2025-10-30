#include <Arduino.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7,8);

byte constexpr address[6] = "00001";

void setup()
{
    Serial.begin(115200);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();

    Serial.println("Comms started");
}

void loop()
{
    if (radio.available())
    {
        char text[32] = "";
        radio.read(&text, sizeof(text));
        if (text[0] == 'H')
            Serial.println(text);
    }
}