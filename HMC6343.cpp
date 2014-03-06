
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

/*=======================================================
*/
HMC6343::HMC6343() {
	Wire.begin();
}

///////////////////////////////////////////////////////////////////////////////
// Bearing

/*=======================================================
 * Returns the heading in degress of a HMC6343 compass. 
 */
float HMC6343::GetHeading() {
	 float heading, pitch, roll;
	 ReadCompass(HMC6343_BEARING_REG, heading, pitch, roll);
	 return heading/10;
	}

/*=======================================================
 * Returns the pitch in degress of a HMC6343 compass. 
 */
float HMC6343::GetPitch() {
	 float heading, pitch, roll;
	 ReadCompass(HMC6343_BEARING_REG, heading, pitch, roll);
	 return pitch/10;
	}

/*=======================================================
 * Returns the roll in degress of a HMC6343 compass. 
 */
float HMC6343::GetRoll() {
	 float heading, pitch, roll;
	 ReadCompass(HMC6343_BEARING_REG, heading, pitch, roll);
	 return roll/10;
	}


///////////////////////////////////////////////////////////////////////////////
// Accelerometer


/*=======================================================
 * Returns the acceleration in the x axis of a HMC6343 compass. 
 */
	float HMC6343::GetXAcc() {
		float x, y, z;
		ReadCompass(HMC6343_ACCELEROMETER_REG, x, y, z);
		return x / 10;
	}

/*=======================================================
 * Returns the acceleration in the x axis of a HMC6343 compass. 
 */
	float HMC6343::GetYAcc() {
		float x, y, z;
		ReadCompass(HMC6343_ACCELEROMETER_REG, x, y, z);
		return y / 10;
	}

/*=======================================================
 * Returns the acceleration in the x axis of a HMC6343 compass. 
 */
	float HMC6343::GetZAcc() {
		float x, y, z;
		ReadCompass(HMC6343_ACCELEROMETER_REG, x, y, z);
		return z / 10;
	}


///////////////////////////////////////////////////////////////////////////////
// HMC6343 interaction


/*=======================================================
 * Returns a byte from a register in the I2C device.
 *
 * @param register 	The register on the HMC6343 we want to 
 *						access.
 * @param v0			The first value that is returned from the HMC.
 * @param v1			The second value that is returned from the HMC.
 * @param v2			The third value that is returned from the HMC.
 */
void HMC6343::ReadCompass(byte register, float& v0, float& v1, float& v2 ) {
	byte high, low;

	// Start the communication with the I2C device
		Wire.beginTransmission(HMC6343_ADDRESS);

		// Send the address of the registers we want to read
		Wire.write(HMC6343_ACCELEROMETER_REG);
		Wire.endTransmission();
		Wire.requestFrom(HMC6343_ADDRESS, 6);

	 // Wait for the data
		while(Wire.available() < 1);

		// Read the data
		v0 = ReadValue();
		v1 = ReadValue();
		v2 = ReadValue();
}

/*=======================================================
 * Reads a value from the compass, each value consists of two bytes 
 * which are combined and returned.
 */
float HMC6343::ReadValue() {
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
float HMC6343::CombineByte(byte high, byte low) {
	return ((high << 8)+ low);
}
