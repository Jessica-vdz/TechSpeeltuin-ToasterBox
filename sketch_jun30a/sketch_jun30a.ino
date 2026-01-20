#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"

int ldrPin = A0; // the pin the ldr is connected on
int ldrVal; // a variable for saving and reading the value
int musiclength = 10000; // a set time limit for each song

int randomNumber; // variable for storing the random number generated
int prevRandomNumber = 0;
int ledPin = 8; // the pin where the led is connected on
SoftwareSerial mySerial(9,10); // rx & tx pins
DFRobotDFPlayerMini myDFPlayer; // this creates a new object out of the DFRobot Library

void setup(){
  
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(ledPin, OUTPUT); 
  if(!myDFPlayer.begin(mySerial)){
    Serial.println("DFPlayer niet gevonden"); // a little message for when the dfplayer isn't found 
    while (true);
  }
  myDFPlayer.volume(5); // set volume on 10
}

void loop(){
  randomizer();

  digitalWrite(ledPin, HIGH);
  ldrVal = analogRead(ldrPin); // leest de analogpin waar de ldr in staat en slaat het op in een variable

    if ((ldrVal <= 160) && ( ldrVal > 120) ) { // red color
        
        myDFPlayer.playFolder(1, randomNumber); // takes the first folder and plays the random number which is chosen in an early function
        Serial.println("red");
        Serial.println(randomNumber);
        delay(musiclength); // wait 10 seconds
        myDFPlayer.playFolder(5,1);
            
      } else if ((ldrVal <= 220) && (ldrVal > 180)) { // yellow color
        myDFPlayer.playFolder(2, randomNumber); // takes the third folder and plays the random number which is chosen in an early function
        Serial.println("yellow");
        Serial.println(randomNumber);
        delay(musiclength); // wait 10 seconds
        myDFPlayer.playFolder(5,1);
  
        
        } else if ((ldrVal <= 130) && (ldrVal > 90)) { // blue color

          myDFPlayer.playFolder(3, randomNumber); // takes the third folder and plays the random number which is chosen in an early function
        Serial.println("blue");
        Serial.println(randomNumber);
          delay(musiclength); // wait 10 seconds
          myDFPlayer.playFolder(5,1);
  
        } else if ((ldrVal <= 89) && (ldrVal > 50)) { // black color

          myDFPlayer.playFolder(4, randomNumber); // takes the third folder and plays the random number which is chosen in an early function
        Serial.println("green");
        Serial.println(randomNumber);
          delay(musiclength); // wait 10 seconds
          myDFPlayer.playFolder(5,1);
  

        } else {

          myDFPlayer.playFolder(5, 2);
          delay(2000);
          myDFPlayer.stop();

        }

  delay(1000); // wacht 1 sec
}

void randomizer(){ // function to generate a random number between 1 and 5. Thats how many files are in each folder

  if((randomNumber == prevRandomNumber) ){

    randomNumber  = random(1,5);
  }
  prevRandomNumber = randomNumber;
};