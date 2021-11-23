#include <Arduino.h>

//Libs 
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Servo.h>
#include "Led.h"
#include "Buzzer.h"
#include "Joystick.h"
#include "Machine.h"

//Oled display 

//Dimmensions
#define W 128
#define H 64

//Button Reset 
#define OLED_RESET 4 // can't use this pin 

//Screen 
Adafruit_SSD1306 oled(W, H, &Wire, OLED_RESET);

//Leds 
Led green(3);
Led red(2);

//Buzzer
Buzzer buzz(5);

//Joystick
Joystick joystick(A1, A2);

//Servo
Servo servo;

Machine machine;

void setup() {
	//Initialize the serial conexion 
	Serial.begin(9600);
	Wire.begin();
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	servo.attach(6, 1000, 2000);
	machine.match(red, green, buzz, servo, joystick, oled);
}

void loop() {
	machine.working();
}
