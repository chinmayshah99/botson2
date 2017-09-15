// HC-SC04 Ultrasonic Module

int duration,distance;
void setup() 
{
pinMode(6,OUTPUT);  //Ultrasonic Trigger
pinMode(7,INPUT);   //Ultrasonic Echo
}

void loop() 
{
digitalWrite(6, HIGH);                      //Trigger pin is ON (Ultasonic sensor transmits sound waves)
delay(10);                                  //Trigger is high for 10 ms
digitalWrite(6, LOW);                      // Trigger pin is OFF (Ultrasonic sensor stops sending sound waves)
// for calculation of total time taken
duration = pulseIn(7, HIGH);               // Reads the signal recievd at the Echo pin
delay(50);                                 //Delay added for stability
return ((duration/2) / 74);              // Calculates distance in inches and sends it to function call (** for centimeters (cm) divide by 58 **)
}
