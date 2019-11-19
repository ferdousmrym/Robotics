Lab homeworks
LAB 5 - Homework:

// digital pin connected to switch output
const int pinSW = 0; 
// A0 - analog pin connected to X output
const int pinX = A1; 
// A1 - analog pin connected to Y output
const int pinY = A0; 
// segments array, similar to before
int segments[segSize] = {
pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
  // activate the display no. received as param
void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}

