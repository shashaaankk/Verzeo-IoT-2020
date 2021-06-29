#include <SoftwareSerial.h>
SoftwareSerial mySerial(5,6);
String readvoice;
int k=0;

void setup()
{
//Defining pins for motor terminals
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
//setting up serial communication-serial monitor
Serial.begin(9600);
mySerial.begin(9600);
}

void loop() {
while (mySerial.available())
{
delay(10);
char input = Serial.read();
readvoice += input;
}

if(readvoice.length() > 0)
{

int stringBreak = indexOf(" ");
char distance = substring(0,stringBreak);
char direction = substring(stringBreak+1);
int distance1 = distance.toInt();
int wheelDiameter = 5;



if(direction == "forward")
{
digitalWrite(2, HIGH);
digitalWrite(3, LOW);
digitalWrite(4, HIGH);
digitalWrite(5, LOW);
k=1;
}

if(direction == "backward")
{
digitalWrite(2, LOW);
digitalWrite(3, HIGH);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
k=2;
}

if(direction == "left")
{
if (k==2)
{
digitalWrite(2, HIGH);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
delay(1000);
digitalWrite(2, LOW);
digitalWrite(3, HIGH);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
}
else
{
digitalWrite(2, HIGH);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
delay(1000);
digitalWrite(2, HIGH);
digitalWrite(3, LOW);
digitalWrite(4, HIGH);
digitalWrite(5, LOW);
}
}

if(direction == "right")
{
if (k==2)
{
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, HIGH);
digitalWrite(5, LOW);
delay(1000);
digitalWrite(2, LOW);
digitalWrite(3, HIGH);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
}
else
{
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, HIGH);
digitalWrite(5, LOW);
delay(1000);
digitalWrite(2, HIGH);
digitalWrite(3, LOW);
digitalWrite(4, HIGH);
digitalWrite(5, LOW);
}
}

if(direction == "stop")
{
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
}
}
direction="";
}
