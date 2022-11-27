/**
 **************************************************
 *
 * @file        TPS65186-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric, Karlo Leksicfor soldered.com
 ***************************************************/

#ifndef __TPS65186__
#define __TPS65186__

#include "Arduino.h"
#include "Wire.h"
#include "libs/Generic-easyC/easyC.hpp"

// Rail enumerated type used with enableRail() method to enable one rail
enum rail_t
{
    V3P3 = 1 << 5,
    VCOM = 1 << 4,
    VDDH = 1 << 3,
    VPOS = 1 << 2,
    VEE = 1 << 1,
    VNEG = 1 << 0
};

// Its last 3 LSB bits, others are not in use -> V1500 - 0000 0011 in register
enum voltageAdjust_t
{
    V1500 = 011, // VADJ register value for setting 15.000 V
    V1475 = 100, // VADJ register value for setting 14.750 V
    V1450 = 101, // VADJ register value for setting 14.500 V
    V1425 = 110  // VADJ register value for setting 14.250 V
};

class TPS65186 : public EasyC
{
  public:
    TPS65186();
    void initializeNative();
    bool enableRail(rail_t);
    bool disableRail(rail_t);
    void enableAllRails();
    bool voltageAdjust(voltageAdjust_t);
    bool standbyMode();
    bool activeMode();
    void setPowerUpSequence(byte, byte, byte, byte);
    void setPowerDownSequence(byte, byte, byte, byte);
    void setPowerUpDelays(byte, byte, byte, byte);
    void setPowerDownDelays(byte, byte, byte, byte);
    void setThermistorThresholds(byte, byte);
    void setVCOM(int, bool);
    byte readPowerGood();
    byte thermistorRead();

  protected:
  private:
    byte addr = 0x48;
};

#endif
