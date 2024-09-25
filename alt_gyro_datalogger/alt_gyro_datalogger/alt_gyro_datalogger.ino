#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <i2c.h>
#include "i2c_BMP280.h"


BMP280 bmp280;
MPU6050 mpu6050(Wire);


//rgb
const int ledr = 3;
const int ledg = 5;
const int ledb = 6;

long timer = 0;

const int chipselect = 4;

//pyrochannel 1 and 2(uncomment the following code when in use)
/*
const int pyro1 = 2;
const int pyro2 = 4;
const int buzz = 9;
*/

//pyro channel 3 and 4 for paracute
const int pyro3 = 7;
const int pyro4 = 8;

//bluetooth(uncomment the following code when in use)
//int state = 0;


void setup() 
{
  //rgb pin out
  pinMode(ledr,OUTPUT);
  pinMode(ledg,OUTPUT);
  pinMode(ledb,OUTPUT);


   //bluetooth(uncomment the following code when in use)
  //Serial.begin(38400);


  //pyrochannel 1 and 2 pin out (uncomment the following code when in use)
  /*pinMode(pyro1,OUTPUT);
  digitalWrite(pyro1,LOW);
  pinMode(pyro2,OUTPUT);
  digitalWrite(pyro2,LOW);
  pinMode(buzz,OUTPUT);
  */

  //pyrochannel 3 and 4 pin out
  pinMode(pyro3,OUTPUT);
  digitalWrite(pyro3,LOW);
  pinMode(pyro4,OUTPUT);
  digitalWrite(pyro4,LOW);
  

  //sd card
  if(!SD.begin(chipselect))
  {
    ledstatus(6,252,104,404);
  }
  else
  ledstatus(204,255,61,100);

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  dataFile.println("Time \t temperature C \t altitude m \t pressure Pa \t temperature C \t Accleration-X \t Accleration-Y \t Accleration-Z \t Gyro-X \t Gyro-Y \t Gyro-Z \t Accleration_angel-X \t Accleration_angel-Y \t Accleration_angel-Z \t Gyro_angel-X \t Gyro_angel-Y \t Gyro_angel-Z \t Angel-X \t Angel-Y \t Angel-Z ");
  dataFile.close();
  
  //pressure and altitude
  if (bmp280.initialize())
  {
    ledstatus(10,237,245,100);
  }
  else
  ledstatus(9,147,228,404);
   bmp280.setEnabled(0);
   bmp280.triggerMeasurement();
  
  
  
  //MPU6050
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);



  //bluetooth (uncomment the following code when in use)
    /*
     int lau =0;
     while(lau == '0'){
     if(Serial.available()>0)
    {
      state = Serial.read();
    }

    if(state == "1001")
    {
      digitalWrite(pyro1,HIGH);
      digitalWrite(buzz,HIGH);
      Serial.println("PYRO1 active");
      delay(500)
      digitalWrite(pyro1,LOW);
      digitalWrite(buzz,LOW);
      Serial.println("PYRO1 deactive");
      state = 0;
      lau = 1;
    }
    if(state == "2002")
    {
      digitalWrite(pyro1,HIGH);
      digitalWrite(buzz,HIGH);
      Serial.println("PYRO2 active");
      delay(500)
      digitalWrite(pyro2,LOW);
      digitalWrite(buzz,LOW);
      Serial.println("PYRO2 deactive");
      state = 0;
      lau = 1;
    }}
    */


   //serial monitor
   Serial.begin(9600);


  
}

void loop() 
{
    //rgb go-fly
    digitalWrite(ledr,78);
    digitalWrite(ledg,255);
    digitalWrite(ledb,250);
  
    
    //pressure and altitude
    String patdata ="";
    bmp280.awaitMeasurement();
    float temperature;
    bmp280.getTemperature(temperature);
    String t = String(temperature);
    float pascal;
    bmp280.getPressure(pascal);
    String pas = String(pascal);
    static float meters, metersold;
    bmp280.getAltitude(meters);
    String met = String(meters);
    bmp280.triggerMeasurement();
    patdata = String(t+"\t"+pas+"\t"+met);
   
   
    //paracute 
    float para=0.0;
    int skip =0;
    while(skip == '0'){
    if((meters <= 35.0)&&(meters<=para)){
      skip += 1;
      digitalWrite(pyro3,HIGH);
      delay(500);
      digitalWrite(pyro3,LOW);
      delay(100);
      digitalWrite(pyro4,HIGH);
      delay(500);
      digitalWrite(pyro4,LOW);
    }
     para = meters;
    }


    //MPU6050
    mpu6050.update();
    String mpudata = "";
    if(millis() - timer > 1000)
    {
      float temp=mpu6050.getTemp();
      String te = String(temp);
      
      float accx = mpu6050.getAccX();
      String ax = String(accx);
      float accy = mpu6050.getAccY();
      String ay = String(accy);
     

      float gyrox = mpu6050.getGyroX();
      String gx = String(gyrox);
      float gyroy = mpu6050.getGyroY();
      String gy = String(gyroy);
      float gyroz = mpu6050.getGyroZ();
      String gz = String(gyroz);

      float accanx = mpu6050.getAccAngleX();
      String aax = String(accanx);
      float accany = mpu6050.getAccAngleY();
      String aay = String(accanx);
    

      float gyroanx = mpu6050.getGyroAngleX();
      String gax = String(gyroanx);
      float gyroany = mpu6050.getGyroAngleY();
      String gay = String(gyroany);
      float gyroanz = mpu6050.getGyroAngleZ();
      String gaz = String(gyroanz);

      float angx = mpu6050.getAngleX();
      String anx = String(angx);
      float angy = mpu6050.getAngleY();
      String any = String(angy);
      float angz = mpu6050.getAngleZ();
      String anz = String(angz);
      timer = millis();
    
      mpudata = String(te+"\t"+ax+"\t"+ay+"\t"+gx+"\t"+gy+"\t"+gz+"\t"+aax+"\t"+aay+"\t"+gax+"\t"+gay+"\t"+gaz+"\t"+anx+"\t"+any+"\t"+anz);
      
    }
    

     
    //data to SD card
    String tim = String(millis()/1000);
    String finaldata = tim+"\t"+ patdata +"\t"+ mpudata;
     File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if(dataFile)
  {
    dataFile.println(finaldata);
    dataFile.close();
   }
  else
  ledstatus(6,252,104,404);

  
  //serial moniter
  if (Serial.available()) {     
    Serial.write(String(finaldata));   
  }
  else
  ledstatus(255,0,247,404);



}  











void ledstatus(int val1, int val2, int val3, int mes)
{ int n = 5;
  if(mes == 404){
    while(n!=0){
    digitalWrite(ledr,val1);
    digitalWrite(ledg,val2);
    digitalWrite(ledb,val3);
    delay(500);
    digitalWrite(ledr,0);
    digitalWrite(ledg,0);
    digitalWrite(ledb,0);
    delay(500)
    n--;
  }}
  if(mes == 100)
  {
   
    digitalWrite(ledr,val1);
    digitalWrite(ledg,val2);
    digitalWrite(ledb,val3);
    delay(5000);
    digitalWrite(ledr,102);
    digitalWrite(ledg,255);
    digitalWrite(ledb,255);
  
}
}
