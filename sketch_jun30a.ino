#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "Adafruit_NeoPixel.h"
#include "SoftwareSerial.h"

#define PIN 2 // defines the digital pin the led is in
#define NUMPIXELS 5 // defines the amount of led on the strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS,PIN,NEO_RGB + NEO_KHZ800);

int colorRedLed;
int colorBlueLed;
int colorWhiteLed;

int ldrPin = A0;
int ldrVal;
int musiclength = 10000;

int randomNumber;
int ledPin = 8;
SoftwareSerial mySerial(9,10); // dit zijn de rx en tx pins
DFRobotDFPlayerMini myDFPlayer; // dut maakt een object aan uit de class van de library DFRobotDFPlayerMini


void setup(){
  
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("DFPlayer start: "); //geeft een bericht voor het opstarten van de dfplayer
  pinMode(ledPin, OUTPUT);
  if(!myDFPlayer.begin(mySerial)){
    Serial.println("DFPlayer niet gevonden"); // voor als de Dfplayer het niet doet of niet gevonden word
    while (true);
  }
  Serial.println("DFPlayer Klaar!"); // bericht voor als de dfplayer klaar is
  myDFPlayer.volume(10); //zet het volume op 20
  pixels.begin();
}

void loop(){

  randomizer();
  digitalWrite(ledPin, HIGH);
  ldrVal = analogRead(ldrPin); // leest de analogpin waar de ldr in staat en slaat het op in een variable
  Serial.println(ldrVal); // print de variable
        if ((ldrVal <= 90) && ( ldrVal > 80) ) {
            colorRed();
            
        }else if ((ldrVal <= 140) && (ldrVal >100)) {

            colorWhite();
        }else if ((ldrVal <= 80) && (ldrVal >70)) {

            colorBlue();
        }else {
          myDFPlayer.playFolder(4, 2);
          delay(2000);
          myDFPlayer.stop();
        }

  delay(1000); // wacht 1 sec
}

void randomizer(){ // function to generate a random number between 1 and 5 
    randomNumber  = random(1,5);
    Serial.println(randomNumber);
    return randomNumber;
}

void colorRed(){
  for (int i = 0; i < NUMPIXELS; i++) {
    colorRedLed = random(50,255);
    pixels.setPixelColor(i, pixels.Color(colorRedLed,20,60));
    pixels.show();
    delay(500);
  }
  myDFPlayer.playFolder(1, randomNumber);
  Serial.println(randomNumber);
  Serial.println("color red should play music");
  delay(musiclength); // wait 10 seconds
  myDFPlayer.playFolder(4,1);
}

void colorBlue(){
    for (int i = 0; i < NUMPIXELS; i++) {
    colorBlueLed = random(50,206);
    pixels.setPixelColor(i,pixels.Color(colorBlueLed,206,colorBlueLed));
    pixels.show();
    delay(500);
  }
  myDFPlayer.playFolder(2, randomNumber);
    Serial.println(randomNumber);
    Serial.println("color blue should play music");

  delay(musiclength); // wait 10 seconds
  myDFPlayer.playFolder(4, 1);
}

void colorWhite(){
    for (int i = 0; i < NUMPIXELS; i++) {
    colorWhiteLed = 0;
    pixels.setPixelColor(i,pixels.Color(colorWhiteLed,0,0));
    pixels.show();
    delay(500);
    }
  myDFPlayer.playFolder(3, randomNumber);
  Serial.println("color white should play music");
  delay(musiclength); // wait 10 seconds
  myDFPlayer.playFolder(4,1);
  
}