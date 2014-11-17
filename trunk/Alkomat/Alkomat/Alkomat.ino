
int sensorPin = A0;    // numer portu analogowego
int ledPin = 13;      // dioda LED
int test=0; //ilosc w test
int kalib=0; // Kalibracja
int poziomsum=0; //pomiar suma
int wskaznik =0;

void setup() {

  Serial.begin(9600);
  for(int i=1; i<17;i++){
    Serial.println("grzejemy...");
    delay(200);
  }

  Serial.println("kalibracja ...");
  for(int i=1;i<11;i++){
    int pomiar = analogRead(sensorPin);
    test = test + pomiar;
    Serial.print("..");
    delay(500);
  }
  kalib=test/10;
  Serial.print("kalibracja");
  Serial.println(kalib);
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  Serial.println("Start pomiaru");

  for(int h=1;h<6;h++){
    int poziom = analogRead(sensorPin);
    poziomsum = poziomsum+poziom;
    Serial.println(poziom);
    delay(400);
  }

  int poziomAl = poziomsum/5;
  Serial.println("serdni wynik");
  Serial.print(poziomAl);

  wskaznik = poziomAl - kalib;

  Serial.println("wynik powyzej otoczenia");
  Serial.print(wskaznik);

delay(5000);
poziomsum=0;
wskaznik=0;
}

