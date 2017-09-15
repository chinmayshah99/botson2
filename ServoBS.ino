#include <Servo.h>
Servo myservo;   // create servo object to control a servo
char button;
int servoangle;
void setup() 
{
  Serial.begin(9600);
  myservo.attach(9);   //Servo control
  servoangle=90; // sets default angle as 90 degrees
  myservo.write(servoangle);
}

// move 10 degree till it reaches 0 degrees
// in case it's 0 degrees, then do nothing
void servoleft()
{
  if(servoangle !=0)
  {
    servoangle=servoangle-10;
    myservo.write(servoangle);
    delay(100);
  }
}

// move 10 degree till it reaches 180degrees
// in case it's 0 degrees, then do nothing
void servoright()
{
   if(servoangle !=180)
  {
    servoangle=servoangle+10;
    myservo.write(servoangle);
    delay(100);
  }
}
void servostop()
{
  myservo.write(servoangle);
  delay(100);
}

void loop() 
{
  while (Serial.available())       //If there's a available byte to read do the following
    {
      delay(10);                   //Delay added for stability
      button = Serial.read();      //Store the input in button
      Serial.println("New data available");
    }

   switch(button)
   {
    case'e':
      servoleft();
      break;
    case'g':
      servoright();
      break;
    case't':
      servostop();
      break;
    default:
      Serial.println("Wrong choice");
      break;
   }
  

}