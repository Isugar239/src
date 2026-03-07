#pragma once

#include "project_config.h"
#include "../New Folder/GPIO.h"

class soft_i2c
{
public:
    soft_i2c(GPIO& sclPin, GPIO& sdaPin);

    bool start();
    bool stop();
    void sendAck();
    void sendNack();
    void write(bool dt);
    bool send(uint8_t addr, uint8_t package);

    uint8_t read(uint8_t addr);
uint8_t readRegister(uint8_t addr, uint8_t reg);

private:
    GPIO& _sclPin;
    GPIO& _sdaPin;

    bool readScl();
    bool readSda();
    void sdaHigh();
    void sdaLow();
    void sclHigh();
    void sclLow();
    void delay(uint32_t d);
    bool readAck();
		
};
