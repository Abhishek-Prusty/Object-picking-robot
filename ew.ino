#include<Servo.h>
int arm=7;
int claw=6;
const int trigPin = 12;
const int echoPin = 13;  
const int leftForward = 2;
const int leftBackward = 3;
const int rightForward = 4;
const int rightBackward = 5;  
Servo armservo,clawservo;
int error=0;
void setup() 
{
    armservo.attach(arm);
    clawservo.attach(claw);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT); 
    Serial.begin(9600);
    pinMode(leftForward , OUTPUT);
    pinMode(leftBackward , OUTPUT);
    pinMode(rightForward , OUTPUT);
    pinMode(rightBackward , OUTPUT);   
}
void turnright()
{
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , HIGH
  );
}
void turnleft()
{
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , HIGH);
  digitalWrite(rightForward , HIGH);
  digitalWrite(rightBackward , LOW);
}
void moveforward()
{
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , HIGH);
  digitalWrite(rightBackward , LOW);
}
void stopmoving()
{
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , LOW);
}
int dist()
{
    long duration;
    int distance; 
    {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
    Serial.print("Distance: ");
    Serial.println(distance);
    delay(100);
    }
    return distance;
}
int checkheight(int initdist)
{
  int ret;
  for(int i=20;i<=50;i++)
  {
    armservo.write(i);
    delay(10);
  }
  delay(100);
  int presentdista=dist();
  int threshhold=initdist/(0.939);
  if(abs(presentdista-initdist)<15)
  {
    ret=0;
  }
  else
  {
    ret=1;
  }
  for(int i=50;i>=20;i--)
  {
    armservo.write(i);
    delay(10);
  }
  return ret;
}
/*int checkwidth(int initdist)
{
   for(int i=0;i<=20;i++)
   {
    turnleft();
    delay(15);
   }
   delay(100);
   int di1=dist();
   for(int i=20;i>=0;i--)
   {
    turnright();
    delay(20);
   }
   delay(100);
   int di2=dist();
   if(abs(initdist-di2)<=4||abs(initdist-di1)<=4)
   {
    return 0;
   }
   else
   {
    return 1;
   }
}*/
void pick()
{
  delay(100);
  armservo.write(10);
  delay(500);
  //delay(1000);
  stopmoving();
  clawservo.write(140);
  delay(100);
  for(int j=140;j<170;j++)
  {
    clawservo.write(j);
    delay(10);
  }
  for(int i=0;i<=140;i++)
  {
    if(i<40)
    {
      clawservo.write(170+i/4);
    }
    {
      armservo.write(i);
      delay(10);
    }
  }
  //delay(100);
  clawservo.write(80);
  delay(100);
  for(int i=140;i>=0;i--)
  {
    armservo.write(i);
    delay(10);
  }
}
int flag=0;
void loop() 
{
    flag=0;
    clawservo.write(140);
    armservo.write(25);
    int dista=dist();
    if(dista>40)
    {
      for(int j=0;;j++)
      {  
         delay(20);
         turnright();
         dista=dist();
        {
          if(dista<=40)
          {
            for(int l=0;l<15;l++)
            {
              turnleft();
              delay(12);
            }
            stopmoving();
            int cond=checkheight(dista);
            if(cond==1)
            {  
              clawservo.write(80);
              break;
            }
            else
            {
              for(int co=0;co<50;co++)
              {
                turnright();
                delay(50);
              }
            }
           }
        }
      }
    }
    clawservo.write(80);
    //dista=dist();
    for(int k=0;;k++)
    {
      moveforward();
      dista=dist();
      if(dista<=8&&flag==0)
      {
        flag=1;
        stopmoving();
        if(checkheight(dista)==0)
        {
          for(int j=0;j<50;j++)
          {
            turnright();
            delay(50);
          }
          break;
        }
      }
      if(dista<=4)
      {
        for(int i=0;i<4;i++)
        {
          moveforward();
          delay(10);
        }
        stopmoving();
        if(checkheight(dista)==1)
        {
          pick();
        }
        else{
          for(int co=0;co<50;co++)
          {
            turnright();
            delay(50);
          }
        }
        break;
      }
    }
}
