#pragma once

/**************************************************
 * How to rick roll. Had to do it to em
 **************************************************/

// notes in the melody:
int melody[] = {
  // nggyu
  NOTE_GS4,
  NOTE_AS4,
  NOTE_CS5,
  NOTE_AS4,
  NOTE_F5,
  NOTE_F5,
  NOTE_DS5,
  // nglyd
  NOTE_GS4,
  NOTE_AS4,
  NOTE_CS5,
  NOTE_AS4,
  NOTE_DS5,
  NOTE_DS5,
  NOTE_CS5,
  // ngraa
  NOTE_GS4,
  NOTE_AS4,
  NOTE_CS5,
  NOTE_AS4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_C5,
  NOTE_AS4,
  NOTE_GS4,
  // dy
  NOTE_GS4,
  NOTE_DS5,
  NOTE_CS5,
  0,


  // nggyu
  NOTE_GS4,
  NOTE_AS4,
  NOTE_CS5,
  NOTE_AS4,
  NOTE_F5,
  NOTE_F5,
  NOTE_DS5,
  // nglyd
  NOTE_GS4,
  NOTE_AS4,
  NOTE_CS5,
  NOTE_AS4,
  NOTE_GS5,
  NOTE_C5,
  NOTE_CS5,
  // ngraa
  NOTE_GS4,
  NOTE_AS4,
  NOTE_CS5,
  NOTE_AS4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_C5,
  NOTE_AS4,
  NOTE_GS4,
  // dy
  NOTE_GS4,
  NOTE_DS5,
  NOTE_CS5,

};

int lights[] = {
  // nggyu
  blue1,
  green1,
  red1,
  green1,
  blue2,
  blue2,
  white1,
  // nglyd
  blue1,
  green1,
  red1,
  green1,
  white1,
  white1,
  red1,
  // ngraa
  blue1,
  green1,
  red1,
  green1,
  red1,
  white1,
  yellow1,
  green1,
  blue1,
  // dy
  blue1,
  white1,
  red1,
  0,


  // nggyu
  blue1,
  green1,
  red1,
  green1,
  blue2,
  blue2,
  white1,
  // nglyd
  blue1,
  green1,
  red1,
  green1,
  green2,
  yellow1,
  red1,
  // ngraa
  blue1,
  green1,
  red1,
  green1,
  red1,
  white1,
  yellow1,
  green1,
  blue1,
  // dy
  blue1,
  white1,
  red1,

};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
float noteDurations[] = {
  // Nggyu
  16,
  16,
  16,
  16,
  16.0 / 3.0,
  16.0 / 3.0,
  8.0 / 3.0,
  // Nglyd
  16,
  16,
  16,
  16,
  16.0 / 3.0,
  16.0 / 3.0,
  8.0 / 3.0,
  // ngraa
  16,
  16,
  16,
  16,
  16.0 / 3.0,
  16.0 / 3.0,
  16.0 / 3.0,
  16,
  4,
  // dy
  8,
  4,
  2,

  64,  // rest

  // Nggyu
  16,
  16,
  16,
  16,
  16.0 / 3.0,
  16.0 / 3.0,
  8.0 / 3.0,
  // Nglyd
  16,
  16,
  16,
  16,
  16.0 / 3.0,
  16.0 / 3.0,
  8.0 / 3.0,
  // ngraa
  16,
  16,
  16,
  16,
  16.0 / 3.0,
  16.0 / 3.0,
  16.0 / 3.0,
  16,
  4,
  // dy
  8,
  4,
  2

};

/**************************************************
 * Do it to em
 **************************************************/
void getRickRolled() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 53; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 2000 / noteDurations[thisNote];
    tone(speaker, melody[thisNote], noteDuration);
    digitalWrite(lights[thisNote], HIGH);

    // very minimal pause between notes
    int pauseBetweenNotes = noteDuration * 1.05;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speaker);
    digitalWrite(lights[thisNote], LOW);
  }
}

