#pragma once

/****************************************************************************
 * Button Class: Associates a light pin with a button pin and a note.
 * Has methods for checking momentary input and playing a note synchronously.
 ***************************************************************************/
class Button {

public:
  Button() {}
  Button(int light, int button, int note)
    : lightPin(light), buttonPin(button), noteNum(note) {}

  bool updateInput() {
    int btnState = digitalRead(buttonPin);
    if (btnState == HIGH) {
      playNote();
      return true;
    }
    digitalWrite(lightPin, LOW);
    noTone(speaker);
    return false;
  }

  void playNote() {
    digitalWrite(lightPin, HIGH);
    tone(speaker, noteNum, 260);
    delay(300);
    noTone(speaker);
    digitalWrite(lightPin, LOW);
  }


private:
  int lightPin;
  int buttonPin;
  unsigned int noteNum;
};
