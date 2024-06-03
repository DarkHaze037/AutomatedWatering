#include<DHT.h>
#include<WiFi.h>
#include "ThingSpeak.h";

#define WIFI_SSID "Redmi Note 12 Pro 5G"
#define WIFI_PASS "@Duong371"
#define SECRET_CH_ID 2356466
#define SECRET_WRITE_APIKEY "73YYO9A17VCV4LA7"
#define SECRET_READ_APIKEY "AQ82NST9KADHTCHW"
#define dhtPin 4
#define dhtType DHT11
DHT dht(dhtPin,dhtType);
#define RXp2 16
#define TXp2 17
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
const char *myReadAPIKey = SECRET_READ_APIKEY;
unsigned long dataMillis = 0;
WiFiClient client;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600,SERIAL_8N1,16,17);
  dht.begin();
  digitalWrite(4,HIGH);
  
  WiFi.begin(WIFI_SSID,WIFI_PASS);
  Serial.print("Connecting to Wi-fi");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  ThingSpeak.setField(1,humidity);
  ThingSpeak.setField(2,temperature);
  if(millis() - dataMillis > 20000)
  {
    int x = ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
    float field1 = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);
    float field2 = ThingSpeak.readFloatField(myChannelNumber, 2, myReadAPIKey);
    Serial.print(field2);
    Serial.print(",");
    Serial.println(field1);
  }

  delay(10000);

}
