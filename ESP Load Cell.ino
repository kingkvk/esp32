
/*
    name  of  the  Project   ---    Digital JB
   each junction box contains 10 adc connected with load cell
   10 adc are controlled by a micro controller


*/
#include "HX711.h"

void adc_read1();
unsigned long count1 = 0;
HX711 scale_1(5, 4); // data,clk

void setup()
{

  Serial.begin(9600);

}

char sbuffer1[6] = {0};

void loop()
{

  adc_read1();
 
}

void adc_read1()
{
  count1  = scale_1.read1() >> 10;
  delay(100);
  sprintf(sbuffer1, "%06ld", count1);
  Serial.write('[');
  Serial.write(sbuffer1);
  Serial.write(']');
  Serial.write(0x0d);
  Serial.write(0x0a);
}
