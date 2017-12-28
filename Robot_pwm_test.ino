#include "IRLremote.h"

#define dirGauche 8
#define pwmGauche 9

#define dirDroite 12
#define pwmDroite 11

#define pinIR 2

CNec IRLremote;           // 0422, 0478, 0493
//CPanasonic IRLremote;     // 1052
//CHashIR IRLremote;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");

  if (!IRLremote.begin(pinIR))
  Serial.println(F("You did not choose a valid pin."));
  
  pinMode(dirGauche, OUTPUT);
  pinMode(pwmGauche, OUTPUT);
  pinMode(dirDroite, OUTPUT);
  pinMode(pwmDroite, OUTPUT);
}

void loop()
{ 
  if (IRLremote.available())
  {
    // Get the new data from the remote
    auto data = IRLremote.read();

    // Print the protocol data
    Serial.print(F("Address: 0x"));
    Serial.println(data.address); //, HEX);
    Serial.print(F("Command: 0x"));
    Serial.println(data.command); //, HEX);
    Serial.println();
    
    if(data.command == 27)          //ch+
    {
      forward();
    }
    else if(data.command == 31)     //ch-
    {
      backward();
    }
    else if(data.command == 28)     //vol-
    {
      left();
    }
    else if(data.command == 24)     //vol+
    {
      right();
    }
    else if(data.command == 8)     //1
    {
      backward_left();
    }
    else if(data.command == 10)     //2
    {
      backward_right();
    }
    else if(data.command == 30)     //M
    {
      halt();
    }
  }
}

void  forward()
{
  // both forward
  digitalWrite(dirGauche, LOW);    //INPUT 1 LOW 
  analogWrite(pwmGauche, 210);     //INPUT 2 PWM
  
  digitalWrite(dirDroite, LOW);    //INPUT 3 LOW
  analogWrite(pwmDroite, 250);     //INPUT 4 PWM
}

void  backward()
{
  // left halt + right !PWM
  digitalWrite(dirGauche, HIGH);   //INPUT 1 HIGH 
  analogWrite(pwmGauche, 40);       //INPUT 2 !PWM
  
  digitalWrite(dirDroite, HIGH);   //INPUT 1 HIGH
  analogWrite(pwmDroite, 0);       //INPUT 2 !PWM
}

void  backward_left()
{
  // left halt + right !PWM
  digitalWrite(dirGauche, LOW);   //INPUT 1 LOW 
  analogWrite(pwmGauche, 0);      //INPUT 2 LOW
  
  digitalWrite(dirDroite, HIGH);  //INPUT 1 HIGH
  analogWrite(pwmDroite, 0);      //INPUT 2 !PWM
}

void  backward_right()
{
  // left !PWM + right halt
  digitalWrite(dirGauche, HIGH);  //INPUT 1 !PWM
  analogWrite(pwmGauche, 0);      //INPUT 2 LOW
  
  digitalWrite(dirDroite, LOW);   //INPUT 1 LOW
  analogWrite(pwmDroite, 0);      //INPUT 1 LOW
}

void left()
{
  
  digitalWrite(dirGauche, LOW);
  analogWrite(pwmGauche, 0);
  
  digitalWrite(dirDroite, LOW);
  analogWrite(pwmDroite, 255);
}

void right()
{
  digitalWrite(dirGauche, LOW);
  analogWrite(pwmGauche, 250);
  
  digitalWrite(dirDroite, LOW);
  analogWrite(pwmDroite, 0);
}

void halt()
{
  digitalWrite(dirGauche, LOW);
  analogWrite(pwmGauche, 0);
  digitalWrite(dirDroite, LOW);
  analogWrite(pwmDroite, 0);
}
