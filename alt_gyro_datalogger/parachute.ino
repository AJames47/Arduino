#include <Adafruit_BMP280.h>
#include <i2c.h>
#include <Wire.h>


int pinCS = 10;
int pyro3 = 3;
int pyro4 = 4;

float altitude;
float apogee = 0.0;
float PreveriousAltitude = 0.0;

Adafruit_BMP280 bmp;


void setup()
{

  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);

  // SD Card Initialization


  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

}



void loop()
{

  altitude = bmp.readAltitude(1013.25);
  Serial.println("Altitude: " + altitude);
  delay(500);
  if(PreveriousAltitude > altitude)
  {
    apogee = PreveriousAltitude;
    Serial.println("apogee: " +apogee);
  }
  if(apogee != 0.0)
  {
    if(altitude<=890.0)
    {
      digitalWrite(pyro3,HIGH);
      digitalWrite(pyro4,HIGH);
      delay(200);
      digitalWrite(pyro3,LOW);
      digitalWrite(pyro4,LOW);
    }
  }



}
