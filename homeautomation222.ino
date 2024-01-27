#include <Servo.h>
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT11;
#define DHT11_PIN 13
Servo myservo;
int temperature;
int rell = 11;
int count = 0;
char c;
String id;
int trig = 5;
int echo = 6;
int buzz = 4;
int pir = 2;
int rel = 3;
long duration;
int distance;
void setup(){
  Serial.begin(9600);
  myservo.attach(12);
  myservo.write(0);
  pinMode(12, OUTPUT);
  Serial.println("Please scan your RFID TAG");
  pinMode(DHT11_PIN, INPUT);
  pinMode(trig,INPUT);
  pinMode(echo,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(pir,INPUT);
  pinMode(rel,OUTPUT);
  pinMode(rell,OUTPUT); 
}

  void loop(){
  while(Serial.available()>0)
  {
    c = Serial.read();
   count++;
   id += c;
   if(count == 12)  
    {
      Serial.print(id);
      if(id=="AB123456789A")  
      {
        Serial.println("Valid TAG");
        digitalWrite(12, HIGH);
        myservo.write(180);
       }
      else
      {
      digitalWrite(12, LOW);
      Serial.println("Invalid TAG");
      myservo.write(0); 
      }
    }
  }
  count = 0;
  id="";
  delay(500);
  DHT11.read(DHT11_PIN);
  temperature = DHT11.temperature;
  Serial.println(temperature);
  if(temperature>30){
    digitalWrite(rell, HIGH);
  }else{
    digitalWrite(rell, LOW);
  }
     digitalWrite(trig, LOW);
     delayMicroseconds(2);
     digitalWrite(trig, HIGH);
     delayMicroseconds(10);
     digitalWrite(trig, LOW);
     duration = pulseIn(echo, HIGH);
     distance = duration * 0.034 / 2;
     if(distance>100){
      digitalWrite(buzz, HIGH);
     }else{
      digitalWrite(buzz,LOW);
     }
      Serial.print("Distance: ");
      Serial.println(distance);
      int data = digitalRead(pir);
      if(data == HIGH){
      digitalWrite(rel, HIGH);
      }else{
      digitalWrite(rel, LOW);
      }
  }
