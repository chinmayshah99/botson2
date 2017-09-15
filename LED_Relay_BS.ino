
void setup() 
{
pinMode(10,OUTPUT); //Lights(connected to relay signal pin)
}

void loop() 
{
digitalWrite(10, HIGH);  // LED on

// you change this to any value to change the timeout
// i.e. time after which it will turn off/on
// try changing it to 30
delay(10); 
digitalWrite(10, LOW);  // LED off
delay(10);
}
