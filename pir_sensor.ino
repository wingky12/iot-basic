#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);


const char* ssid = "nama ssid wifi";
const char* password = "password";

int ledPin = 2;                
int inputPin = 16;              
int pirState = LOW;            
int val = 0;                  
 


// Initialize Telegram BOT
#define BOTtoken "xxxxxxxxxx:AAAAAAAAAAAAAAAAAAAAAAAAAAAAaAAA"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "2222222222222222"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);     
  pinMode(inputPin, INPUT);    
  configTime(0, 0, "pool.ntp.org");     
  client.setTrustAnchors(&cert); 

  lcd.init();
  lcd.backlight(); 

 
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0,0); lcd.print("Trainer Kit IoT"); 
  lcd.setCursor(0,1); lcd.print("Connecting-WiFi");
  bot.sendMessage(CHAT_ID, "Bot started up", "");
  lcd.setCursor(0,1); lcd.print("Bot startup");
}

void loop() {
  lcd.setCursor(0, 1);
  val = digitalRead(inputPin); 
  if (val == HIGH) {           
    digitalWrite(ledPin, HIGH);  
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      lcd.print("Motion Detected..");
      bot.sendMessage(CHAT_ID, "Motion detected!!", ""); 
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      lcd.print("motion ended..!");
      bot.sendMessage(CHAT_ID, "Motion ended!!", ""); 
      pirState = LOW;
    }
  }
}