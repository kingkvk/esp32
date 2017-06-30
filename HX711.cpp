#include <Arduino.h>
#include "HX711.h"

HX711::HX711(byte dout, byte pd_sck) {
	PD_SCK 	= pd_sck;
	DOUT 	= dout;
	
	pinMode(PD_SCK, OUTPUT);
	pinMode(DOUT, INPUT_PULLUP);

	
}

HX711::~HX711() {

}

bool HX711::is_ready() {
	return digitalRead(DOUT) == LOW;
}


	

long HX711::read1() {
	// wait for the chip to become ready
	while (!is_ready());

	byte data1[3];

	// pulse the clock pin 24 times to read the data
	for (byte j = 3; j--;) {
		for (char i = 8; i--;) {
			digitalWrite(PD_SCK, HIGH);
			bitWrite(data1[j], i, digitalRead(DOUT));
			digitalWrite(PD_SCK, LOW);
		}
	}



	data1[2] ^= 0x80;

	return ((uint32_t) data1[2] << 16) | ((uint32_t) data1[1] << 8) | (uint32_t) data1[0];
}

long HX711::read_average(byte times) {
	long sum = 0;
	for (byte i = 0; i < times; i++) {
		sum += read1();
	}
	return sum / times;
}

double HX711::get_value(byte times) {
	return read_average(times) - OFFSET;
}

float HX711::get_units(byte times) {
	return get_value(times) / SCALE;
}

void HX711::tare(byte times) {
	double sum = read_average(times);
	set_offset(sum);
}

void HX711::set_scale(float scale) {
	SCALE = scale;
}

void HX711::set_offset(long offset) {
	OFFSET = offset;
}

void HX711::power_down() {
	digitalWrite(PD_SCK, LOW);
	digitalWrite(PD_SCK, HIGH);	
}

void HX711::power_up() {
	digitalWrite(PD_SCK, LOW);	
}
