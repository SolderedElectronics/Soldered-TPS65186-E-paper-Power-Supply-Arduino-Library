/**
 **************************************************
 *
 * @file        Generic-easyC-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/

#ifndef __TPS65186__
#define __TPS65186__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

#define V3P3 1 << 5
#define VCOM 1 << 4
#define VDDH 1 << 3
#define VPOS 1 << 2
#define VEE  1 << 1
#define VNEG 1 << 0

#define V1500 011
#define V1475 100
#define V1450 101
#define V1425 110


class TPS65186 : public EasyC
{
  public:
    TPS65186(int _pin);

  protected:
    void initializeNative();
    bool begin();

  private:
    int pin;
};

#endif
