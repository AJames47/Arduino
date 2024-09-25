int trigPin=8;
int echoPin = 11;

int ledr = 3;
int ledg = 5;
int ledb = 6;

long duration;
int distance;

int r[] = {255,255,255,255,255,255,204,153,102,51,0};
int g[] = {0,51,102,153,204,255,255,255,255,255,255};


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin,LOW);
  delay(2);

  digitalWrite(trigPin,HIGH);
  delay(10);
  digitalWrite(trigPin,LOW);


  duration = pulseIn(echoPin,HIGH);
  distance = duration*0.034/2;
  Serial.println(distance);

  if (distance>=4 && distance<=30)
  {
    int i = map(distance,4,30,0,10);
    analogWrite(ledr,(255-r[i]));
    analogWrite(ledg,(255-g[i]));
    analogWrite(ledb,255);
  }

  else
  {
    analogWrite(ledr,255);
    analogWrite(ledg,(255-239));
    analogWrite(ledb,0);
  }
  

}
