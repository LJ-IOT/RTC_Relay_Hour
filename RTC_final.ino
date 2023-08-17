#include <RTClib.h>
#include <Wire.h>
RTC_DS3231 rtc;
char t[32];
const int Relay = 8;
int valh, valm, vald ;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  Serial.begin(9600);
  pinMode(Relay, OUTPUT); //relay1
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
digitalWrite(Relay, LOW);
delay(5000);
digitalWrite(Relay, HIGH);
}

void loop () {
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(1000);

    valh = (now.hour()); 
    valm = (now.minute());
    vald = (now.day());
    if ((valh > 8) && (valh < 16) && (valm > 00) && (valm <02) && (vald != 7))           
    {
    digitalWrite(Relay, LOW);
    Serial.println('ON');
    }
    else if ((valh > 16) && (valh < 24) && (valm > 00) && (valm <02))
    {
    digitalWrite(Relay, HIGH);
    //Serial.print(':');
    }
    else
    {
    digitalWrite(Relay, HIGH);
    }

}
