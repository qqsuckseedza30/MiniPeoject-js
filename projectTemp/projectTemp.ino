#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_PCF8574.h>

#define ONE_WIRE_BUS 2            //กำหนดขาที่จะเชื่อมต่อ Sensor
LiquidCrystal_PCF8574 lcd(0x27);  // LCD
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int show = -1;
byte dotOff[] = { 0b00000, 0b01110, 0b10001, 0b10001,
                  0b10001, 0b01110, 0b00000, 0b00000 };
byte dotOn[] = { 0b00000, 0b01110, 0b11111, 0b11111,
                 0b11111, 0b01110, 0b00000, 0b00000 };

void setup(void) {
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library");
  sensors.begin();
  initLCD();
}

void loop(void) {
  Serial.println("Requesting temperatures...");
  sensors.requestTemperatures();  //อ่านข้อมูลจาก library
  Serial.print("Temperature is: ");
  Serial.print(sensors.getTempCByIndex(0));  // แสดงค่า อูณหภูมิ
  Serial.println(" *C");

  String msgDisplay1 = "Tmp : " + String(sensors.getTempCByIndex(0)) + " *C";
   String msgDisplay2 = "===============";

  //String msgDisplay1 = "====TEST1=====";
  //String msgDisplay2 = "====TEST2======";

  displayLCD(msgDisplay1, msgDisplay2);

  delay(3000);
}


void initLCD() {
  int error;
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();

  if (error == 0) {
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