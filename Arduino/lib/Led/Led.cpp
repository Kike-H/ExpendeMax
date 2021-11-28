#include <Arduino.h>
#include <Led.h>

Led::Led(byte pin) {
	this->_pin = pin;
	pinMode(_pin, OUTPUT);
}

void Led::turnOn() {
	digitalWrite(this->_pin, HIGH);
}

void Led::turnOff() {
	digitalWrite(this->_pin, LOW);
}


