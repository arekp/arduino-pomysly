/* Alkomat na podstawie czujnika MQ-3
 */

int sensorPin = A0;    // numer portu analogowego na którym czytamy wartosc

//int ledPin = 13;      // dioda LED
int inData =3; // Pin DATA z czujnika przekroczenie progu wykrywania 

int test=0; //ilosc w test
int kalib=0; // Kalibracja okreslenie wartosci poczatkowej
int poziomsum=0; //pomiar suma ze wskaznika podczas pomiaru
int wskaznik =0;

int leds[] = {
  5, 6, 7, 8, 9, 10, 11, 12, 13,4};
#define SIZE 10

void setup() { 
  Serial.begin(9600);
  for (int x = 0; x < SIZE; x++) {
    pinMode(leds[x], OUTPUT);
  }
  pinMode(inData,INPUT);
/* Przy pierszym odpaleniu potrzeba nagrzania grzałki */
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
  kalib=test/10; // wyliczamy wartość poczatkową
    Serial.print("kalibracja"); Serial.println(kalib);
}

void loop() {
  Serial.println("Start pomiaru");
  Serial.println("Dmuchaj !!!!!");

  for(int h=1;h<11;h++){
    digitalWrite(leds[h-1], HIGH);
    int poziom = analogRead(sensorPin); //Czytamy wartosc z czujnika
    poziomsum = poziomsum+poziom;
    int inAL = digitalRead(inData); //Czytamy stan ustawiony na czujniku 0 / 1
    Serial.print("data: - > "); 
    Serial.println(inAL);
    Serial.println(poziom);
    delay(400);
  }
 
  int poziomAl = poziomsum/10; // Obliczamy usredniona wartosc z pomiaru
  Serial.print("serdni wynik"); Serial.println(poziomAl);

  wskaznik = poziomAl - kalib; // wartość powyzej danych startowych
  Serial.print("wynik powyzej otoczenia: "); Serial.println(wskaznik);

long mgCalk = map(poziomAl,0,1023,0,10);// wartosc w mg/L dla całkowitego pomiaru
  Serial.print("Wartosc całkowita mg/l: "); Serial.println(mgCalk);
long promile =  mgCalk*2.1;
  Serial.print("Promile: "); Serial.println(promile);
Serial.println("-------------------------------------------------");
long mgCzastkowe = map(poziomAl,0,1023,0,10);
  Serial.print("Wartosc czastkowa mg/l: "); Serial.println(mgCzastkowe);
  
/*Czyszenie wskaznika */
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


