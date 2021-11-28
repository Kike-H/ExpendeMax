#include <Arduino.h>
#include "protothreads.h"
#include "Machine.h"


void Machine::inizialice(Led red, Led green, Servo servo, Joystick joy, Adafruit_SSD1306 oled) {
	this->_red = red;
	this->_green = green;
	this->_servo = servo;
	this->_joy = joy;
	this->_oled = oled;
	this->_servo.write(0);
	this->_point = 0;
	this->_actual_balance = 0;
	this->_message = "I: coin & code";
	this->_oled.setTextWrap(false);
	this->_x = this->_oled.width();
	this->_minX = -12 * this->_message.length();
}

void Machine::_printMessage() {
	this->_oled.clearDisplay();
	this->_oled.setTextColor(WHITE);
	this->_oled.setTextSize(2);

	this->_oled.setCursor(0, 30);
	this->_oled.print("$:");
	this->_oled.print(this -> _actual_balance);

	this->_oled.setCursor(0, 50);
	this->_oled.print("$:");
	this->_oled.print(this->_balance);

	this->_oled.setCursor(this->_x, 3);
	this->_oled.print(this->_message);

	this->_oled.display();
	this->_x = this->_x-1;
	if(this->_x < this->_minX)this->_x = this->_oled.width();
}

void Machine::_changeMessage(String new_message) {
	this->_message = new_message;
	this->_x = this->_oled.width();
	this->_minX = -12 * this->_message.length();
}

int Machine::changeBalance(struct pt* pt) {
	int values[] = {0,1,2,5,10,20,50,100,200};
	unsigned int timeout = 300;
	PT_BEGIN(pt);

	for(;;) {
		if(this->_joy.getX() >= 0 && this->_joy.getX() < 480) {
			this->_point = (this->_point > 0) ? this->_point-1 : 0;
			PT_SLEEP(pt, timeout);
		}
		if (this->_joy.getX() > 540 && this->_joy.getX() < 1023 ) {
			this->_point = (this->_point < 8) ? this->_point+1 : 8;
			PT_SLEEP(pt, timeout);
		}
		if(this->_joy.getS() == LOW) {
			this->_actual_balance += this->_balance;
			Serial.println(this->_actual_balance);
			this->_balance = 0;
			this->_point = 0;
			PT_SLEEP(pt,timeout);
		}
		this->_balance = values[this->_point];
		PT_YIELD(pt);
	}

	PT_END(pt);
}

int Machine::reciveData(struct pt *pt) {
	String data;
	String key;
	String info;
	int index;

	unsigned int timeout = 10000;

	PT_BEGIN(pt);

	for(;;) {
		if(Serial.available()) {
			data = Serial.readString();
			
			index = data.indexOf(":");
			key = data.substring(0,index);
			info = data.substring(index+1);

			_changeMessage(info);

			if(key == "accepted") {
				this->_green.turnOn();
				this->_actual_balance = 0;
				this->_servo.write(90);
				PT_SLEEP(pt, 600);
				this->_servo.write(0);
			}
			if(key == "rejected") {
				this->_red.turnOn();
			}
			PT_SLEEP(pt, timeout);
			_changeMessage("I: coin & code");
			this->_green.turnOff();
			this->_red.turnOff();
		}
		PT_YIELD(pt);
	}

	PT_END(pt);
}

int Machine::printOnOled(struct pt *pt) {
	PT_BEGIN(pt);

	for(;;) {
		_printMessage();
		PT_YIELD(pt);
	}

	PT_END(pt);
}
