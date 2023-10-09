#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 


#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



#define TRIGGER_PIN  12  // D6 
#define ECHO_PIN     14  // D5 
#define MAX_DISTANCE 200 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

const char* ssid = "ssid";
const char* password = "pass";


#define BOTtoken "xxxxxxxxxx:jjjjjjjjjjjjjjjjjjjjjjjjjjjjjj"  


#define CHAT_ID "888888888888888888"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);



void setup() {
  Serial.begin(115200); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  configTime(0, 0, "pool.ntp.org");      
  client.setTrustAnchors(&cert); 

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
  
  bot.sendMessage(CHAT_ID, "Bot started up", "");



  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);

  
  display.clearDisplay();

  display.setTextColor(WHITE); 
  display.setCursor(0,24);
  display.println("SMKN1 TPI");
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextColor(WHITE); 
  display.setCursor(0,24);
  display.println("PROJECT Meteran IoT");
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setCursor(0,24);
  display.println("Presented by wingky");
  display.display();
  delay(3000);
  display.clearDisplay();

  
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("MOHON");
  display.println("TUNGGU");
  display.println("SEBENTAR");
  display.display();
  display.startscrollright(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);    
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  display.clearDisplay();
}

void loop() {
  delay(50);                    
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); 
  Serial.println("cm");

  delay(100);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("meteran Iot");

    
  display.setTextSize(2);
  display.print("nilai:");
  display.print(sonar.ping_cm());
  display.println("Cm");
  display.display(); 
  int value = sonar.ping_cm();
  display.clearDisplay();
   bot.sendMessage(CHAT_ID,"data ketinggian:  " + String(value)+ " Cm", "");


}