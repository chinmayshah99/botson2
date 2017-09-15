char button;

// this function tells arduino which pins to take input from
// basically activates this pins for input
void setup() 
{
/*
  Both sides of the serial connection (i.e. the Arduino and your computer) need to be set to use the same speed serial connection in order to get any sort of intelligible data. 
  If there's a mismatch between what the two systems think the speed is then the data will be garbled.

  9600 bits per second is the default for the Arduino, but you could change it to other speeds: 
  refer to: https://arduino.stackexchange.com/questions/1569/what-is-serial-begin9600 for more
*/
 Serial.begin(9600); // opens serial port, sets data rate to 9600 bits/second
 pinMode(2,OUTPUT);  //Motor driver pin 1
 pinMode(3,OUTPUT);  //Motor driver pin 2
 pinMode(4,OUTPUT);  //Motor driver pin 3
 pinMode(5,OUTPUT);  //Motor driver pin 4
}


// bots moves forward
void forward()
{
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  Serial.println("FORWARD");
  delay(100);
}

// bot moves in reverse direction
void backward()
{
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  Serial.println("BACK");
  delay(100);
}

// take the left turn 
// the low and high needs to provided according to the moment
// like in which direction you want the bot to move
void left()
{
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  Serial.println("LEFT");
  delay(100);
}

// take the right turn 
void right()
{
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  Serial.println("RIGHT");
  delay(100);
}

// bot stops here
void stop()
{
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  Serial.println("STOP");
  delay(100);
}


// contininous infite loop
// similar to :
// while(true)

void loop() 
{
  while (Serial.available())       //If there's a available byte to read do the following
    {
      delay(10);                   //Delay added for stability
      button = Serial.read();      //Store the input in button
      Serial.println("New data available");
    }

    // switch case, similar to C
    switch(button)
   {
    case'f':
      forward();
      break;
    case'b':
      backward();
      break;
    case'l':
      left();
      break;
    case'r':
      right();
      break;
    case's':
      stop();
      break;
    default:
      Serial.println("Wrong choice");
      break;
   }
}
