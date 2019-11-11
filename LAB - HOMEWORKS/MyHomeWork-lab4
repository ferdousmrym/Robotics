#include "pitches.h"
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int buttonPin = 12;
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4,4};

void setup()
{
 pinMode(buttonPin, INPUT);
}

void loop() 
{
 int buttonState = digitalRead(buttonPin);
 if(buttonState == 1)
 {
 for(int thisNote=0; thisNote<8; thisNote++){
 int NoteDuration = 1000 / noteDurations [thisNote];
 tone(8, melody [thisNote], NoteDuration);
 
 int pauseBetweenNotes = NoteDuration * 1.30; 
 delay(pauseBetweenNotes);
 noTone(8);
  }
 }
}
