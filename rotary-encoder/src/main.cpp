#include <Arduino.h>

byte pin[] = {2, 3, 4, 5, 6, 7, 8, 9}; // arduino pin array

int number[10][8] = {
    /*
     E  D  C  .  B  A  F  G
    */
    {1, 1, 1, 0, 1, 1, 1, 0}, // 0
    {0, 0, 1, 0, 1, 0, 0, 0}, // 1
    {0, 0, 1, 0, 1, 0, 1, 1}, // 4
    {0, 1, 1, 0, 0, 1, 1, 1}, // 5
    {1, 1, 1, 0, 0, 1, 1, 1}, // 6
    {0, 0, 1, 0, 1, 1, 0, 0}, // 7
    {1, 1, 1, 0, 1, 1, 1, 1}, // 8
    {0, 1, 1, 0, 1, 1, 1, 1}, // 9
};

const int PinCLK = 10;
const int PinDT = 11;
const int PinSW = 12;

int clkState;
int clkLastState;
int RotaryPosition = 0;
bool buttonPressed = false;

void setup()
{
  for (byte a = 0; a < 8; a++)
  {
    pinMode(pin[a], OUTPUT);
  }

  pinMode(PinCLK, INPUT);
  pinMode(PinDT, INPUT);
  pinMode(PinSW, INPUT);
  digitalWrite(PinSW, HIGH);

  clkLastState = digitalRead(PinCLK);
}

void loop()
{
  if (!(digitalRead(PinSW)))
  {
    buttonPressed = true;
  }
  else
  {
    if (buttonPressed)
    {
      RotaryPosition = (rand() % (9 + 1)) * 2;
    }
    buttonPressed = false;
  }

  clkState = digitalRead(PinCLK);
  if (clkState != clkLastState)
  {
    if ((digitalRead(PinDT) != clkState))
    {
      if (RotaryPosition < 18)
      {
        RotaryPosition = RotaryPosition + 1;
      }
      else
      {
        // RotaryPosition = 0;
      }
    }
    else
    {
      if (RotaryPosition > 0)
      {
        RotaryPosition = RotaryPosition - 1;
      }
      else
      {
        // RotaryPosition = 18;
      }
    }

    clkLastState = clkState;
  }

  if (RotaryPosition % 2 == 0)
  {
    for (int b = 0; b < 8; b++)
    {
      digitalWrite(pin[b], number[RotaryPosition / 2][b]);
    }
  }
}
