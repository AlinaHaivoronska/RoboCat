#include <SoftwareSerial.h>
SoftwareSerial nodemcu(2,3);
 
long int data; 
int firstVal, secondVal,thirdVal;
 
 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors
String cdata; // complete data
 
// for L298N motor driver
int ena = 5; 
int enb = 6; 
 
int in1 = 8; 
int in2 = 9; 
int in3 = 10; 
int in4 = 11;
 
 
void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600);
 
 pinMode(ena, OUTPUT); 
  pinMode(enb, OUTPUT); 
 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
 analogWrite(ena, 255); 
 analogWrite(enb, 255);
 
}
 
void loop()
{
  
if(nodemcu.available() == 0 )
{
 Serial.println("not available");
   delay(100); // 100 milli seconds
 
}
 
if ( nodemcu.available() > 0 ) 
{
  Serial.println(" available");
  thirdVal = map(thirdVal, 0, 1023, 0 , 255); 
analogWrite(ena, thirdVal); 
analogWrite(enb, thirdVal); 
 
      rdata = nodemcu.read(); 
    myString = myString+ rdata; 
    //Serial.print(rdata);
    if( rdata == '\n')
    {
Serial.println(myString);
// new code
String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2); 
 
 
firstVal = l.toInt(); // for left and right
secondVal = m.toInt(); // forward and reverse
//thirdVal = n.toInt(); // speed
  myString = "";
 
 
            if ( (firstVal == 2) && (secondVal == 2) ) // for joystic normal position
            {
               // analogWrite(ena,0);
               // analogWrite(enb,0);
                digitalWrite(in1,LOW);
                digitalWrite(in2,LOW); 
                digitalWrite(in3,LOW); 
                digitalWrite(in3,LOW);
                
            } else
            
            if ( (firstVal == 2) && (secondVal > 3) ) // Forward direction
            {
               // analogWrite(ena,thirdVal);
               // analogWrite(enb,thirdVal);
                  digitalWrite(in1,HIGH);
                  digitalWrite(in2, LOW); 
                  digitalWrite(in3,LOW); 
                  digitalWrite(in4,HIGH); 
            }else
 
            if ( (firstVal == 2) && (secondVal < 1) ) // reverse direction
            {
              //  analogWrite(ena,thirdVal);
              //  analogWrite(enb,thirdVal);
                digitalWrite(in1,LOW);
                digitalWrite(in2, HIGH); 
                digitalWrite(in3,HIGH); 
                digitalWrite(in4,LOW); 
            }else
 
           if ( (firstVal > 3) && (secondVal == 2) ) // Right
            {
              //  analogWrite(ena,thirdVal);
              //  analogWrite(enb,thirdVal);
                digitalWrite(in1,HIGH);
                digitalWrite(in2, LOW); 
                digitalWrite(in3,LOW); 
                digitalWrite(in4,LOW); 
            } else
 
            
           if ( (firstVal < 1) && (secondVal == 2) ) // left
            {
              //  analogWrite(ena,thirdVal);
              //  analogWrite(enb,thirdVal);
                digitalWrite(in1,LOW);
                digitalWrite(in2, LOW); 
                digitalWrite(in3,LOW); 
                digitalWrite(in4,HIGH); 
            }
    }
  
}
 
}
 
 
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
