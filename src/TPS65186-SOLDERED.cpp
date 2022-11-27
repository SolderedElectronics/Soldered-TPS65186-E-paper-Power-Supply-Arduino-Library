/**
 **************************************************
 *
 * @file        TPS65186-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric, Karlo Leksic for soldered.com
 ***************************************************/


#include "TPS65186-SOLDERED.h"

/**
 * @brief                   Sensor specific native constructor.
 */
TPS65186::TPS65186()
{
    native = 1;
}

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void TPS65186::initializeNative()
{
    Wire.begin();
}


/**
 * @brief         Enable one rail
 *
 * @param rail    The rail you want to enable
 *
 * @return        1 if its successful, 0 if its not
 */
bool TPS65186::enableRail(rail_t rail)
{
    Wire.beginTransmission(addr);
    uint8_t temp;
    readRegister(0x01, &temp, 1);
    Wire.write(0x01);
    Wire.write(temp | rail);
    return !(Wire.endTransmission());
}

/**
 * @brief          Disable one rail
 *
 * @param rail     The rail you want to disable
 *
 * @return         None
 */
bool TPS65186::disableRail(rail_t rail)
{
    Wire.beginTransmission(addr);
    uint8_t temp;
    readRegister(0x01, &temp, 1);
    Wire.write(0x01);
    Wire.write(temp & ~(rail));
    return !(Wire.endTransmission());
}

/**
 * @brief          Adjusting output voltage on the VCOM pin
 *
 * @param voltage  Voltage to set
 *
 * @return         1 if its successful, 0 if its not
 */
bool TPS65186::voltageAdjust(voltageAdjust_t voltage)
{
    Wire.beginTransmission(addr);
    Wire.write(0x02);    // Writting to the Voltage Adjustment Register - VADJ
    Wire.write(voltage); // jel netreba tu samo ove vrijednosti koje imamo u defineovima - onda bi ih se dodalo u enum
    return !(Wire.endTransmission());
}

/**
 * @brief          Put TPS into standby mode
 *
 * @return         1 if its successful, 0 if its not
 */
bool TPS65186::standbyMode()
{
    byte reg;
    readRegister(0x01, &reg, 1);
    byte data = (1 << 6) | reg;
    Wire.beginTransmission(addr);
    Wire.write(0x01);
    Wire.write(data);
    return !(Wire.endTransmission());
}

/**
 * @brief          Put TPS into active mode
 *
 * @return         1 if its successful, 0 if its not
 */
bool TPS65186::activeMode()
{
    byte reg;
    readRegister(0x01, &reg, 1);
    byte data = (1 << 7) | reg;
    Wire.beginTransmission(addr);
    Wire.write(0x01);
    Wire.write(data);
    return !(Wire.endTransmission());
}

/**
 * @brief          Read the thermistor value
 *
 * @return         Thermistor value read by ADC
 */
byte TPS65186::thermistorRead()
{
    byte temp;
    Wire.beginTransmission(addr);
    Wire.write(0x0D);
    Wire.write(B11000000); // Set READ_THEM to 1
    Wire.endTransmission();

    delay(5);

    Wire.beginTransmission(addr);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(addr, 1); // Read thermistor value from TMST_VALUE register
    if (Wire.available())
    {
        temp = Wire.read();
    }

    return temp;
}

/**
 * @brief           Set on which strobe will be powered up each rail
 *                  Number must be from 0 to 3.
 *                  0 -> power up on STROBE1
 *                  1 -> power up on STROBE2
 *                  2 -> power up on STROBE3
 *                  3 -> power up on STROBE4
 *
 * @param vddh      A number from 0 to 3 to determine on which strobe VDDH will be powered up
 *
 * @param vpos      A number from 0 to 3 to determine on which strobe VPOS will be powered up
 *
 * @param vee       A number from 0 to 3 to determine on which strobe VEE will be powered up
 *
 * @param vneg      A number from 0 to 3 to determine on which strobe VNEG will be powered up
 *
 * @return          None
 */
void TPS65186::setPowerUpSequence(byte vddh, byte vpos, byte vee, byte vneg)
{
    if (vddh > 3 || vpos > 3 || vee > 3 || vneg > 3)
    {
        return;
    }

    byte data;
    data = (vddh << 6) | (vpos << 4) | (vee << 2) | vneg;

    Wire.beginTransmission(addr);
    Wire.write(0x09);
    Wire.write(data);
    Wire.endTransmission();
}

/**
 * @brief              Set delays for power up to each sequence.
 *                     Number must be from 0 to 3.
 *                     0 -> 3  ms
 *                     1 -> 6  ms
 *                     2 -> 9  ms
 *                     3 -> 12 ms
 *
 * @param dly1         Defines the delay time from VN_PG high to STROBE1 during power up
 *
 * @param dly2         Defines the delay time from STROBE1 to STROBE2 during power up
 *
 * @param dly3         Defines the delay time from STROBE2 to STROBE3 during power up
 *
 * @param dly4         Defines the delay time from STROBE3 to STROBE4 during power up
 *
 * @return             None
 */
void TPS65186::setPowerUpDelays(byte dly1, byte dly2, byte dly3, byte dly4)
{
    if (dly1 > 3 || dly2 > 3 || dly3 > 3 || dly4 > 3)
    {
        return;
    }

    byte data;
    data = (dly4 << 6) | (dly3 << 4) | (dly2 << 2) | dly1;

    Wire.beginTransmission(addr);
    Wire.write(0x0A); // Power up sequence register
    Wire.write(data);
    Wire.endTransmission();
}

/**
 * @brief           Function to enable all rails
 *
 * @return          None
 */
void TPS65186::enableAllRails()
{
    byte data = B00101111;

    Wire.beginTransmission(addr);
    Wire.write(0x01);
    Wire.write(data);
    Wire.endTransmission();
}

/**
 * @brief           Set on which strobe will be powered down each rail
 *                  Number must be from 0 to 3.
 *                  0 -> power up on STROBE1
 *                  1 -> power up on STROBE2
 *                  2 -> power up on STROBE3
 *                  3 -> power up on STROBE4
 *
 * @param vddh      A number from 0 to 3 to determine on which strobe VDDH will be powered down
 *
 * @param vpos      A number from 0 to 3 to determine on which strobe VPOS will be powered down
 *
 * @param vee       A number from 0 to 3 to determine on which strobe VEE will be powered down
 *
 * @param vneg      A number from 0 to 3 to determine on which strobe VNEG will be powered down
 *
 * @return          None
 */
void TPS65186::setPowerDownSequence(byte vddh, byte vpos, byte vee, byte vneg)
{
    if (vddh > 3 || vpos > 3 || vee > 3 || vneg > 3)
    {
        return;
    }

    byte data;
    data = (vddh << 6) | (vpos << 4) | (vee << 2) | vneg;

    Wire.beginTransmission(addr);
    Wire.write(0x0B);
    Wire.write(data);
    Wire.endTransmission();
}

/**
 * @brief              Set delays for power down to each sequence.
 *                     Number must be from 0 to 3.
 *                     0 -> 6  ms
 *                     1 -> 12 ms
 *                     2 -> 24 ms
 *                     3 -> 48 ms
 *
 * @param dly1         Defines the delay time from VN_PG high to STROBE1 during power down
 *
 * @param dly2         Defines the delay time from STROBE1 to STROBE2 during power down
 *
 * @param dly3         Defines the delay time from STROBE2 to STROBE3 during power down
 *
 * @param dly4         Defines the delay time from STROBE3 to STROBE4 during power down
 *
 * @return             None
 */
void TPS65186::setPowerDownDelays(byte dly1, byte dly2, byte dly3, byte dly4)
{
    if (dly1 > 3 || dly2 > 3 || dly3 > 3 || dly4 > 3)
    {
        return;
    }

    byte data;
    data = (dly4 << 6) | (dly3 << 4) | (dly2 << 2) | dly1;

    Wire.beginTransmission(addr);
    Wire.write(0x0A); // Power up sequence register
    Wire.write(data);
    Wire.endTransmission();
}

/**
 * @brief             Functions reads power good status for each rail
 *
 * @return            Power good status register
 */
byte TPS65186::readPowerGood()
{
    byte reg;
    Wire.beginTransmission(addr);
    Wire.write(0x0F); // Power good register
    Wire.requestFrom(addr, 1);
    if (Wire.available())
    {
        reg = Wire.read();
    }
    return reg;
}

/**
 * @brief               Set threshold values for high and low-temperature interrupts.
 *                      If the diference between baseline temperature and threshold is equal or greater than the
 *                      threshold value, an interrupt issued.
 *                      Default is 0 and 50.
 *
 * @param coldThreshold The threshold for low temperature. A number from 0 to 15 represents temperatures from -7 to 8
 *                      degrees
 *
 * @param hotThreshold  The threshold for low temperature. A number from 0 to 15 represents temperatures from 42 to 57
 *                      degrees
 *
 * @return              None
 */
void TPS65186::setThermistorThresholds(byte coldThreshold, byte hotThreshold)
{
    if (coldThreshold > 15 || hotThreshold > 15)
    {
        return;
    }

    byte data = (coldThreshold << 4) | hotThreshold;

    Wire.beginTransmission(addr);
    Wire.write(0x0E);
    Wire.write(data);
    Wire.endTransmission();
}

/**
 * @brief             Set the VCOM output of the amplifier with a voltage from 0 to -5.11 V, adjustable in 10 mV steps.
 *
 * @param voltage     Voltage to set from 0 to -5110 mV
 *
 * @param store       1 to store VCOM, 0 to not store
 *
 * @return            None
 */
void TPS65186::setVCOM(int voltage, bool store)
{
    if (voltage < -5110)
    {
        return;
    }

    int v = abs(voltage); // Get positive value
    v /= 10;              // Get number from 0 to 511 instead of 0 - 5110
    byte b1, b2 = 0;
    b1 = v - 256; // Get 8bit number
    if (v > 255)
    {
        b2 = 1;
    }

    if (store == 1)
    {
        b2 |= 64;
    }

    Wire.beginTransmission(addr);
    Wire.write(0x03); // VCOM1 register
    Wire.write(b1);
    Wire.endTransmission();

    Wire.beginTransmission(addr);
    Wire.write(0x04); // VCOM2 register
    Wire.write(b2);
    Wire.endTransmission();
}