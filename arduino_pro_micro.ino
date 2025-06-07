const int numReadings = 10;  // počet vzorků pro průměr
int readings[numReadings];   // pole hodnot
int readIndex = 0;           // index pro ukládání
int total = 0;               // suma hodnot
int average = 0;             // průměrná hodnota

const int buttonPin = 2;
int buttonState = 0;
const int ledPin = 9;
bool mute = false;
bool lastButtonState = HIGH;  // pro detekci změny stavu tlačítka

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // odečti starou hodnotu ze sumy
  total = total - readings[readIndex];

  // přečti novou hodnotu a ulož ji
  readings[readIndex] = analogRead(A0);

  // přičti novou hodnotu k sumě
  total = total + readings[readIndex];

  // posuň index
  readIndex++;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // spočítej průměr
  average = total / numReadings;

  // přemapuj průměrnou hodnotu
  int sensorValue = map(average, 0, 1023, 0, 100);

  // čtení tlačítka s detekcí změny stavu
  int currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    mute = !mute;  // přepne stav mute
  }
  lastButtonState = currentButtonState;

  // logika LED a vypnutí výstupu
  if (mute) {
    digitalWrite(ledPin, HIGH);
    sensorValue = 0;
  } else {
    digitalWrite(ledPin, LOW);
  }

  Serial.println(sensorValue);
  
}
