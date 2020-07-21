/* Interruptions with LCD I2C*/
/* 07/13/2020*/

// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
String multiple = "ms";
const int inputstart = 2; //digital 2 as start
const int increase = 3; //digital 3 as increase time
const int decrease = 4; //digital 4 as decrease time
const int noInterrupt = 5; //digital 5 as stop interruptions
int interruption = 1; 

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 20, 4); // Change to (0x27,16,2) for 16x2 LCD.

void setup() {
  pinMode(inputstart, INPUT);           // set pin to input
  digitalWrite(inputstart, HIGH);       // turn on pullup resistors
  pinMode(increase, INPUT);           // set pin to input
  digitalWrite(increase, HIGH);       // turn on pullup resistors
  pinMode(decrease, INPUT);           // set pin to input
  digitalWrite(decrease, HIGH);       // turn on pullup resistors
  pinMode(noInterrupt, INPUT);           // set pin to input
  digitalWrite(noInterrupt, HIGH);       // turn on pullup resistors
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
  selectTimeMultiple(0);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).  
  lcd.print("Interrupt = " + String(interruption));
  Serial.begin(9600);
  while (!Serial); // Leonardo: wait for serial monitor 
  Serial.println("Initialize");

}

void loop() {
  // Print 'Scale' on the first line of the LCD:   
  Serial.println("1");
  Serial.println(digitalRead(inputstart));
  delay(100);
  selectTimeMultiple(0);  
  if(digitalRead(inputstart) == 0){
     Serial.println("Start");
    instart(interruption,multiple);   
  }
  else if(digitalRead(increase) == 0){
    increaseTimeInterruption();
  }
  else if(digitalRead(decrease) == 0){
    decreaseTimeInterruption();
  }
  
}
void decreaseTimeInterruption(){
  if(interruption >= 1){
    interruption--;   
      
    lcd.clear();
    lcd.setCursor(0, 0); //Set the cursor on the third column and the second row (counting starts at 0!).
    lcd.print("Multiple = ms");
    lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
    lcd.print("Interrupt = " + String(interruption));
  }
}

void increaseTimeInterruption(){
  interruption++;   
  lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).  
  lcd.print("Interrupt = " + String(interruption));
}

void instart(int interruption,String multiples){
  if(multiples = "ms"){ 
    while(1){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.println("ON");
      delay(interruption);                 
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      Serial.println("OFF");
      delay(interruption);  
      if(digitalRead(noInterrupt) == 0){
        break;      
      }
    }
    if(multiples = "us"){ 
    while(1){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delayMicroseconds(interruption);                       
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delayMicroseconds(interruption);   
      if(digitalRead(noInterrupt) == 1){
        break;      
      }     
    }

  }
  
  }
}

void selectTimeMultiple(int value){
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  switch(value){
    case 1:
      lcd.print("Multiple = ms"); // Print the string "Scale = ms"
      multiple = "ms";
    case 2:
      lcd.print("Multiple = us"); // Print the string "Scale = us"
      multiple = "us";
    default:
      lcd.print("Multiple = ms"); // Print the string "Scale = ms"
  }
}
