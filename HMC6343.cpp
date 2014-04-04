
/*
 * HMC6343.cpp - A library for using the HMC6343 compass with a ardunio.
 * 
 * Author: Jordan Springett
 * GitHub: https://github.com/JSpringett
 *
 * This code is released under the terms of the LGPLv3 licence.
 */

#include "Arduino.h"
#include "Wire.h"
#include "HMC6343.h"

 #define Null 0

//*******************************************************************************//
//  Constructor											 
//*******************************************************************************//
	

//=====================================================================
HMC6343::HMC6343() {
	Wire.begin();
	TimeOut = 2000;
}

//*******************************************************************************//
//  Public Methods											 
//*******************************************************************************//


//=====================================================================
bool HMC6343::IsFunctioning() {
	int x, y, z;
	if(ReadCompass(HMC6343_BEARING_REG, x, y, z))
		return true;
	return false;
}

//=====================================================================
void HMC6343::GetBearing(int& heading, int& pitch, int& roll) {
	ReadCompass(HMC6343_BEARING_REG, heading, pitch, roll);
	heading = heading/10;
	pitch = pitch/10;
	roll = roll/10;
}

//=====================================================================
void HMC6343::GetAcceleration(int& x, int& y, int& z) {
	ReadCompass(HMC6343_ACCELEROMETER_REG, x, y, z);
	x /= 10;
	y /= 10;
	z /= 10;
}

///////////////////////////////////////////////////////////////////////////////
// HMC6343 interaction


//=====================================================================
bool HMC6343::ReadCompass(byte register, int& v0, int& v1, int& v2 ) {
	byte high, low;

	// Start the communication with the I2C device
	Wire.beginTransmission(HMC6343_ADDRESS);

	// Send the address of the registers we want to read
	Wire.write(register);
	Wire.endTransmission();
	Wire.requestFrom(HMC6343_ADDRESS, 6);

	unsigned long endTime = millis() + TimeOut;

	 // Wait for the data
	while(Wire.available() < 1 && millis() <= endTime) {
	}
        
        // Check to see if we timeout
        if(Wire.available() < 1 ) {
            return false;
        }

	// Read the data
	v0 = ReadValue();
	v1 = ReadValue();
	v2 = ReadValue();

	return true;
}

//=====================================================================
int HMC6343::ReadValue() {
	byte high, low;

	 high = Wire.read();
	low = Wire.read();

	return CombineByte(high, low);
}

/*=================================================================
 * Combines a high and low byte together, to form a single number.
 * @param v0			The first byte for a value returned by the HMC.
 * @param v0			The second byte for a value returnd by the HMC.
 */
int HMC6343::CombineByte(byte high, byte low) {
	return ((high << 8)+ low);
}
