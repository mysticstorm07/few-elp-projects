#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','4'}, {'5','6','7','8'},
  {'9','.', '0','#'}, {'+','-','x','/'}
};
byte rowPins[ROWS] = {A5, A4, A3, A2};
byte colPins[COLS] = {10, 9, 8, 7};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String equation = "";
String password = "1234";

void setup() {
  lcd.begin(16, 2);
  
  String attempt = "";
  lcd.print("PIN:");
  while (true) {
    char key = keypad.getKey();
    if (key) {
      if (key == '#') {
        if (attempt == password) break;
        lcd.clear(); lcd.print("WRONG"); delay(1000);
        lcd.clear(); lcd.print("PIN:");
        attempt = "";
      } else {
        attempt += key;
        lcd.setCursor(attempt.length()-1, 1); lcd.print('*');
      }
    }
  }
  lcd.clear(); lcd.print("READY"); delay(1000); lcd.clear();
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {
      solveDMAS();
    } else if (key == '.') {
      equation = "";
      lcd.clear();
    } else {
      equation += key;
      render();
    }
  }
}

void render() {
  lcd.setCursor(0, 0);
  lcd.print("                "); 
  lcd.setCursor(0, 0);
  if (equation.length() > 16) lcd.print(equation.substring(equation.length() - 16));
  else lcd.print(equation);
}

void solveDMAS() {
  float values[10];
  char ops[10];
  int vCount = 0, oCount = 0;

  String tmp = "";
  for (int i = 0; i < equation.length(); i++) {
    char c = equation[i];
    if (isDigit(c) || c == '.') tmp += c;
    else {
      values[vCount++] = tmp.toFloat();
      ops[oCount++] = c;
      tmp = "";
    }
  }
  values[vCount++] = tmp.toFloat();

  for (int i = 0; i < oCount; i++) {
    if (ops[i] == 'x' || ops[i] == '/') {
      float res = (ops[i] == 'x') ? values[i] * values[i+1] : values[i] / values[i+1];
      values[i] = res;
      for (int j = i + 1; j < vCount - 1; j++) values[j] = values[j+1];
      for (int j = i; j < oCount - 1; j++) ops[j] = ops[j+1];
      vCount--; oCount--; i--;
    }
  }

  float finalAns = values[0];
  for (int i = 0; i < oCount; i++) {
    if (ops[i] == '+') finalAns += values[i+1];
    if (ops[i] == '-') finalAns -= values[i+1];
  }

  lcd.setCursor(0, 1);
  lcd.print("="); lcd.print(finalAns, 2);
  equation = String(finalAns, 2); 
}