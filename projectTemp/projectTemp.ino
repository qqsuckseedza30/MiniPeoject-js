#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_PCF8574.h>

#define ONE_WIRE_BUS 2            //กำหนดขาที่จะเชื่อมต่อ Sensor
LiquidCrystal_PCF8574 lcd(0x27);  // LCD
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

byte dotOff[] = { 0b00000, 0b01110, 0b10001, 0b10001, 0b10001, 0b01110, 0b00000, 0b00000 };
byte dotOn[] = { 0b00000, 0b01110, 0b11111, 0b11111, 0b11111, 0b01110, 0b00000, 0b00000 };
int show = -1;
int vlPin = A0;

void setup() {
  pinMode(vlPin, INPUT);
  sensors.begin();
  initLCD();
  Serial.begin(9600);
}

void loop() {
  int rawVL = analogRead(vlPin);
  int vlN = map(rawVL, 0, 1023, 0, 50);
  
  // Serial.println(vlN);

  // sensors.requestTemperatures();  //อ่านข้อมูลจาก library
  // Serial.print("Temperature is: ");
  // Serial.print(sensors.getTempCByIndex(0));  // แสดงค่า อูณหภูมิ
  // Serial.println(" *C");
  String msgDisplay1 = "Tmp : " + String(sensors.getTempCByIndex(0)) + " *C";

  if (sensors.getTempCByIndex(0) < vlN) {

    String msgDisplay2 = "Start : " + String(vlN);
    displayLCD(msgDisplay1, msgDisplay2);

    Serial.println(msgDisplay1);
    Serial.println(msgDisplay2);
    
  } else {
    String msgDisplay2 = "Stop : " + String(vlN);
    displayLCD(msgDisplay1, msgDisplay2);
    Serial.print(msgDisplay1);
    Serial.println(msgDisplay2);
  }

  delay(1000);
}


void initLCD() {
  int error;
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();

  if (error == 0) {
    // Not ERROR
    Serial.println(": LCD found.");
    show = 0;
    lcd.begin(16, 2);  // initialize the lcd
    lcd.createChar(1, dotOff);
    lcd.createChar(2, dotOn);
    delay(1000);
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("Hello LCD");

  } else {
    // ERROR
    Serial.println(": LCD not found.");
  }
}


void displayLCD(String msg1, String msg2) {
  // msg1 ข้อความที่จะแสดงบันทัดที่ 1
  // msg2 ข้อความที่จะแสดงบันทัดที่ 2
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(msg1);

  lcd.setCursor(0, 1);
  lcd.print(msg2);
}