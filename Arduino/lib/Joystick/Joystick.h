#ifndef Joystick_h
#define Joystick_h

#include <Arduino.h>

class Joystick {
	private:
		//Atributes priv
		int _X, _S;
		byte _VRX, _SW;
	public:
		//Methods pub
		int getX();
		int getS();
		//Constructor
		Joystick(byte VRX, byte SW);
		Joystick(){};
};


#endif
