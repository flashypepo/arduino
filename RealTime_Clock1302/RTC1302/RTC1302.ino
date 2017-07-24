#include <LCD5110_Graph.h>
#include <stdio.h>
#include <DS1302.h>

LCD5110 lcd(8,9,10,12,11);
extern unsigned char BigNumbers[];
extern unsigned char SmallFont[];
extern uint8_t clock[];

namespace {

const int kCePin   = 5;  //RST
const int kIoPin   = 6;  //DAT
const int kSclkPin = 7;  //CLK

// Create a DS1302 object.
DS1302 rtc(kCePin, kIoPin, kSclkPin);

String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
}
}

void setup() {
 
 setTime(); 
 lcd.InitLCD();
 lcd.clrScr();
 lcd.drawBitmap(0, 0, clock, 84, 48);
 lcd.update();  
 delay(3000);
}

void loop() {
 
 printTime();
 delay(1000);
}

void printTime() {
  
  Time t = rtc.time();
  
  const String day = dayAsString(t.day);
  String month;
  String date;
  String hour;
  String minutes;
  
  month = String(t.mon);
  date = String(t.date);
  hour = String(t.hr);
  minutes = String(t.min);
  
 String fullDate = day+" "+month+"/"+date; 
  
  lcd.clrScr();
  lcd.setFont(SmallFont);
  lcd.print(fullDate,0,0);
  
  lcd.setFont(BigNumbers);
  
  if(t.hr<10)
  {
    hour = "0"+hour;
    lcd.print(hour,7,18);
  }else
  {
        lcd.print(hour,7,18);
  }
  lcd.print(".",35,18);
  if(t.min<10)
  {
    minutes = "0"+minutes;
    lcd.print(minutes,47,18);
  }else
  {
      lcd.print(minutes,47,18);
  }
  lcd.update();
}

void setTime()
{
  rtc.writeProtect(false);
  rtc.halt(false);
  Time t(2015, 2, 26, 13, 35, 50, Time::kThursday); //Change this line to set time  ex 2015 26/2 9:09:50
  rtc.time(t);
}
