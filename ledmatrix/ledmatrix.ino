byte heart[8] = {
  0b00000000,
  0b01100110,
  0b11111111,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000 };

byte box[8] = {
  0b11111111,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b11111111};

byte smile[8] = {
  0b00000000,
  0b01100110,
  0b01100110,
  0b00000000,
  0b10000001,
  0b01111110,
  0b00111100,
  0b00000000};

const int rowPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int colPins[] = {A5,A4,A3,A2,13,12,11,10};
const int button = A1; // Using an extra analog pin for the button

int patternIndex = 0;
int buttonState = HIGH;
int lastButtonState = HIGH;

void setup() {
  pinMode(button, INPUT_PULLUP);
  for (int i = 0; i < 8; i++) {
    pinMode(rowPins[i], OUTPUT);
    pinMode(colPins[i], OUTPUT);
  }
}

void loop() {
  // 1. CHECK THE BUTTON
  buttonState = digitalRead(button);
  if (buttonState == LOW && lastButtonState == HIGH) {
    patternIndex = (patternIndex + 1) % 3; // Cycle through 3 patterns
  }
  lastButtonState = buttonState;

  // 2. DRAW THE SELECTED PATTERN
  for (int r = 0; r < 8; r++) {
    byte currentRow;
    
    // Choose which "Blueprint" to use based on the index
    if (patternIndex == 0) currentRow = heart[r];
    else if (patternIndex == 1) currentRow = box[r];
    else currentRow = smile[r];

    // Prepare columns
    for (int c = 0; c < 8; c++) {
      bool pixel = (currentRow >> (7 - c)) & 0x01;
      digitalWrite(colPins[c], !pixel); 
    }

    // Flash the row
    digitalWrite(rowPins[r], HIGH);
    delay(1); // Keep this small!
    digitalWrite(rowPins[r], LOW);
  }
}