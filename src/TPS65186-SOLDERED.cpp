/**
 **************************************************
 *
 * @file        TPS65186-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Goran Juric @ soldered.com
 ***************************************************/


#include "TPS65186-SOLDERED.h"

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
    return !(Wire.endTransmission());
}

bool TPS65186::standbyMode()
{
    Wire.beginTransmission(0x48);
    Wire.write(0x01);
    Wire.write(0x6f);
    return !(Wire.endTransmission());
}

bool TPS65186::activeMode()
{
    Wire.beginTransmission(0x48);
    Wire.write(0x01);
    Wire.write(B10101111);
    return !(Wire.endTransmission());
}