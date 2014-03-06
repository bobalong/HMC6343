
/*
 * HMC6343.h - A library for using the HMC6343 compass with a ardunio.
  * 
 * Author: Jordan Springett
 * GitHub: https://github.com/JSpringett
 *
 * This code is released under the terms of the LGPLv3 licence.
 */

#ifndef HMC6343_H
#define HMC6343_H

#include "Arduino.h"

#define HMC6343_ADDRESS 0x19
#define HMC6343_BEARING_REG 0x50
 #define HMC6343_ACCELEROMETER_REG 0x50

 class HMC6343 {
 public:
 	HMC6343();
 	float GetHeading();
 	float GetPitch();
 	float GetRoll();
 	float GetXAcc();
 	float GetYAcc();
 	float GetZAcc();
 private:
 	void ReadCompass(byte register, float& v0, float& v1, float& v2 );
 	float ReadValue();
 	float CombineByte(byte high, byte low);
 };

 #endif
