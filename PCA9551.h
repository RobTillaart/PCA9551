#pragma once
//
//    FILE: PCA9551.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-17
// VERSION: 0.1.0
// PUPROSE: Arduino library for for I2C PCA9551 8 channel PWM
//     URL: https://github.com/RobTillaart/PCA9551


#include "Arduino.h"
#include "Wire.h"


#define PCA9551_LIB_VERSION         (F("0.1.0"))


//  REGISTERS
#define PCA9551_INPUT       0x00
#define PCA9551_PSC0        0x01
#define PCA9551_PWM0        0x02
#define PCA9551_PSC1        0x03
#define PCA9551_PWM1        0x04
#define PCA9551_LS0         0x05
#define PCA9551_LS1         0x06


//  MUX OUTPUT MODES
#define PCA9551_MODE_LOW      0
#define PCA9551_MODE_HIGH     1
#define PCA9551_MODE_PWM0     2
#define PCA9551_MODE_PWM1     3


//  ERROR CODES (not all used yet)
#define PCA9551_OK          0x00
#define PCA9551_ERROR       0xFF
#define PCA9551_ERR_WRITE   0xFE
#define PCA9551_ERR_CHAN    0xFD
#define PCA9551_ERR_MODE    0xFC
#define PCA9551_ERR_REG     0xFB
#define PCA9551_ERR_I2C     0xFA


/////////////////////////////////////////////////////
//
//  CLASS
//
class PCA9551
{
public:
  explicit PCA9551(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(int sda, int scl);
#endif
  bool     begin();
  bool     isConnected();
  uint8_t  reset();

  uint8_t  getAddress();
  uint8_t  outputCount();

  //  GPIO
  uint8_t  getInput();
  void     pinMode(uint8_t pin, uint8_t mode);
  void     digitalWrite(uint8_t pin, uint8_t value);
  uint8_t  digitalRead(uint8_t pin);

  //  PRESCALERS
  void     setPrescaler(uint8_t generator, uint8_t prescaler = 0);
  uint8_t  getPrescaler(uint8_t generator);

  //  PWM
  void     setPWM(uint8_t generator, uint8_t pwm = 128);
  uint8_t  getPWM(uint8_t generator);


  //  OUTPUT MODE - MUX SELECTION
  //  pin:   0..7
  //  mode:
  //    0 = output is set LOW (LED on)
  //    1 = output is set high-impedance (LED off; default)
  //    2 = output blinks at PWM0 rate
  //    3 = output blinks at PWM1 rate
  uint8_t  setOutputMode(uint8_t pin, uint8_t mode);
  uint8_t  getOutputMode(uint8_t pin);

  //  ERROR
  uint8_t  getLastError();


private:
  uint8_t  writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);

  uint8_t  _address;
  uint8_t  _outputCount;
  uint8_t  _error;

  TwoWire* _wire;
};


//  -- END OF FILE --

