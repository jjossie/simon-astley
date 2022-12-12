/*******************************************************************************************
 * SIMON ASTLEY
 *   Author: Joel Jossie
 *
 * This project mimics the old electronic handheld game Simon, where a series of lights and 
 * sounds will play and the user has to copy the pattern by pressing the same buttons. It 
 * starts one button at a time, then adds one each time the user gets it right. My project 
 * does the same thing, but only has one pre-programmed sequence of four light-sound-button 
 * combos, which play the first four notes of the chorus to Rick Astley’s Never Gonna Give 
 * You Up. Why? No reason.
 * 
 * Took some code from this dude:
 * 
 *   created 21 Jan 2010
 *   modified 30 Aug 2011
 *   by Tom Igoe
 * 
 *   This example code is in the public domain.
 * 
 *   https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
 *******************************************************************************************/

#include "config.h"
#include "buttons.h"
#include "roll.h"

/******************************************************************
 * Plays a sequence of Buttons.
 ******************************************************************/
void playSequence(int sequence[], int length, Button *buttons) {
  delay(200);
  for (int i = 0; i < length; i++) {
    buttons[sequence[i]].playNote();
  }
}

enum GameState {
  PLAY,
  USER_INPUT,
  CHECK,
  FAIL,
  PASS,
};

GameState gameState = PLAY;
Button buttons[BUTTON_COUNT];

int sequence[] = { 0, 1, 3, 1 }; // The sequence of notes the user is trying to copy (as indexes of buttons[].)
int currentSequenceLength = 1;   // The length of the current attempt. 1 means only play buttons[0], 
                                 // 2 means play buttons[0], buttons[1], etc. 
int sequenceAttempt[4];          // Holds the indecies of buttons[] that the user has attempted
int iAttempt = 0;                // The index of the current attempt

void setup() {
  // Setup everything
  Serial.begin(9600);
  // Set up lights & speaker as outputs
  pinMode(blue1,   OUTPUT);
  pinMode(green1,  OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(red1,    OUTPUT);
  pinMode(white1,  OUTPUT);
  pinMode(blue2,   OUTPUT);
  pinMode(green2,  OUTPUT);
  pinMode(speaker, OUTPUT);
  // Set up buttons as inputs (they're analog pins but it works)
  pinMode(blueBtn,   INPUT);
  pinMode(greenBtn,  INPUT);
  pinMode(yellowBtn, INPUT);
  pinMode(redBtn,    INPUT);
  pinMode(whiteBtn,  INPUT);
  // Setup the buttons
  buttons[0] = Button(blue1, blueBtn, NOTE_GS4);
  buttons[1] = Button(green1, greenBtn, NOTE_AS4);
  buttons[2] = Button(yellow1, yellowBtn, NOTE_C5);
  buttons[3] = Button(red1, redBtn, NOTE_CS5);
  buttons[4] = Button(white1, whiteBtn, NOTE_DS5);

  gameState = PLAY;
}

void loop() {
  switch (gameState) {
    case USER_INPUT:
      // Loop through all the buttons to see if any are pressed
      for (int iButton = 0; iButton < BUTTON_COUNT; iButton++) {
        bool pressed = buttons[iButton].updateInput();
        if (pressed) {
          // Add it to the sequence attempt
          sequenceAttempt[iAttempt++] = iButton;
          if (iAttempt == currentSequenceLength) {
            gameState = CHECK;
            break;
          }
        }
      }
      break;

    case PLAY:
      // Play the sequence up to the current length, then turn control back to the user
      playSequence(sequence, currentSequenceLength, buttons);
      gameState = USER_INPUT;
      break;

    case CHECK:
      // Reset the attempt
      iAttempt = 0;
      // Check the attempted sequence against the expected sequence, but only to the current length
      for (int i = 0; i < currentSequenceLength; i++) {
        if (sequenceAttempt[i] != sequence[i]) {
          gameState = FAIL;
          break;
        }
      }
      if (gameState != FAIL) {
        // Move on to the next attempt or finish
        currentSequenceLength++;
        if (currentSequenceLength > 4)
          gameState = PASS; // Mission Accomplished!
        else
          gameState = PLAY; // Passed, but more left to do
      }
      break;

    case FAIL:
      // Play an error tone
      tone(speaker, NOTE_CS3, 250);
      delay(500);
      noTone(speaker);
      // Reset the sequence length to start over from the beginning
      currentSequenceLength = 1;
      gameState = PLAY;
      break;

    case PASS:
      // Prank 'em, John!
      getRickRolled();
      gameState = USER_INPUT;

    default:
      gameState = USER_INPUT;
      break;
  }

  delay(10);
}
