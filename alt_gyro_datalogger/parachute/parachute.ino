#include <Adafruit_BMP280.h>
#include <i2c.h>
#include <Wire.h>


int pinCS = 10;
int pyro3 = 3;
int pyro4 = 4;

float AltF;
long Altitude;
long apogee = 0;
long PreveriousAltitude = 0;

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

  AltF = bmp.readAltitude(1013.25);
  AltF = AltF*100;
  Serial.print(AltF);
  Serial.print("\t");
  Altitude = AltF;
  Serial.println(Altitude);
  delay(500);
  if(PreveriousAltitude > Altitude)
  {
    apogee = PreveriousAltitude;
    Serial.print("apogee: ");
    Serial.println( apogee);
  }
  PreveriousAltitude = Altitude;
  if(apogee != 0.0)
  {
    if(Altitude<=89960)
    {
      digitalWrite(pyro3,HIGH);
      Serial.println("pyro3 and 4 active");
      digitalWrite(pyro4,HIGH);
      delay(200);
      digitalWrite(pyro3,LOW);
      digitalWrite(pyro4,LOW);
      apogee = 0;
    }
  }



}
