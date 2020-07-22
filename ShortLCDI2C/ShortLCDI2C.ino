/* Interruptions with LCD I2C*/
/* 07/13/2020*/

// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD


const int enter = 2; //digital 2 as enter
const int up = 3; //digital 3 as up 
const int down = 4; //digital 4 as down 
const int right = 5; //digital 5 as right
const int left = 6; //digital 6 as left
const int esc = 7; //digital 7 as stop interruptions
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
  pinMode(esc, INPUT);           // set pin to input
  digitalWrite(esc, HIGH);       // turn on pullup resistors
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
  delay(100);

  if(digitalRead(left) == 0){
     Serial.println("left button pressed");        
     ACMenu(); // Calls the function to move on the menu. 
  }   
}

void ACMenu(){
  ACInputVoltageTestCases(noCase); // Updates the lcd and change the TimeInterruption 
  while(1){
    delay(300);
    if(digitalRead(down) == 0){
      if(noCase > 1){
        noCase--;
        Serial.println("noCase " + String(noCase)); 
        ACInputVoltageTestCases(noCase); // Updates the lcd and change the TimeInterruption
      }
    }
    else if(digitalRead(up) == 0){
      if(noCase < 6){      
        noCase++; 
        Serial.println("noCase " + String(noCase));   
        ACInputVoltageTestCases(noCase); // Updates the lcd and change the TimeInterruption  
      }     
    }
    else if(digitalRead(enter) == 0){    
      executeInterruption(interruption); // Execute the Interruption 
      Serial.println("noCase " + String(noCase)); 
      ACInputVoltageTestCases(noCase); // Updates the lcd and change the TimeInterruption       
    }
       
    
  }
}

void executeInterruption(int interruptionTime){

  Serial.println("Check miliseconds selected " + String(interruptionTime));      
  coundown();
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(5);
  digitalWrite(SecondGroupRelays, LOW); // later
  delay(interruptionTime);
  digitalWrite(SecondGroupRelays, HIGH); // later
  delayMicroseconds(5);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  ACInputVoltageTestCases(noCase); // Updates the lcd and change the TimeInterruption
                         
  
}
void coundown(){
  lcd.clear();
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("TEST IN PROGRESS");
  lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
  lcd.print("     5");  
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("TEST IN PROGRESS");
  lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
  lcd.print("     4");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("TEST IN PROGRESS");
  lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
  lcd.print("     3");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("TEST IN PROGRESS");
  lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
  lcd.print("     2");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("TEST IN PROGRESS");
  lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
  lcd.print("     1");
  delay(1000);
  
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
      break;
    case 2:
      lcd.clear(); // Clear the screen
      lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
      lcd.print("SELECT TEST AC");
      lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
      lcd.print("V2: 0%  20ms"); // Print string 
      interruption = 20;  
      break;
    case 3:
      lcd.clear(); // Clear the screen
      lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
      lcd.print("SELECT TEST AC");
      lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
      lcd.print("V2: 40%  200ms"); // Print string 
      interruption = 200;
      break;
    case 4:
      lcd.clear(); // Clear the screen
      lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
      lcd.print("SELECT TEST AC");
      lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
      lcd.print("V2: 70%  500ms"); // Print string 
      interruption = 500;
      break;
    case 5:
      lcd.clear(); // Clear the screen
      lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
      lcd.print("SELECT TEST AC");
      lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
      lcd.print("V2: 80%  5000ms"); // Print string 
      interruption = 5000;
      break;
    case 6:
      lcd.clear(); // Clear the screen
      lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
      lcd.print("SELECT TEST AC");
      lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
      lcd.print("V2: 0%  5000ms"); // Print string 
      interruption = 5000;
      break;
 
  }
}
