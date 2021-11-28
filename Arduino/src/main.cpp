#include <Arduino.h>

//Libs 
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Servo.h>
#include <protothreads.h>
#include "Led.h"
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

//Joystick
Joystick joystick(A1, A2);

//Servo
Servo servo;

// Threads 
Machine machine;
pt pThreadBalanceC;
pt pThreadRecivedData;
pt pThreadPrintData;

void setup() {
	//Initialize the serial conexion 
	Serial.begin(9600);
	Wire.begin();
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	servo.attach(6, 1000, 2000);

	//Initial Threads
	machine.inizialice(red, green, servo, joystick, oled);
	PT_INIT(&pThreadBalanceC);
	PT_INIT(&pThreadRecivedData);
	PT_INIT(&pThreadPrintData);
}

void loop() {
	PT_SCHEDULE(machine.printOnOled(&pThreadPrintData));
	PT_SCHEDULE(machine.changeBalance(&pThreadBalanceC));
	PT_SCHEDULE(machine.reciveData(&pThreadRecivedData));
}
