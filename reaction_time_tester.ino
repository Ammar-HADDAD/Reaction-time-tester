#include <LCD-I2C.h>
#include <Wire.h>

/*
  ***************************************************************
  *                                                             *
  *  Author: Ammar                                             *
  *  Description:                                               *
  *  This Arduino program uses an LCD with I2C interface to      *
  *  display messages and custom characters. It controls a set   *
  *  of LEDs and measures reaction time based on button press.   *
  *  The program implements a simple reaction test game where     *
  *  the user has to press the button as quickly as possible     *
  *  after the LEDs turn off. The fastest reaction time is       *
  *  recorded and displayed on the LCD.                          *
  *                                                             *
  ***************************************************************
*/

// Pin and configuration constants
#define BUTTON_PIN 2                  // Pin number for the button
#define LED_PINS {8, 9, 10, 11, 12}  // Array of LED pin numbers
#define NUM_LEDS 5                    // Number of LEDs
#define LED_DELAY 1000                // Delay between LED transitions
#define MIN_WAIT_DELAY 500            // Minimum random wait delay in milliseconds
#define MAX_WAIT_DELAY 10000          // Maximum random wait delay in milliseconds

// LCD instance
LCD_I2C lcd(0x27, 16, 4);             // Initialize LCD with I2C address 0x27, 16 columns, and 4 rows

// LED pin definitions
const int ledPins[NUM_LEDS] = LED_PINS;

// Variables to track button press and timing
bool btnPressed;
unsigned long btnPressedTime;
unsigned long reactionTime;
unsigned long ledsOff;
unsigned long record = 5000;           // Initial record time in milliseconds

// Custom characters for the LCD
byte fullHeart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

byte bomb[8] = {
  B10101,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B10101
};

byte octopus[8] = {
  B00100,
  B01110,
  B10101,
  B11111,
  B11011,
  B01110,
  B11011,
  B10101
};

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Configure button pin as input
  pinMode(BUTTON_PIN, INPUT);

  // Configure LED pins as outputs
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Initialize I2C communication and LCD
  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();

  // Set up button interrupt
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), btnISR, RISING);

  // Seed random number generator
  randomSeed(0);

  // Create custom characters on the LCD
  lcd.createChar(1, fullHeart);
  lcd.createChar(2, bomb);
  lcd.createChar(3, octopus);

  // Display introductory message on the LCD
  lcd.setCursor(5, 1);
  lcd.print("RT Tester ");
  lcd.write(byte(2));
  lcd.setCursor(0, 3);
  lcd.print("made with ");
  lcd.write(byte(1));
  lcd.print(" by LORD");

  // Wait before starting the game
  delay(5000);
}

void loop() {
  // Prompt user to press button to start the game
  lcd.setCursor(1, 0);
  lcd.print("Hold Press to Play");
  delay(500);

  // Check if button is not pressed
  if(digitalRead(BUTTON_PIN) == LOW){
    return;
  }

  // Countdown before starting the game
  for (int i = 0; i < 5; i++) {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Starting in ");
    lcd.print(5 - i);
    lcd.print(" s");
    delay(1000);
  }

  // Start the game
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("Game started!");

  // Reset button press flag
  btnPressed = false;
  
  // Turn off all LEDs initially
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // Light up LEDs one by one
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(LED_DELAY);
  }

  // Random delay before turning off LEDs
  unsigned long waitDelay = random(MIN_WAIT_DELAY, MAX_WAIT_DELAY + 1);
  delay(waitDelay);

  // Record the time when LEDs are turned off
  ledsOff = millis();

  // Turn off all LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // Wait for button press and record reaction time
  while(true){
    Serial.println(btnPressed);
    if(btnPressed){
      reactionTime = millis();
      break;
    }
  }

  // Display results on the LCD
  if (btnPressedTime < ledsOff) {
    // Button was pressed too early
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.write(byte(2));
    lcd.print(" Game Over ");
    lcd.write(byte(2));
  } else {
    // Calculate and display reaction time
    unsigned long result = reactionTime - ledsOff;
    if (result < record) {
      // New record achieved
      record = result;
      lcd.clear();
      lcd.setCursor(4, 1);
      lcd.write(byte(3));
      lcd.print(" New Record!");
      lcd.setCursor(8, 3);
      lcd.print(record);
      lcd.print(" ms");
    } else {
      // Display result without breaking the record
      lcd.clear();
      lcd.setCursor(3, 1);
      lcd.print("Result :");
      lcd.print(result);
      lcd.print(" ms");
    }
  }

  // Wait before restarting the game
  delay(5000);
}

// Interrupt Service Routine for button press
void btnISR() {
  if (!btnPressed){
    btnPressed = true;
    btnPressedTime = millis();
  }
}
