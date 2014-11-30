
int sensorPin = A0;    // numer portu analogowego

//int ledPin = 13;      // dioda LED
int inData =3;

int test=0; //ilosc w test
int kalib=0; // Kalibracja
int poziomsum=0; //pomiar suma
int wskaznik =0;
int leds[] = {5, 6, 7, 8, 9, 10, 11, 12, 13,4};
#define SIZE 10

void setup() { 
 for (int x = 0; x < SIZE; x++) {
    pinMode(leds[x], OUTPUT);
  }
  
  pinMode(inData,INPUT);
  Serial.begin(9600);
  for(int i=1; i<17;i++){
    Serial.println("grzejemy...");
    delay(200);
  }

  Serial.println("kalibracja ...");
  for(int i=1;i<11;i++){
      digitalWrite(leds[i-1], HIGH);
    int pomiar = analogRead(sensorPin);
    test = test + pomiar;
    Serial.print("..");
    delay(500);
  }
  kalib=test/10;
  Serial.print("kalibracja");
  Serial.println(kalib);
 
}

void loop() {
 // digitalWrite(w1, HIGH);
  Serial.println("Start pomiaru");
Serial.println("Dmuchaj !!!!!");
//digitalWrite(w10, HIGH);

  for(int h=1;h<11;h++){
    digitalWrite(leds[h-1], HIGH);
    int poziom = analogRead(sensorPin);
    poziomsum = poziomsum+poziom;
    int inAL = digitalRead(inData);
    Serial.print("data: - > "); Serial.println(inAL);
    Serial.println(poziom);
    delay(400);
  }
  
//digitalWrite(w10, LOW);
  int poziomAl = poziomsum/10;
  Serial.print("serdni wynik");
  Serial.println(poziomAl);

  wskaznik = poziomAl - kalib;

  Serial.print("wynik powyzej otoczenia: ");
  Serial.println(wskaznik);

delay(5000);


 for (int x = 0; x < SIZE; x++) {
    digitalWrite(leds[x], LOW);
  }
int val = map(wskaznik, 0, 300, 0, 10);
  Serial.print("Wyswietlam wartos na wy swietlaczu : ");
  Serial.println(val);
  
 for (int x = 0; x < val; x++) {
    digitalWrite(leds[x], HIGH);
  }
  delay(5000);
   for (int x = 0; x < SIZE; x++) {
    digitalWrite(leds[x], LOW);
  }
  poziomsum=0;
wskaznik=0;
}

