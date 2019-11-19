const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;
const int segSize = 8;
const int noOfDisplays = 4;
const int noOfDigits = 10;

const int pinSW = 0; // digital pin connected to switch output
const int pinX = A1; // A0 - analog pin connected to X output
const int pinY = A0; // A1 - analog pin connected to Y output
int switchValue;
int xValue = 0;
int yValue = 0;
int i0 = 0, i1 = 0, i2 = 0, i3 = 0, i = 0;
int sw = 1;
int sw1 = 1;
int sw2 = 1;
int currentDigit = 0;
int pressed = 0;

// segments array, similar to before
int segments[segSize] = {
pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
// digits array, to switch between them easily
int digits[noOfDisplays] = {
pinD1, pinD2, pinD3, pinD4
};
byte digitMatrix[noOfDigits][segSize - 1] = {
// a b c d e f g
{1, 1, 1, 1, 1, 1, 0}, // 0
{0, 1, 1, 0, 0, 0, 0}, // 1
{1, 1, 0, 1, 1, 0, 1}, // 2
{1, 1, 1, 1, 0, 0, 1}, // 3
{0, 1, 1, 0, 0, 1, 1}, // 4
{1, 0, 1, 1, 0, 1, 1}, // 5
{1, 0, 1, 1, 1, 1, 1}, // 6
{1, 1, 1, 0, 0, 0, 0}, // 7
{1, 1, 1, 1, 1, 1, 1}, // 8
{1, 1, 1, 1, 0, 1, 1} // 9
};

void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
    // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1], decimalPoint);
}
  // activate the display no. received as param
void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}

int joystickDigit(int i){
  
  xValue = analogRead(pinX);
  
  if(xValue > 950 && sw1 == 1){
    i++;
    sw1 = 0;
    i = i % 10;
  }
  
  if(xValue < 50 && sw1 == 1){
    i--;
    sw1 = 0;
    if(i == -1)
      i = 9;
    i = i % 10;
  }

  if(xValue > 500 && xValue < 800)
    sw1 = 1;
  return i;
}

void setup() {
  for (int i = 0; i <= segSize - 1; i++)
  {
    pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < noOfDisplays; i++)
  {
    pinMode(digits[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int digit;
  switchValue = !digitalRead(pinSW);
  
  if (switchValue == 1 && sw == 1){
      if (pressed == 1)
        pressed = 0;
      else
        pressed = 1;
      sw = 0;
  }
  if (switchValue == 0)
    sw = 1;
    
  if (pressed == 0){
    yValue = analogRead(pinY);
    if(yValue > 950 && sw2 == 1){
      currentDigit++;
      sw2 = 0;
      currentDigit = currentDigit % 4;
    }
    
    if (yValue < 50 && sw2 == 1){
      currentDigit--;
      sw2 = 0;
      if (currentDigit < 0)
        currentDigit = 4 + currentDigit;
    }
  
    if(yValue > 500 && yValue < 800)
      sw2 = 1;
  }

  if(pressed == 1){  
    if(currentDigit == 0)
      i0 = joystickDigit(i0);
    if(currentDigit == 1)
      i1 = joystickDigit(i1);
    if(currentDigit == 2)
      i2 = joystickDigit(i2);
    if(currentDigit == 3)
      i3 = joystickDigit(i3);
  }

  Serial.print("Digitul curent:");
  Serial.print(currentDigit);
  Serial.print(" ");
  Serial.print(i3);
  Serial.print(" ");
  Serial.print(i2);
  Serial.print(" ");
  Serial.print(i1);
  Serial.print(" ");
  Serial.println(i0);

  digit = 0;
  while (digit != 4) {
    showDigit(digit);
    if (pressed == 0){
      if (digit == 0 && currentDigit == 0 && millis() % 500 > 250)
        displayNumber(i0, HIGH);
      else if (digit == 0)
        displayNumber(i0, LOW);
      if (digit == 1 && currentDigit == 1 && millis() % 500 > 250)
        displayNumber(i1, HIGH);
      else if (digit == 1)
        displayNumber(i1, LOW);
      if (digit == 2 && currentDigit == 2 && millis() % 500 > 250)
        displayNumber(i2, HIGH);
      else if (digit == 2)
        displayNumber(i2, LOW);
      if (digit == 3 && currentDigit == 3 && millis() % 500 > 250)
        displayNumber(i3, HIGH);
      else if (digit == 3)
        displayNumber(i3, LOW);
    }
    else{
      if (digit == 0 && currentDigit == 0)
        displayNumber(i0, HIGH);
      else if (digit == 0)
        displayNumber(i0, LOW);
      if (digit == 1 && currentDigit == 1)
        displayNumber(i1, HIGH);
      else if (digit == 1)
        displayNumber(i1, LOW);
      if (digit == 2 && currentDigit == 2)
        displayNumber(i2, HIGH);
      else if (digit == 2)
        displayNumber(i2, LOW);
      if (digit == 3 && currentDigit == 3)
        displayNumber(i3, HIGH);
      else if (digit == 3)
        displayNumber(i3, LOW);
    }
    delay(4);
    digit++;
  }
}
