
// include the library code:
#include <LiquidCrystal.h>

// for acclerometer
const int xpin = 0;
const int ypin = 1;
const int zpin = 2;

// for buttons
const int button1 = 2;
const int button2 = 3;
const int button3 = 5;
const int button4 = 7;

int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;

//for LED
const int ledPin = 9;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

void setup() {
  // initialize the serial communications
  Serial.begin(9600);
  // LCD
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
  lcd.print("Device not armed"); 
  lcd.setCursor(0,1); // set the cursor to column 0, row 1
  lcd.print("Enter PIN to arm");
  // LED
  pinMode(ledPin, OUTPUT);
  //buttons
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
}

void loop() {
  if (checkPassword()) {
    lcd.clear();
    lcd.print("  Device armed");
    lcd.setCursor(0,1);
    lcd.print("Enter PIN unarm");
    alarmTrigger();
    lcd.clear();
    lcd.print("Device not armed");
    lcd.setCursor(0,1); // set the cursor to column 0, row 1
    lcd.print("Enter PIN to arm");
  } 
}

bool checkPassword() {
  button1State = digitalRead(button1);
  button3State = digitalRead(button3);
  
  return button1State == LOW && button3State == LOW;
}

void alarmTrigger() {
  do {
    int x = analogRead(xpin);  //read from xpin
    delay(1); //
    int y = analogRead(ypin);  //read from ypin
    delay(1);  
    int z = analogRead(zpin);  //read from zpin
  
    float xProcessed = ((float)x - 331.5)/65*9.8;
    float yProcessed = ((float)y - 329.5)/68.5*9.8;
    float zProcessed = ((float)z - 340)/68*9.8;
    
    x = analogRead(xpin);  //read from xpin
    delay(1); //
    y = analogRead(ypin);  //read from ypin
    delay(1);  
    z = analogRead(zpin);  //read from zpin
    
    float xProcessed2 = ((float)x - 331.5)/65*9.8;
    float yProcessed2 = ((float)y - 329.5)/68.5*9.8;
    float zProcessed2 = ((float)z - 340)/68*9.8;
    
    Serial.print(abs(abs(xProcessed2) - abs(xProcessed)));
    Serial.print("\t");
    Serial.print(abs(abs(yProcessed2) - abs(yProcessed)));
    Serial.print("\t");
    Serial.print(abs(abs(yProcessed2) - abs(yProcessed)));
    Serial.print("\n");
    
    if (abs(abs(xProcessed2) - abs(xProcessed)) > 0.4 || abs(abs(yProcessed2) - abs(yProcessed)) > 0.4 || abs(abs(yProcessed2) - abs(yProcessed)) > 0.4) {
      digitalWrite(ledPin, HIGH); 
    } else {
      digitalWrite(ledPin,LOW);
    }
    
    //delay(500); // wait for half a second
  } while (!checkPassword());
  
}

 
