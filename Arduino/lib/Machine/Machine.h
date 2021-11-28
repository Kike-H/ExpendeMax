#ifndef Machine_h
#define Machine_h

#include <Arduino.h>
#include <pt.h>
#include <protothreads.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include "Led.h"
#include "Joystick.h"

class Machine {
	private:
		Led _red;
		Led _green;
		Servo _servo;
		Joystick _joy;
		Adafruit_SSD1306 _oled;
		int _balance;
		int _point;
		int _actual_balance;
		int _x, _minX;
		String _message;
		void _printMessage();
		void _changeMessage(String new_message);
	public:
		Machine(){};
		void inizialice(Led red, Led green, Servo servo, Joystick joystick, Adafruit_SSD1306 oled);
		int changeBalance(struct pt* pt);
		int reciveData(struct pt* pt);
		int printOnOled(struct pt* pt);
};

#endif /* ifndef Machine_h */
