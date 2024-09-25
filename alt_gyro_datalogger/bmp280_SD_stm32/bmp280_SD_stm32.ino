//#include <SPI.h>
#include <SD.h>
//#include <i2c.h>
#include <Adafruit_BMP280.h>

File myFile;
//Adafruit_BMP280 bmp;

int PA15  = 4;


#define BMP_CS   10

//Adafruit_BMP280 bmp; // I2C
Adafruit_BMP280 bmp(BMP_CS);

void setup() {
//  pinMode(PC13,OUTPUT);
  
   Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  


  //Serial.print("Initializing SD card...");

  if (!SD.begin(PA15)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");



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

  Serial.print(F("Temperature = "));
    Serial.println(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.println(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.println(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println("     ");
    

  
  myFile = SD.open("spet.txt", FILE_WRITE);  
  if (myFile) {
    myFile.print(bmp.readTemperature());
    Serial.println("11111111111  ");
    myFile.print("\t");
    myFile.print(bmp.readPressure());
    Serial.println("2222222222222     ");
    myFile.print("\t");
    myFile.println(bmp.readAltitude(1013.25));
    Serial.println("33333333333333     ");delay(200);
    myFile.close();
   // digitalWrite(PC13,LOW);
    Serial.println("done.");
  } else {
    //if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}
