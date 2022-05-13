/**
 **************************************************
 *
 * @file        Generic-easyC-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/


#include "Generic-easyC-SOLDERED.h"

/**
 * @brief                   Sensor specific native constructor.
 *
 * @param int _pin          Example parameter.
 */
TPS65186::TPS65186(int _pin)
{
    pin = _pin;
    native = 1;
}

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void TPS65186::initializeNative()
{
    pinMode(pin, INPUT);
}

bool TPS65186::begin()
{

    EasyC::begin();
}

bool TPS65186::enableRail(int rail)
{
    Wire.beginTransmission(0x48);
    uint8_t temp;
    readRegister(0x01, &temp, 1);
    Wire.write(0x01);
    Wire.write(temp | rail);
    return !(Wire.endTransmission());
}

bool TPS65186::disableRail(int rail)
{
    Wire.beginTransmission(0x48);
    uint8_t temp;
    readRegister(0x01, &temp, 1);
    Wire.write(0x01);
    Wire.write(temp & ~(rail));
    return !(Wire.endTransmission());
}

bool TPS65186::voltageAdjust(int voltage)
{
    Wire.beginTransmission(0x48);
    Wire.write(0x0);
    Wire.write(voltage);
}



/*
    Wire.beginTransmission(0x48);
    Wire.write(0x09);
    Wire.write(B00011011); // Power up seq.
    Wire.write(B00000000); // Power up delay (3mS per rail)
    Wire.write(B00011011); // Power down seq.
    Wire.write(B00000000); // Power down delay (6mS per rail)
    Wire.endTransmission();


 // Put TPS65186 into standby mode (leaving 3V3 SW active)
    VCOM_CLEAR;
    Wire.beginTransmission(0x48);
    Wire.write(0x01);
    Wire.write(0x6f);
    Wire.endTransmission();

    // Wait for all PWR rails to shut down
    delay(100);

    // Disable 3V3 to the panel
    Wire.beginTransmission(0x48);
    Wire.write(0x01);
    Wire.write(0x4f);
    Wire.endTransmission();

     // Enable all rails
    Wire.beginTransmission(0x48);
    Wire.write(0x01);
    Wire.write(B00101111);
    Wire.endTransmission();

    // Modify power up sequence  (VEE and VNEG are swapped)
    Wire.beginTransmission(0x48);
    Wire.write(0x09);
    Wire.write(B11100001);
    Wire.endTransmission();

    delay(1);

    // Switch TPS65186 into active mode
    Wire.beginTransmission(0x48);
    Wire.write(0x01);
    Wire.write(B10101111);
    Wire.endTransmission();
*/