const int numReadings = 10;  // počet vzorků pro průměr
int readings[numReadings];   // pole hodnot
int readIndex = 0;           // index pro ukládání
int total = 0;               // suma hodnot
int average = 0;             // průměrná hodnota

void setup() {
  Serial.begin(115200);
  // inicializace pole hodnot na nulu
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

  // posuň index, pokud dosáhl konce, vrať ho na začátek
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // spočítej průměr
  average = total / numReadings;

  // přemapuj průměrnou hodnotu
  int sensorValue = map(average, 0, 1023, 0, 100);

  Serial.println(sensorValue);

  
}
