#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above

const char* ssid = "Virus575";
const char* password = "Index1209";

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
String tag;
WiFiClientSecure client;
void setup(){
Serial.begin(9600);
WiFi.begin(ssid, password); 
while (WiFi.status() != WL_CONNECTED) { 
delay(1000);
Serial.print("Connecting..");
client.setInsecure();
}                                  
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
}
void loop() {
  char* iphone12;
  HTTPClient http;
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
String link= upload(tag);
  http.begin(client, link);
  int httpCode = http.GET(); 
  http.end();
    Serial.println(tag);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}

String upload(String tag){
  String iphone12 = "https://script.google.com/a/yourdomain.com/macros/s/AKfycbzvIsrgM1NQFzLUmfL4SxqB4QQeIcWzjIDMuA-Cx6lnQ9cW6g/exec?temperature=iphone12&humidity=1000000";
  String iphone6 = "https://script.google.com/a/yourdomain.com/macros/s/AKfycbzvIsrgM1NQFzLUmfL4SxqB4QQeIcWzjIDMuA-Cx6lnQ9cW6g/exec?temperature=iphone6&humidity=1000000";
  if (tag == "16219915128")
  return iphone12;
  else
  return iphone6;
}
