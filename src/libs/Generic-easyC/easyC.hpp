/**
 **************************************************
 *
 * @file        easyC.hpp
 * @brief       Basic funtions for easyC libraries
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric, Karlo Leksic for soldered.com
 ***************************************************/

#ifndef __EASYC__
#define __EASYC__

#include "Arduino.h"
#include "Wire.h"

class EasyC
{
public:
    /**
     * @brief       Main constructor for easyC version
     *
     */
    EasyC()
    {
        native = 0;
    }

    /**
     * @brief       Initializes sensors on native or easyC on default address
     */
    void begin()
    {
        if (native)
            initializeNative();
        else
            begin(defaultAddress);
        beginDone = 1;
    }

    /**
     * @brief                  Initializes sensors on supplied i2c address
     *
     * @param uint8_t _address Custom easyC sensor address
     */
    void begin(uint8_t _address)
    {
        address = _address;

        Wire.begin();

        beginDone = 1;
    }

    int native = 0;
    bool beginDone = 0;

    virtual void initializeNative() = 0;

    int err;

    byte address;
    const byte defaultAddress = 0x48;

    /**
     * @brief                Private function to send a single byte to sensor
     *
     * @param  byte regAddr  Address of register to access later
     *
     * @return int           Standard endTransmission error codes
     */
    int sendAddress(byte regAddr)
    {
        Wire.beginTransmission(address);
        Wire.write(regAddr);

        return err = Wire.endTransmission();
    }

    /**
     * @brief           Private function to read n bytes over i2c
     *
     * @param  byte a[] Array to read data to
     * @param  int n    Number of bytes to read
     *
     * @return int      Error code, always 0
     */
    int readData(byte a[], int n)
    {
        Wire.requestFrom(address, n);
        Wire.readBytes(a, n);

        return 0;
    }

    /**
     * @brief                   Private function to send over i2c and then read n bytes
     *
     * @param byte regAddr      Address of register to access data from
     * @param byte a            Array to put data in
     * @param size_t n          Size of data to read
     *
     * @return int              0 if read successfuly, error code from endTransmission if not
     */
    int readRegister(byte regAddr, byte a[], size_t n)
    {
        if (sendAddress(regAddr))
            return err;

        if (readData(a, n))
            return err;

        return 0;
    }

    /**
     * @brief           Private function to write n bytes over i2c
     *
     * @param byte a[]  Array to read data from
     * @param int n     Number of bytes to read
     *
     * @return int       Standard endTransmission error codes
     */
    int sendData(const uint8_t *a, int n)
    {
        Wire.beginTransmission(address);
        Wire.write(a, n);

        return err = Wire.endTransmission();
    }
};

#endif
