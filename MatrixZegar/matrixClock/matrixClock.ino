#include "LedControlMS.h"
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

#define NBR_MTX 1 
LedControl lc=LedControl(5,4,3, NBR_MTX);

unsigned long delaytime=300;

int second=0, minute=0, hour=0; //start the time on 00:00:00
int munit,hunit,valm=0,valh=0,ledstats,i,secondunit=0;
 
void setup() { //set outputs and inputs
//pinMode(1, OUTPUT);pinMode(2, OUTPUT);pinMode(3, OUTPUT);pinMode(4, OUTPUT);pinMode(5, OUTPUT);
//pinMode(6, OUTPUT);pinMode(7, OUTPUT);pinMode(8, OUTPUT);pinMode(9, OUTPUT);pinMode(10, OUTPUT);
//pinMode(11, OUTPUT);pinMode(12, OUTPUT);pinMode(13, OUTPUT);
second=0; minute=0; hour=0;
  Serial.begin (9600);
  Serial.println("Setup");
  
    Wire.begin();
    RTC.begin();
    
      if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
  } 
  
pinMode(0, INPUT);

  for (int i=0; i< NBR_MTX; i++){
    lc.shutdown(i,false);
  /* Set the brightness to a medium values */
    lc.setIntensity(i,8);
  /* and clear the display */
    lc.clearDisplay(i);
  }
   Serial.println("Koniec SETUP");
}
 
void loop() {

static unsigned long lastTick = 0; // set up a local variable to hold the last time we moved forward one second
// (static variables are initialized once and keep their values between function calls)
// move forward one second every 1000 milliseconds
 
if (millis() - lastTick >= 1000) {
lastTick = millis();
second++;
 
}
 
// move forward one minute every 60 seconds
if (second >= 60) {
minute++;
second = 0; // reset seconds to zero
}
 
// move forward one hour every 60 minutes
if (minute >=60) {
hour++;
minute = 0; // reset minutes to zero
}
 
if (hour >=24) {
hour=0;
minute = 0; // reset minutes to zero
}
 
munit = minute%10; //sets the variable munit and hunit for the unit digits
hunit = hour%10;
secondunit = second%10;


                  
//  Serial.println(hour+' '+hunit+' : '+minute+' '+munit);
  
ledstats = digitalRead(0); // read input value, for setting leds off, but keeping count
if (ledstats == LOW) {
for(i=1;i<=13;i++){
digitalWrite(i, LOW);}
} else {

//sec units
if(secondunit == 1 || secondunit == 3 || secondunit == 5 || secondunit == 7 || secondunit == 9) { lc.setLed(0,7,0,true);} else { lc.setLed(0,7,0,false);}
if(secondunit == 2 || secondunit == 3 || secondunit == 6 || secondunit == 7) {lc.setLed(0,7,1,true);} else {lc.setLed(0,7,1,false);}
if(secondunit == 4 || secondunit == 5 || secondunit == 6 || secondunit == 7) {lc.setLed(0,7,2,true);} else {lc.setLed(0,7,2,false);}
if(secondunit == 8 || secondunit == 9) {lc.setLed(0,7,3,true);} else {lc.setLed(0,7,3,false);}
 
//sec
if((second >= 10 && second < 20) || (second >= 30 && second < 40) || (second >= 50 && second < 60)) {lc.setLed(0,6,0,true);} else {lc.setLed(0,6,0,false);}
if(second >= 20 && second < 40) {lc.setLed(0,6,1,true);} else {lc.setLed(0,6,1,false);}
if(second >= 40 && second < 60) {lc.setLed(0,6,2,true);} else {lc.setLed(0,6,2,true);}
 
//minutes units
if(munit == 1 || munit == 3 || munit == 5 || munit == 7 || munit == 9) { lc.setLed(0,4,0,true);} else { lc.setLed(0,4,0,false);}
if(munit == 2 || munit == 3 || munit == 6 || munit == 7) {lc.setLed(0,4,1,true);} else {lc.setLed(0,4,1,false);}
if(munit == 4 || munit == 5 || munit == 6 || munit == 7) {lc.setLed(0,4,2,true);} else {lc.setLed(0,4,2,false);}
if(munit == 8 || munit == 9) {lc.setLed(0,4,3,true);} else {lc.setLed(0,4,3,false);}
 
//minutes
if((minute >= 10 && minute < 20) || (minute >= 30 && minute < 40) || (minute >= 50 && minute < 60)) {lc.setLed(0,3,0,true);} else {lc.setLed(0,3,0,false);}
if(minute >= 20 && minute < 40) {lc.setLed(0,3,1,true);} else {lc.setLed(0,3,1,false);}
if(minute >= 40 && minute < 60) {lc.setLed(0,3,2,true);} else {lc.setLed(0,3,2,true);}

//hour units
if(hunit == 1 || hunit == 3 || hunit == 5 || hunit == 7 || hunit == 9) {lc.setLed(0,1,0,true);} else {lc.setLed(0,1,0,false);}
if(hunit == 2 || hunit == 3 || hunit == 6 || hunit == 7) {lc.setLed(0,1,1,true);} else {lc.setLed(0,1,1,false);}
if(hunit == 4 || hunit == 5 || hunit == 6 || hunit == 7) {lc.setLed(0,1,2,true);} else {lc.setLed(0,1,2,false);}
if(hunit == 8 || hunit == 9) {lc.setLed(0,1,3,true);} else {lc.setLed(0,1,3,false);}
 
//hour
if(hour >= 10 && hour < 20) {lc.setLed(0,0,0,true);} else {lc.setLed(0,0,0,false);}
if(hour >= 20 && hour < 24) {lc.setLed(0,0,1,true);} else {lc.setLed(0,0,1,false);}
 
}
 
valm = analogRead(0); // add one minute when pressed
if(valm<800) {
minute++;
second=0;
delay(250);
}
valh = analogRead(5); // add one hour when pressed
if(valh<800) {
hour++;
second=0;
delay(250);
}
 
 
}
