void setup() 
{
	 pinMode(A0, INPUT); //LDR

}

void  loop()
{
	ldr= analogRead(A0);
  if(ldr==0)                          //Condition for bot to stop when hit by a laser
  {
    stop();
    repeat:
    digitalWrite(10,HIGH);
    delay(1000);
    digitalWrite(10,LOW);
    delay(1000);
    goto repeat;
  }
}