
char button;
void setup() 
{
 Serial.begin(9600);
}

void loop() 
{
while (Serial.available())       //If there's a available byte to read do the following
    {
      delay(10);                   //Delay added for stability

      // serial.read reads for any byte and stores it in variable button
      button = Serial.read();      //Store the input in button
      Serial.println("New data available");
    }
}
