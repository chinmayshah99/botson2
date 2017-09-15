#include <Servo.h>
char button,voice,sequence[20];
String laserstatus,requiredlaserstatus,recordstatus,requiredrecordstatus,fullvoice,voicecommand;
int duration,distance,servoangle,ldr;
int far[20],bar[20],sar[20],rar[20],lar[20],fr,br,sr,rr,lr,i,j,v,c;
Servo myservo;           // create servo object to control a servo


void setup() 
{
 Serial.begin(9600);
 myservo.attach(9);   //Servo control
 pinMode(2,OUTPUT);  //Motor driver pin 1
 pinMode(3,OUTPUT);  //Motor driver pin 2
 pinMode(4,OUTPUT);  //Motor driver pin 3
 pinMode(5,OUTPUT);  //Motor driver pin 4
 pinMode(6,OUTPUT);  //Ultrasonic Trigger
 pinMode(7,INPUT);   //Ultrasonic Echo
 pinMode(8,OUTPUT);  //Laser 
 pinMode(10,OUTPUT); //LED
 pinMode(A0, INPUT); //LDR
 laserstatus="OFF";
 servoangle=90;
 myservo.write(servoangle);
 recordstatus="NotRecording";
 requiredrecordstatus="StopRecording";
 fr=0;
 br=0;
 sr=0;
 rr=0;
 lr=0;
 i=0;
 for(int c=0;c<20;c++)
 {
     sequence[i]='p';
     far[c]=0;
     bar[c]=0;
     sar[c]=0;
     lar[c]=0;
     rar[c]=0;
 }
}


void loop() 
{ 
  /*ldr= analogRead(A0);
  if(ldr==0)                          //Condition for bot to stop when hit by a laser
  {
    stop();
    repeat:
    digitalWrite(10,HIGH);
    delay(1000);
    digitalWrite(10,LOW);
    delay(1000);
    goto repeat;
  }*/
  exitvoice:
  while (Serial.available())
    {
      delay(10);
      button = Serial.read();
      Serial.print("New data available :");
      Serial.println(button);
      if(button=='o')
      {
        if(laserstatus=="OFF")
        {
          requiredlaserstatus="ON";
        }
        else
        {
          requiredlaserstatus="OFF";
        }
      }
      if(requiredrecordstatus=="StartRecording")
      {
        sequence[i]=button;
        far[i]=fr;
        fr=0;
        bar[i]=br;
        br=0;
        sar[i]=sr;
        sr=0;
        rar[i]=rr;
        rr=0;
        lar[i]=lr;
        lr=0;
        i=i+1;
      }
    }
   switch(button)
   {
    case'f':                   //Forward
     forward();
    break;
    
    case'b':                   //Backward
     backward();
    break;
    
    case'l':                   //Left
     left();
    break;
    
    case'r':                   //Right
     right();
    break;
    
    case's':                   //Stop
      stop();
    break;
    
    case'o':                   //Laser
      laser();
    break;
    
    case'e':                   //Servo left 
      servoleft();
    break;
    
    case'g':                   //Servo right
      servoright();
    break;
    
    case't':                   //Hold servo position
      servostop();
    break;
    
    case'a':                   //Obstacle avoiding mode
      distance=ultrasonic();
      if(distance>=10)
      {
        forward();
      }
      else
      {
        left();
      }
    break;
    // turns on the mic
    case'*':                                                  //Voice commands
      Serial.println("MIC ON ");
      loop:
      delay(500);
      while (Serial.available())
      {
         voice = Serial.read();
         if(voice=='*')
         {
           button='s';
           goto exitvoice;
         }
         if(voice=='#')
         {
           voicecommand=fullvoice;
           fullvoice="";
           Serial.print("Voice command : ");
           Serial.println(voicecommand);
           goto aud;
         }
         fullvoice=fullvoice+voice;
      }
      aud:
      if(voicecommand=="stop" || voicecommand=="wait")
      {
        stop();
      }
      else if(voicecommand=="forward" || voicecommand=="straight" || voicecommand=="go")
      {
        forward();
      }
      else if(voicecommand=="backward" || voicecommand=="back" || voicecommand=="reverse")
      {
        backward();
      }
      else if(voicecommand=="left")
      {
        left();
      }
      else if(voicecommand=="right")
      {
        right();
      }
      goto loop;
      break;
    
    case 'z':                                                   //Record bot motion
      if(recordstatus=="NotRecording")
      {
        requiredrecordstatus="StartRecording";
        recordstatus="Recording";
        Serial.println("Started Recording");
      }
      else
      {
        requiredrecordstatus="StopRecording";
        recordstatus="NotRecording";
        Serial.println("Stopped recording");
      }
      button='s';
    break;
    
    case 'p':                                                    //Play recorded motion
      for(int j=0;j<20;j++)
      { 
        digitalWrite(29,HIGH);
        switch (sequence[j])
        {
          case 'f':
          while (far[j+1]!=0)
          {
            forward();
            far[j+1]=far[j+1]-1;
          }
          break;
          case 'b':
          while (bar[j+1]!=0)
          {
            backward();
            bar[j+1]=bar[j+1]-1;
          }
          break;
          case 's':
          while (sar[j+1]!=0)
          {
            stop();
            sar[j+1]=sar[j+1]-1;
          }
          break;
          case 'r':
          while (rar[j+1]!=0)
          {
            right();
            rar[j+1]=rar[j+1]-1;
          }
          break;
          case 'l':
          while (lar[j+1]!=0)
          {
            left();
            lar[j+1]=lar[j+1]-1;
          }
          break;
          default :
          Serial.println("Done playing");
          button='s';
          break;
        }
      }
      button='s';
    break;
    
    default:
      Serial.println("Wrong choice");
    break;
   } // End of switch
    
}//End of loop


void forward()
{ delay(500);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  Serial.println("FORWARD");
  delay(100);
  if(recordstatus=="Recording")
    {
      fr=fr+1;
    } 
}

void backward()
{delay(500);
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  Serial.println("BACK");
  delay(100);
  if(recordstatus=="Recording")
    {
      br=br+1;
    }
}

void left()
{delay(500);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  Serial.println("LEFT");
  delay(100);
  if(recordstatus=="Recording")
    {
      lr=lr+1;
    }
}

void right()
{delay(500);
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  Serial.println("RIGHT");
  delay(100);
  if(recordstatus=="Recording")
    {
      rr=rr+1;
    }
}

void stop()
{delay(500);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  Serial.println("STOP");
  delay(100);
  if(recordstatus=="Recording")
    {
      sr=sr+1;
    }
}

void laser()
{delay(500);
  if(requiredlaserstatus=="ON")
  {
    digitalWrite(8,HIGH);
    Serial.println("Laser ON");
    laserstatus="ON";
    delay(50);
  }
  else 
  {
    digitalWrite(8,LOW);
    Serial.println("Laser OFF");
    laserstatus="OFF";
    delay(50);
  }
}

void servoleft()
{delay(500);
  if(servoangle !=0)
  {
    servoangle=servoangle-10;
    myservo.write(servoangle);
    Serial.print("Servo angle: ");
    Serial.println(servoangle);
    delay(100);
  }
}

void servoright()
{delay(500);
   if(servoangle !=180)
  {
    servoangle=servoangle+10;
    myservo.write(servoangle);
    Serial.print("Servo angle: ");
    Serial.println(servoangle);
    delay(100);
  }
}

void servostop()
{delay(500);
  myservo.write(servoangle);
  Serial.print("Servo angle: ");
  Serial.println(servoangle);
  delay(100);
}

int ultrasonic()
{delay(500);
  digitalWrite(6, HIGH);                      //Trigger pin is ON (Ultasonic sensor transmits sound waves)
  delay(10);                                  //Trigger is high for 10 ms
  digitalWrite(6, LOW);                      // Trigger pin is OFF (Ultrasonic sensor stops sending sound waves)
  duration = pulseIn(7, HIGH);               // Reads the signal recievd at the Echo pin
  delay(50);                                 //Delay added for stability
  return ((duration/2) / 74);              // Calculates distance in inches and sends it to function call (** for centimeters (cm) divide by 58 **)
}

