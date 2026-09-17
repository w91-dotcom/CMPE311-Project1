#include <Arduino.h>

int selectedLED = -1;

unsigned long blinkRateOne;
unsigned long blinkRateTwo;

unsigned long blinkTrackerOne;
unsigned long blinkTrackerTwo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);


  Serial.println("What LED? (1 or 2):");
}

void loop() {
  // put your main code here, to run repeatedly:

  // Tracks the time
  unsigned long currentTime = millis();

  // Checks the time to see if LED1 should blink
  if (blinkRateOne && (currentTime - blinkTrackerOne) >= (blinkRateOne / 2)){
      digitalWrite(2, !digitalRead(2));
      blinkTrackerOne = currentTime;
  }

  // Checks the time to see if LED2 should blink
  if (blinkRateTwo && (currentTime - blinkTrackerTwo) >= (blinkRateTwo / 2)){
      digitalWrite(3, !digitalRead(3));
      blinkTrackerTwo = currentTime;
  }

  if ((Serial.available() > 0) && (selectedLED == -1)){
    selectedLED = Serial.parseInt(); 

    while (Serial.available() > 0) {
      Serial.read();
    }
    
    Serial.println("What interval (in msec):");
  }

  else if ((Serial.available() > 0) && (selectedLED != -1)){

    // Sets new blink rate based on LED chosen before
    if (selectedLED == 1){
      blinkRateOne = Serial.parseInt(); 
    } else {
      blinkRateTwo = Serial.parseInt(); 
    }

    selectedLED = -1;
    while (Serial.available() > 0) {
      Serial.read();
    }
    Serial.println("What LED? (1 or 2):");

  }

}