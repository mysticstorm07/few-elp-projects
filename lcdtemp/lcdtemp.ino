#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 6
#define DHTTYPE DHT22
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE);

const int fanEnable = 10; 
const int fanIn1 = 9;
const int fanIn2 = 8;
const int acRelay = 7;  
const int ledPin = 13;     
const int heaterPin = A0;  
const float hot = 25.0;
const float cold = 20.0;

void setup() {
  dht.begin();
  lcd.begin(16, 2);
  
  pinMode(fanEnable, OUTPUT);
  pinMode(fanIn1, OUTPUT);
  pinMode(fanIn2, OUTPUT);
  pinMode(acRelay, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
  
  lcd.print("System Ready");
  delay(1000);
}

void loop() {
  float temp = dht.readTemperature();

  lcd.setCursor(0, 0);
  lcd.print("T: "); lcd.print(temp); lcd.print("C ");

  if (temp >= hot) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(fanIn1, HIGH);
    digitalWrite(fanIn2, LOW);
    analogWrite(fanEnable, 255);
    digitalWrite(acRelay, HIGH);
    
    lcd.setCursor(0, 1);
  } 
  
  else if (temp <= cold) {
    digitalWrite(heaterPin, HIGH); 
    digitalWrite(fanIn1, LOW);
    digitalWrite(fanIn2, LOW);
    analogWrite(fanEnable, 0);
    digitalWrite(acRelay, HIGH);
    digitalWrite(ledPin, LOW);
    lcd.setCursor(0, 1);
  } 

  else {
    digitalWrite(fanIn1, LOW);
    digitalWrite(fanIn2, LOW);
    analogWrite(fanEnable, 0);
    digitalWrite(acRelay, LOW);
    digitalWrite(ledPin, LOW);
    digitalWrite(heaterPin, LOW);
    lcd.setCursor(0, 1);;
  }

  delay(2000);
}