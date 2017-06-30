
/*
   HX711 ADC with ESP32
   Author:KINGKVK
   Project:Reading ADC Value 
   


*/
#include "HX711.h"

void adc_read();
unsigned long count = 0;
HX711 scale_1(5, 4); // data,clk

void setup()
{

  Serial.begin(9600);

}

char sbuffer[6] = {0};

void loop()
{

  adc_read();
 
}

void adc_read()
{
  count  = scale_1.read1() >> 10;
  delay(100);
  sprintf(sbuffer, "%06ld", count);
  Serial.write('[');
  Serial.write(sbuffer);
  Serial.write(']');
  Serial.write(0x0d);
  Serial.write(0x0a);
}
