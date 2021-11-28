#include <Arduino.h>
#include "Joystick.h"

Joystick::Joystick(byte VRX, byte SW) {
	//Analog pins can't need to initialize
	this->_VRX = VRX;
	this->_SW = SW;
}

int Joystick::getX() {
	return analogRead(this->_VRX);
}

int Joystick::getS() {
	return analogRead(this->_SW);
}
