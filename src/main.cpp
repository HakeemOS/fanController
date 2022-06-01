#include <Arduino.h>
#include <LiquidCrystal.h>
#include <string.h>
#include <Wire.h>



// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//Variables
String input = " ";
int fanSpeed = 0; 


//Pin assignments 
#define ENABLE 5
#define DIRA 3
#define DIRB 4

void countDownLCD(){
  lcd.print("                3, 2, 1, Go...");
  for( int i = 0; i < 15 ; i++){
    lcd.scrollDisplayLeft();
    delay(300);
  }
  lcd.clear();

}

void setup() {
  // put your setup code here, to run once:
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  countDownLCD(); 

}

void loop() {
  // put your main code here, to run repeatedly:

  //set fanspeed to var
  analogWrite(ENABLE, fanSpeed); 
   //direction choice 
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,LOW);
  //First row text; Doesnt change 
  lcd.setCursor(0, 0);
  lcd.print("Enter Speed(0-5):");
  //Getting ready to write on second row text
  lcd.setCursor(0,1);
  //recieve input via serial monitor 
  if(Serial.available() > 0){
    input = Serial.readString(); 
    Serial.print("input: ");
    Serial.println(input);
  }
  // Display set up
  lcd.print("Speed: ");
  lcd.setCursor(8,1);
  lcd.print(input);
  lcd.setCursor(10,1);

  // Handling serial input 
  if(input == "1"){
    fanSpeed = (425/3);
    lcd.print("(LOW)");
  }
  else if(input == "2"){
    fanSpeed = (170);
    lcd.print("(LOW)");
  }
  else if(input == "3"){
    fanSpeed = (595/3);
    lcd.print("(MED)");
  }
  else if(input == "4"){
    fanSpeed = (680/3);
    lcd.print("(HI) ");
  }
  else if(input == "5"){
    fanSpeed = (255);
    lcd.print("(HI) ");
  }
  else {
    fanSpeed = 0; 
    lcd.print("(OFF)");
  }
  // delay to insure no weird behaviour
  delay(200);
  
}