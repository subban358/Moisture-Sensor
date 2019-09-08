//#include <SoftwareSerial.h>
#include <dht.h>

dht DHT;
int flag = 0;
//SoftwareSerial BT(0, 1); //TX, RX respetively
String readdata;
int trigPin = 2;
int echoPin = 4;
long duration, cm, inches;
void setup() {
// BT.begin(9600);
 Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(12, OUTPUT); // connect to input 1 of l293d
  pinMode(9, OUTPUT); // connect to input 4 of l293d
  pinMode(11, OUTPUT); // connect to input 3 of l293d
  pinMode(10, OUTPUT); // connect to input 2 of l293d
  pinMode(A0,INPUT);
  pinMode(6, OUTPUT);
}
//-----------------------------------------------------------------------//
void loop()
{
       
         
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  DHT.read11(A0);
 float H = DHT.humidity;
 //float T = DHT.temperature;
 if(H>0){
 Serial.print(int(H));
 Serial.println("%");
 }

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  while (Serial.available()>0)
  {  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
 
  char c = Serial.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  }


   if(flag==1){
     
        digitalWrite(trigPin, LOW);//MEANS OFF NO TRANSMITTING
        delayMicroseconds(2);
         digitalWrite(trigPin, HIGH);//MEANS ON TRANSMITTING
          delayMicroseconds(4);
         digitalWrite(trigPin, LOW);//AGAIN OFF TRANSMITTING

       duration = pulseIn(echoPin, HIGH);// DURATION OF TRAVELLING THE ULTRASONIC SOUND WAVE CALCULATED BY ARDUINO WHICH IS RECEIVED BY THE ECHO PIN. HERE HIHG MEANS ECHO PIN IS ACTIVE AND RECEIVING RETURNED PULSE
// converts the time to a distance
            cm = (duration / 2) / 29.1;//DURATION INCLUDE UP AND DOWN TRAVELLING TIME THAT’S WHY DURATION IS DIVIDED BY 2 IN BOTH CASES
            inches = (duration / 2) / 74;
             delay(250);
   if (inches <= 12)//distance never be like inches=4.5
     {
       digitalWrite (12, LOW);//stop
       digitalWrite (9, LOW);
       digitalWrite (11, LOW);
       digitalWrite (10, LOW);
       delay(500);
        digitalWrite(12, LOW);//back
        digitalWrite(9, LOW);
        digitalWrite(11, HIGH);
        digitalWrite(10,HIGH);
        delay(500);
         digitalWrite (12,HIGH);//right
        digitalWrite (9,LOW);
        digitalWrite (11,LOW);
        digitalWrite (10,HIGH);
        delay(500);
         digitalWrite(12, HIGH);//fwd
        digitalWrite (9, HIGH);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
   
          delay (100);
     }
   else
   {
      digitalWrite(12, HIGH);//fwd
      digitalWrite (9, HIGH);
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
   }
   }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (readdata.length() > 0) {
    //Serial.println(readdata); // print data to serial monitor
// if data received as forward move robot forward

  if(readdata == "forward")
  {
    digitalWrite(12, HIGH);
    digitalWrite (9, HIGH);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    flag =0;
    delay(100);
  }
  // if data received as reverse move robot reverse

  else if(readdata == "backward")
  {
    digitalWrite(12, LOW);
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(10,HIGH);
    delay(100);
    flag =0;
  }
// if data received as right turn robot to right direction.
  else if (readdata == "right")
  {
    digitalWrite (12,HIGH);
    digitalWrite (9,LOW);
    digitalWrite (11,LOW);
    digitalWrite (10,HIGH);
    delay (100);
   flag =0;
  }
// if data received as left turn robot to left direction
 else if ( readdata == "left")
 {
   digitalWrite (12, LOW);
   digitalWrite (9, HIGH);
   digitalWrite (11, HIGH);
   digitalWrite (10, LOW);
   delay (100);
   flag =0;
 }
 // if data received as stop, halt the robot
else if (readdata == "stop"){
  digitalWrite (12, LOW);//stop
   digitalWrite (9, LOW);
   digitalWrite (11, LOW);
   digitalWrite (10, LOW);
   flag =0;
   
}
else if (readdata == "automatic")
 {
   
     flag =1;    
     
 }

 else{
 
 }
}

 if(H>65 && H<0){
  digitalWrite(6,HIGH);
 }

 else{
  digitalWrite(6,LOW);
 }
 //delay(1000);
readdata="";
}

 //Reset the variable

