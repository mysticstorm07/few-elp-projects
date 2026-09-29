const int s1 = 2;
const int s0 = 3;
const int filter = 9;
const int sinpin = 10;
const int ampPot = A0;
const int frePot = A1;

float phase = 0;

void setup() {
  pinMode(s1, INPUT_PULLUP);
  pinMode(s0, INPUT_PULLUP);
  pinMode(filter, OUTPUT);
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;
}

void loop() {
  int freq = analogRead(frePot);
  int amp = analogRead(ampPot);
  
  float freqStep = map(freq, 0, 1023, 1, 100) / 500.0;
  phase += freqStep;
  if (phase >= 2 * PI) phase = 0;

  int out = 0;

  bool s1_v = digitalRead(s1);

  if (s1_v == LOW){
    if (phase < PI) {
      out = (amp / 4.0);
    } else {
      out = 0;           
    }
    analogWrite(filter, constrain(out, 0, 255));
  }
  else if (s1_v == HIGH){
    out = (sin(phase) + 1.0) * (amp / 8.0);
    analogWrite(sinpin, out);
  }  
}
