#include "soft_i2c.h"

soft_i2c::soft_i2c(GPIO& sclPin, GPIO& sdaPin)
    : _sclPin(sclPin),
      _sdaPin(sdaPin)
{
    sdaHigh();
    sclHigh();
}

bool soft_i2c::readScl(){
    return _sclPin.readBit();
}

bool soft_i2c::readSda(){
    return _sdaPin.readBit();
}

void soft_i2c::sdaHigh(){
    _sdaPin.setBit();
}

void soft_i2c::sdaLow(){
    _sdaPin.resetBit();
}

void soft_i2c::sclHigh(){
    _sclPin.setBit();
}

void soft_i2c::sclLow(){
    _sclPin.resetBit();
}

void soft_i2c::delay(uint32_t d){
    for (volatile uint32_t i = d; i > 0; i--) {
    }
}

bool soft_i2c::start(){
    sdaHigh();
    sclHigh();
    delay(35);
    if (!readSda()) {
        //return false;
    }

    sdaLow();
    delay(35);
    if (readSda()) {
       // return false;
    }

    sclLow();
    delay(35);
    if (readScl()) {
        //return false;
    }

    return true;
}

bool soft_i2c::stop(){
    sclLow();
    delay(35);
    sdaLow();
    delay(35);

    sclHigh();
    delay(35);
    sdaHigh();
    delay(35);

    return true;
}

void soft_i2c::sendAck(){
    sclLow();
    delay(35);
    sdaLow();
    delay(35);
    sclHigh();
    delay(35);
    sclLow();
    delay(35);
    sdaHigh();
}

void soft_i2c::sendNack(){
    sclLow();
    delay(35);
    sdaHigh();
    delay(35);
    sclHigh();
    delay(35);
    sclLow();
    delay(35);
}

void soft_i2c::write(bool dt){
    sclLow();
    delay(35);

    if (dt) {
        sdaHigh();
    } else {
        sdaLow();
    }

    delay(35);
    sclHigh();
    delay(35);
    //sclLow();
   // delay(35);
}

bool soft_i2c::readAck(){
    sclLow();
    delay(35);

    sclHigh();
    delay(35);
    const bool ack = !readSda();

    delay(35);

    sclLow();
    delay(35);

    return ack;
}

bool soft_i2c::send(uint8_t addr, uint8_t package){
    if (!start()) {
        return false;
    }


    for (int i = 0; i < 7; i++) {
        write((addr & 0x80));
        addr <<= 1;
    }
    write(0);

//    if (!readAck()) {
//        stop();
//        return false;
//    }

    for (int i = 0; i < 8; i++) {
        write((package & 0x80));
        package <<= 1;
    }

//    if (!readAck()) {
//        stop();
//        return false;
//    }

    return stop();
}


uint8_t soft_i2c::read(uint8_t addr){
	
	  if (!start()) {
        return false;
    }


    for (int i = 0; i < 7; i++) {
        write((addr & 0x80));
        addr <<= 1;
    }
    write(1);





    uint8_t data = 0;

    sdaHigh();
    delay(35);

    for (int i = 0; i < 8; i++) {
        data <<= 1;
        sclLow();
        delay(35);
        sclHigh();
        delay(35);
        if (readSda()) {
            data |= 0x01;
        }
    }
sclLow();
		delay(35);
		stop();
    return data;
	}
uint8_t soft_i2c::readRegister(uint8_t addr, uint8_t reg) {
    start();
    
    uint8_t addrWrite = addr << 1;
    for (int i = 0; i < 8; i++) {
        write((addrWrite & 0x80));
        addrWrite <<= 1;
    }
     readAck();

    uint8_t regCopy = reg;
    for (int i = 0; i < 8; i++) {
        write((regCopy & 0x80));
        regCopy <<= 1;
    }
    sclLow(); delay(35);
    readAck();

    stop();
    start();

    uint8_t addrRead = (addr << 1) | 0x01;
    for (int i = 0; i < 8; i++) {
        write((addrRead & 0x80));
        addrRead <<= 1;
    }
    sclLow(); delay(35);
    if (!readAck()) return 0xDD;

    sdaHigh();
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
        data <<= 1;
        sclLow(); delay(35);
        sclHigh(); delay(35);
        if (readSda()) data |= 0x01;
    }
    sclLow(); delay(35);
    stop();
    return data;
}