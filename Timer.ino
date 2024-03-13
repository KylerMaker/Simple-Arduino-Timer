#include <LiquidCrystal.h>;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int minuteCount = 0;
int hourCount = 0;
int timer = 0;
unsigned long startTime;    // in ms
unsigned long currentTime;  // in ms
const unsigned long period = 1000; // period currently runs this timer in seconds. change this value to determine the timer interval!
int minuteButtonPin = 10;
int hourButtonPin = 8;
int startButtonPin = 9;
bool startHasBeenPressed = false;
bool timeCalculated = false;
int finalTime = 0;

void setup() {
  lcd.begin(16, 2);
  startTime = millis();
  pinMode(minuteButtonPin, INPUT_PULLUP);
  pinMode(hourButtonPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);
}

void loop() {
  timerSetup();
  runTimer();
  timerDone();
}

void timerSetup() {
  if (startHasBeenPressed == false) {
    if (digitalRead(startButtonPin) == LOW) {
      startHasBeenPressed = true;
      calculateTime();
      delay(1000);
    }
    if (digitalRead(hourButtonPin) == LOW) {
      if (hourCount == 24) {
        hourCount = 0;
      } else {
        hourCount += 1;
      }
      delay(100);
    }
    if (digitalRead(minuteButtonPin) == LOW) {
      if (minuteCount == 60) {
        minuteCount = 0;
      } else {
        minuteCount += 1;
      }
      delay(100);
    }
    displaySetTimer();
  }
}

void displaySetTimer() {
  timer = hourCount * 60 + minuteCount;
  String displayTimer = "";
  int hours = (timer - (timer % 60)) / 60;
  int minutes = timer % 60;
  if (hours < 10) {
    displayTimer += "0";
    displayTimer += hours;
  } else {
    displayTimer += hours;
  }
  displayTimer += ":";
  if (minutes < 10) {
    displayTimer += "0";
    displayTimer += minutes;
  } else {
    displayTimer += minutes;
  }
  lcd.setCursor(5, 0);
  lcd.print(displayTimer);
}

void displayTimer() {
  timer = hourCount * 60 + minuteCount;
  String displayTimer = "";
  int hours = (finalTime - (finalTime % 60)) / 60;
  int minutes = finalTime % 60;
  if (hours < 10) {
    displayTimer += "0";
    displayTimer += hours;
  } else {
    displayTimer += hours;
  }
  displayTimer += ":";
  if (minutes < 10) {
    displayTimer += "0";
    displayTimer += minutes;
  } else {
    displayTimer += minutes;
  }
  lcd.setCursor(5, 0);
  lcd.print(displayTimer);
}


void calculateTime() {
  if (timeCalculated == false) {
    finalTime = (hourCount * 60) + minuteCount;
    timeCalculated = true;
  }
}

void runTimer() {
  currentTime = millis();
  if (currentTime - startTime >= period && startHasBeenPressed == true) {
    if (finalTime != 0) {
      finalTime--;
      displayTimer();
    }
    startTime = currentTime;
  }
}

void timerDone() {
  if (startHasBeenPressed == true && finalTime == 0) {
    delay(1000);
    for (int i = 0; i < 4; i++){
      lcd.clear();
      delay(750);
      displayTimer();
      delay(750);
    }
    minuteCount = 0;
    hourCount = 0;
    timeCalculated = false;
    finalTime = 0;
    timer = 0;
    startHasBeenPressed = false;
  }
}
