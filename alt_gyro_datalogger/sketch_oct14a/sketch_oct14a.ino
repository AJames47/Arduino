#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "i2c.h"

#include "i2c_BMP280.h"
BMP280 bmp280;


const int ledr = 3;
const int ledg = 5;
const int ledb = 6;


void setup() 
{
  pinMode(ledr,OUTPUT);
  pinMode(ledg,OUTPUT);
  pinMode(ledb,OUTPUT);
  
  
  
  
  if (bmp280.initialize())
  {
    ledstatus(10,237,245,100);
  }
  else
  ledstatus(9,147,228,404);

}

void loop() {
 

}






void ledstatus(int val1, int val2, int val3, int mes)
{ int n = 10;
  if(mes = 404){
    while(n!=0){
    digitalWrite(ledr,val1);
    digitalWrite(ledg,val2);
    digitalWrite(ledb,val3);
    delay(500);
    n--;
  }}
  if(mes = 100)
  {
   
    digitalWrite(ledr,val1);
    digitalWrite(ledg,val2);
    digitalWrite(ledb,val3);
    delay(2000);
  
}
}
