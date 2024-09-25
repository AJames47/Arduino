#include <SPI.h>
#include <SD.h>
#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;
double baseline;

const int chipSelect = 4;
void setup()
{
  pinMode(1,OUTPUT);//led_sd
  pinMode(2,OUTPUT);//led_sen
  if(pressure.begin())
  { digitalWrite(2,HIGH);}
  else
  {digitalWrite(2,LOW);
  while(1);}
  if(!SD.begin(chipSelect))
  {digitalWrite(1,HIGH);}
  else
  {digitalWrite(1,LOW);
  while(1);}
  baseline = getPressure();
}

void loop()
{
  double a,P;
  P = getPressure();
  a = pressure.altitude(P,baseline);
  String data_a = "";
  if (a>=0.0)
  {
    data_a = String( a )+ "M" + String(P) + "mB";
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile)
    {
      dataFile.println(data_a);
      dataFile.close();
    }
    else
    {
      while(1)
      {
      digitalWrite(1,HIGH);
      delay(500);
      digitalWrite(1,LOW);
      delay(500);
      }
    }
  }
}





double getPressure()
{
  char status;
  double T,P,p0,a;

 
  status = pressure.startTemperature();
  if (status != 0)
  {
   
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0)
    {
     
      status = pressure.startPressure(3);
      if (status != 0)
      {
        
        delay(status);

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else {
      while(1)
      {
      digitalWrite(2,HIGH);
      delay(500);
      digitalWrite(2,LOW);
      delay(500);
      }
    }
      }
      else {
      while(1)
      {
      digitalWrite(2,HIGH);
      delay(1000);
      digitalWrite(2,LOW);
      delay(1000);
      }
    }
    }
    else {
      while(1)
      {
      digitalWrite(2,HIGH);
      delay(1500);
      digitalWrite(2,LOW);
      delay(1500);
      }
    }
  }
  else {
      while(1)
      {
      digitalWrite(2,HIGH);
      delay(2000);
      digitalWrite(2,LOW);
      delay(2000);
      }
    }
}
