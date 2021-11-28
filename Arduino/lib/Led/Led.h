#ifndef Led_h
#define Led_h

#include <Arduino.h>

class Led{
	private:
		//Atributes 
		byte _pin; 
	public:
		//Methods
		void turnOn();
		void turnOff();
		//Constructor
		Led(byte pin);
		Led(){};
};

#endif
