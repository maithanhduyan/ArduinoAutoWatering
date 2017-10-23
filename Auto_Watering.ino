
#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68
int second  ; //second
int _minute  ; //minute
int _hour  ; //hour
int set_minute = 0;

int relay1 = 2 ; // set Pin 2 is control Relay 1
int relay2 = 3 ; // set Pin 3 is control Relay 2

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  // setDS3231time(0, 40, 9, 3, 23, 8, 16);

  delay(1000);
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
                   dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second,
                    byte *minute,
                    byte *hour,
                    byte *dayOfWeek,
                    byte *dayOfMonth,
                    byte *month,
                    byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());

}
void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
                 &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute < 10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second < 10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch (dayOfWeek) {
    case 1:
      Serial.println("Sunday");
      break;
    case 2:
      Serial.println("Monday");
      break;
    case 3:
      Serial.println("Tuesday");
      break;
    case 4:
      Serial.println("Wednesday");
      break;
    case 5:
      Serial.println("Thursday");
      break;
    case 6:
      Serial.println("Friday");
      break;
    case 7:
      Serial.println("Saturday");
      break;
  }
    //
  _minute = minute ; 
  _hour = hour;
}
void watering() {
  digitalWrite(relay1, LOW); // LOW = ON
  delay(60000);     //Cho nước vào 60s
  digitalWrite(relay1, HIGH); // HIGH = OFF
  delay(300000);    //Đợi 5 phút
  digitalWrite(relay2, LOW); // LOW = ON
  delay(120000);    // Xả nước ra 120s = 2 phút
  digitalWrite(relay2, HIGH); // HIGH = OFF
}
void loop()
{
  displayTime(); // display the real-time clock data on the Serial Monitor,
  digitalWrite(relay1, HIGH);  //Valve 1 OFF
  digitalWrite(relay2, HIGH);   // Valve 2 OFF
  delay(1000);
  //------ TƯỚI LẦN 1 VÀO LÚC 0Giờ:0phút
  if (_hour == 0 && _minute == set_minute) {
    Serial.println("Tuoi lan 1");
    watering();
  }
  //------ TƯỚI LẦN 2 VÀO LÚC 2Giờ:0phút
  if (_hour == 2 && _minute == set_minute) {
    Serial.println("Tuoi lan 2");
    watering();
  }
  //------ TƯỚI LẦN 3 VÀO LÚC 4Giờ:0phút
  if (_hour == 4 && _minute == set_minute) {
    Serial.println("Tuoi lan 3");
    watering();
  }
  //------ TƯỚI LẦN 4 VÀO LÚC 6Giờ:0phút
  if (_hour == 6 && _minute == set_minute) {
    Serial.println("Tuoi lan 4");
    watering();
  }
  //------ TƯỚI LẦN 5 VÀO LÚC 8Giờ:0phút
  if (_hour == 8 && _minute == set_minute) {
    Serial.println("Tuoi lan 5");
    watering();
  }
  //------ TƯỚI LẦN 6 VÀO LÚC 10Giờ:0phút
  if (_hour == 10 && _minute == set_minute) {
    Serial.println("Tuoi lan 6");
    watering();
  }
  //------ TƯỚI LẦN 7 VÀO LÚC 12Giờ:0phút
  if (_hour == 12 && _minute == set_minute) {
    Serial.println("Tuoi lan 7");
    watering();
  }
  //------ TƯỚI LẦN 8 VÀO LÚC 14Giờ:0phút
  if (_hour == 14 && _minute == set_minute) {
    Serial.println("Tuoi lan 8");
    watering();
  }
  //------ TƯỚI LẦN 9 VÀO LÚC 16Giờ:0phút
  if (_hour == 16 && _minute == set_minute) {
    Serial.println("Tuoi lan 9");
    watering();
  }
  //------ TƯỚI LẦN 10 VÀO LÚC 18Giờ:0phút
  if (_hour == 18 && _minute == set_minute) {
    Serial.println("Tuoi lan 10");
    watering();
  }
  //------ TƯỚI LẦN 11 VÀO LÚC 20Giờ:0phút
  if (_hour == 20 && _minute == set_minute) {
    Serial.println("Tuoi lan 11");
    watering();
  }
  //------ TƯỚI LẦN 12 VÀO LÚC 22Giờ:0phút
  if (_hour == 22 && _minute == set_minute) {
    Serial.println("Tuoi lan 12");
    watering();
  }

}//end Loop
