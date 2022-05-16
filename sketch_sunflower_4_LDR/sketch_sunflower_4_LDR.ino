//The DIY Life
//10 October 2016
//Michael Klements
 
int eastLDRPin = 0;  //Assign analogue pins
int westLDRPin = 1;
int reverserPin = 7;	//Assign the digital pins
int motorPin = 8;
int eastLDR = 0;   //Create variables for the east and west sensor values
int westLDR = 0;
int error = 0;
int calibration = 0;  //Calibration offset to set error to zero when both sensors receive an equal amount of light
int trackerPos = 180;
 
void setup() 
{ 
  pinMode(reverserPin,OUTPUT);
  pinMode(motorPin,OUTPUT);
  digitalWrite(reverserPin,LOW);
  digitalWrite(motorPin,LOW);
} 
 
 
void loop() 
{ 
  eastLDR = calibration + analogRead(eastLDRPin);    //Read the value of each of the east and west sensors
  westLDR = analogRead(westLDRPin);
  if(eastLDR<350 && westLDR<350 && trackerPos<180)  //Check if both sensors detect very little light, night time
  {
    digitalWrite(reverserPin,LOW);
    digitalWrite(motorPin,HIGH);
    while(trackerPos<180)  //Move the tracker all the way back to face east for sunrise
    {
      trackerPos++;
      delay(1000);
    }
    digitalWrite(motorPin,LOW);
  }
  error = eastLDR - westLDR;          //Determine the difference between the two sensors.
  if(error>15&&trackerPos<180)        //If the error is positive and greater than 15 then move the tracker in the east direction
  {
    digitalWrite(reverserPin,LOW);	//Change motor direction to east
    digitalWrite(motorPin,HIGH); 	//Move the tracker to the east
    trackerPos++;
    delay(1000); 
    digitalWrite(motorPin,LOW);
  }
  else if(error<-15&&trackerPos>0)  //If the error is negative and less than -15 then move the tracker in the west direction
  {
    digitalWrite(reverserPin,HIGH);	//Change motor direction to west
    digitalWrite(motorPin,HIGH); 	//Move the tracker to the west
    trackerPos--;
   	delay(1000); 
    digitalWrite(motorPin,LOW);
  }
  delay(1000);
} 
