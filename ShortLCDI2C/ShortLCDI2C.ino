/* Interruptions with LCD I2C*/
/* 07/13/2020*/

// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD


String multiple = "ms";
const int enter = 2; //digital 2 as enter
const int up = 3; //digital 3 as up 
const int down = 4; //digital 4 as down 
const int right = 5; //digital 5 as right
const int left = 6; //digital 6 as left
const int noInterrupt = 7; //digital 5 as stop interruptions
const int SecondGroupRelays = 12; //digital 5 as stop interruptions
int interruption = 1; // Time of test execution
int noCase = 1; // Number of the test case

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 20, 4); // Change to (0x27,16,2) for 16x2 LCD.

void setup() {

  // Input Digitals
  pinMode(enter, INPUT);           // set pin to input
  digitalWrite(enter, HIGH);       // turn on pullup resistors
  pinMode(up, INPUT);           // set pin to input
  digitalWrite(up, HIGH);       // turn on pullup resistors
  pinMode(down, INPUT);           // set pin to input
  digitalWrite(down, HIGH);       // turn on pullup resistors
  pinMode(noInterrupt, INPUT);           // set pin to input
  digitalWrite(noInterrupt, HIGH);       // turn on pullup resistors
  pinMode(right, INPUT);           // set pin to input
  digitalWrite(right, HIGH);       // turn on pullup resistors
  pinMode(left, INPUT);           // set pin to input
  digitalWrite(left, HIGH);       // turn on pullup resistors
  
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();

  // OUTPUT DIGITALS  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN, HIGH); 
  digitalWrite(SecondGroupRelays, OUTPUT);  
  digitalWrite(SecondGroupRelays, HIGH);    
    
  lcd.setCursor(0, 0); //Set the cursor on the third column and the second row (counting starts at 0!).  
  lcd.print("SELECT VOLTAGE");
  lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).  
  lcd.print("AC <        >DC");
  Serial.begin(9600);
  while (!Serial); // Leonardo: wait for serial monitor 
  Serial.println("Initialization complete");

}

void loop() {
  // Print 'Scale' on the first line of the LCD:   
  Serial.println("1");
  Serial.println(digitalRead(enter));
  delay(100);

  if(digitalRead(left) == 0){
     Serial.println("left button pressed");
        
     ACSelected();
    
  }  
   
  
  
}

void ACSelected(){
  while(1){
    delay(100);
    if(digitalRead(down) == 0){
      if(noCase > 1){
        noCase--;
        ACInputVoltageTestCases(noCase); 
      }
    }
    else if(digitalRead(up) == 0){
      if(noCase < 3){      
        noCase++;   
        ACInputVoltageTestCases(noCase);    
      }     
    }
    else if(digitalRead(enter) == 0){    
      executeInterruption(interruption);        
    }
       
    
  }
}

void executeInterruption(int interruptionTime){


  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(5);
  digitalWrite(SecondGroupRelays, LOW); // later
  delay(interruptionTime);
  digitalWrite(SecondGroupRelays, HIGH); // later
  delayMicroseconds(5);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                         
  
}
void downTimeInterruption(){
  if(interruption >= 1){
    interruption--;   
      
    lcd.clear();
    lcd.setCursor(0, 0); //Set the cursor on the third column and the second row (counting starts at 0!).
    lcd.print("Multiple = ms");
    lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
    lcd.print("Interrupt = " + String(interruption));
  }
}

void upTimeInterruption(){
  interruption++;   
  lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).  
  lcd.print("Interrupt = " + String(interruption));
}

void instart(int interruption,String multiples){
  if(multiples = "ms"){ 
    while(1){
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
      Serial.println("ON");
      delay(interruption);                 
      digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
      Serial.println("OFF");
      delay(interruption);  
      if(digitalRead(noInterrupt) == 0){
        break;      
      }
    }
    if(multiples = "us"){ 
    while(1){
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
      delayMicroseconds(interruption);                       
      digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
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


void ACInputVoltageTestCases(int caseValue){
 switch(caseValue){
    case 1:
      lcd.clear(); // Clear the screen
      lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
      lcd.print("SELECT TEST AC");
      lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
      lcd.print("V2: 0%  10ms"); // Print string 
      interruption = 10;  
    case 2:
      lcd.clear(); // Clear the screen
      lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
      lcd.print("SELECT TEST AC");
      lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
      lcd.print("V2: 0%  20ms"); // Print string 
      interruption = 20;  
    case 3:
      lcd.clear(); // Clear the screen
      lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
      lcd.print("SELECT TEST AC");
      lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
      lcd.print("V2: 40%  200ms"); // Print string 
      interruption = 200;
    default:
      lcd.print("Hola Mundo");
     
  }
}
