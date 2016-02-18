/*
 *    Example-Code that emulates a DS2438 Smart Battery Monitor
 *    Tested with https://github.com/PaulStoffregen/OneWire --> still untested
 */

#include "OneWireHub.h"
#include "DS2438.h"  // Smart Battery Monitor

const uint8_t led_PIN       = 13;         // the number of the LED pin
const uint8_t OneWire_PIN   = 8;

auto hub    = OneWireHub(OneWire_PIN);
auto ds2438 = DS2438( 0x26, 0x0D, 0x02, 0x04, 0x03, 0x08, 0x0A );    //      - Smart Battery Monitor

bool blinking()
{
    const  uint32_t interval    = 500;          // interval at which to blink (milliseconds)
    static uint32_t nextMillis  = millis();     // will store next time LED will updated

    if (millis() > nextMillis)
    {
        nextMillis += interval;             // save the next time you blinked the LED
        static uint8_t ledState = LOW;      // ledState used to set the LED
        if (ledState == LOW)    ledState = HIGH;
        else                    ledState = LOW;
        digitalWrite(led_PIN, ledState);
        return 1;
    }
    return 0;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("OneWire-Hub DS2438 Smart Battery Monitor");

    // Setup OneWire
    hub.attach(ds2438);

    Serial.println("config done");
}

void loop()
{
    // following function must be called periodically
    hub.waitForRequest(false);

    // Blink triggers the state-change
    if (blinking())
    {

    }
}