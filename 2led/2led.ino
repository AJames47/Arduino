int b1=0;
int b2=1;
int led1=2;
int led2=3;
int  bu1=0;
int bu2=0;

void setup()
{
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
 
}

void loop()
{
  bu1=digitalRead(b1);
  bu2=digitalRead(b2);
  if(b1==HIGH)
  {digitalWrite(led1,HIGH);
   digitalWrite(led2,LOW);
  }
  
  if(b2==HIGH)
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
  }
  if(b1==HIGH&&b2==HIGH)
  {
     digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
  }
  if(b1==LOW&&b2==LOW)
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
  }
}
