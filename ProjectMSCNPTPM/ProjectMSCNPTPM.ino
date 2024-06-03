#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
  mySerial.begin(9600);     // Serial monitor
  Serial.begin(115200);
  delay(100);
  pinMode(4,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("MSCNPTPM");
  lcd.setCursor(3,1);
  lcd.print("Nhom: 16");
  delay(5000);
  lcd.clear();
}
float t = 0;//temperature
float h = 0;//humidity
void loop() {
  if(mySerial.available()){
    String received  = "";
    received = mySerial.readStringUntil('\n');
    int comma = received.indexOf(',');
    if(comma !=-1)
    {
      t = received.substring(0,comma).toFloat();
      h = received.substring(comma+1).toFloat();
    }

    Serial.print("Temperature value: ");
    Serial.println(t);
    
    lcd.setCursor(0,0);
    lcd.print("T:");
    lcd.setCursor(2,0);
    lcd.print(t);
    lcd.setCursor(6,0);
    lcd.print("oC");

    Serial.print("Humidity value: ");
    Serial.println(h);
    
    lcd.setCursor(9,0);
    lcd.print("H:");
    lcd.setCursor(11,0);
    lcd.print(h);
    lcd.setCursor(15,0);
    lcd.print("%");
  }
  if(t > 30.0 && h>50)
  {
    lcd.setCursor(0,1);
    lcd.print("Pump: BAT");
    digitalWrite(4,HIGH);
  }else{
    lcd.setCursor(0,1);
    lcd.print("Pump: TAT");
    digitalWrite(4,LOW);
  }
  }