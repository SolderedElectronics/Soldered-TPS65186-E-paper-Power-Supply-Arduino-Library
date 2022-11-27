/**
 **************************************************
 *
 * @file        TPS65186.ino
 * @brief       Example template for easyC sensors
 *
 *
 *
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#include "TPS65186-SOLDERED.h"

TPS65186 tps;

void setup()
{
    Serial.begin(115200);                 // Begin serial comunication
    tps.begin();                          // Initialize tps
    tps.setPowerUpSequence(3, 1, 2, 0);   // Setting power up sequence
    tps.activeMode();                     // Turn TPS in active mode and power up default rails
    tps.setVCOM(-3500, 0);                // Set VCOM to -3.1V
    Serial.println(tps.readPowerGood());  // Read power good register and print it to serial
    Serial.println(tps.thermistorRead()); // Read temperature from thermistor
    delay(5000);                          // Wait 5 seconds
    tps.standbyMode();                    // Turn TPS in standby mode
}

void loop()
{
}
