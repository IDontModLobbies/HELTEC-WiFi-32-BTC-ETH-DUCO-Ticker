/*  
  ______ _________ _______      __      _______ _________           
 (  ___ \\__   __/(  ____ \    /__\    (  ____ \\__   __/|\     /|  
 | (   ) )  ) (   | (    \/   ( \/ )   | (    \/   ) (   | )   ( |  
 | (__/ /   | |   | |          \  /    | (__       | |   | (___) |  
 |  __ (    | |   | |          /  \/\  |  __)      | |   |  ___  |  
 | (  \ \   | |   | |         / /\  /  | (         | |   | (   ) |  
 | )___) )  | |   | (____/\  (  \/  \  | (____/\   | |   | )   ( |  
 |/ \___/   )_(   (_______/   \___/\/  (_______/   )_(   |/     \|  
 
                                                                 
 __________________ _______  _        _______  _______              
 \__   __/\__   __/(  ____ \| \    /\(  ____ \(  ____ )             
    ) (      ) (   | (    \/|  \  / /| (    \/| (    )|             
    | |      | |   | |      |  (_/ / | (__    | (____)|             
    | |      | |   | |      |   _ (  |  __)   |     __)             
    | |      | |   | |      |  ( \ \ | (      | (\ (                
    | |   ___) (___| (____/\|  /  \ \| (____/\| ) \ \__             
    )_(   \_______/(_______/|_/    \/(_______/|/   \__/   

  ,------.          ,--.                       ,-----.       ,--.         
  |  .-.  \ ,--.,--.`--',--,--,  ,---. ,-----.'  .--./ ,---. `--',--,--,  
  |  |  \  :|  ||  |,--.|      \| .-. |'-----'|  |    | .-. |,--.|      \ 
  |  '--'  /'  ''  '|  ||  ||  |' '-' '       '  '--'\' '-' '|  ||  ||  | 
  `-------'  `----' `--'`--''--' `---'         `-----' `---' `--'`--''--'  
  
*/                                                               

//Includes-------------------------------------------|
#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <U8g2lib.h>
#include "heltec.h"
#include "images.h"

//Definitions-----------------------------------------|
#define FONT_ONE_HEIGHT               8                  // font one height in pixels
#define FONT_TWO_HEIGHT               20                 // font two height in pixels
#define ONBOARD_LED  25

//Screen Dimensions and type--------------------------|
U8G2_SSD1306_128X64_NONAME_F_HW_I2C     u8g2(U8G2_R0, 16, 15, 4);

//Constants and Variables----------------------------|
const char* ssid     = "NETGEAR39";     //Replace "<NETWORK_NAME>" with yours.
const char* password = "niftyjade691";  //Replace "<PASSWORD>" with yours.
char chBuffer[128];

//Setup----------------------------------------------|
void setup() {

  Serial.begin (115200);

  pinMode(ONBOARD_LED, OUTPUT);

//Anything that starts with HELTEC is related to the display.
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);

  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "Hello world");
  delay(100);
  Heltec.display->clear();
  
//Draws the IDML logo
  Heltec.display -> drawXbm(0, 0, IDML_width, IDML_height, IDMLlogo_bits);
  Heltec.display -> display();
  delay(2000);
  
//Draws the WiFI logo
  Heltec.display -> clear();
  Heltec.display -> drawXbm(0, 0, WIFI1_width, WIFI1_height, WIFI1logo_bits);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(50, 50, ssid);
  Heltec.display -> display();
  delay(500);
  Heltec.display->clear();

  Heltec.display -> clear();
  Heltec.display -> drawXbm(0, 0, WIFI2_width, WIFI2_height, WIFI2logo_bits);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(50, 50, ssid);
  Heltec.display -> display();
  delay(500);
  Heltec.display->clear();

  Heltec.display -> clear();
  Heltec.display -> drawXbm(0, 0, WIFI3_width, WIFI3_height, WIFI3logo_bits);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(50, 50, ssid);
  Heltec.display -> display();
  delay(500);
  Heltec.display->clear();

  Heltec.display -> clear();
  Heltec.display -> drawXbm(0, 0, WIFI4_width, WIFI4_height, WIFI4logo_bits);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(50, 50, ssid);
  Heltec.display -> display();
  delay(500);
  Heltec.display->clear();

  Serial.print("Connecting to Wifi");
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay (1250);
  }

// Oled Screen Startup 0.96-inch 128*64 dot matrix OLED.

  u8g2.begin();
  u8g2.setFont(u8g2_font_6x12_t_symbols);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);


  // Display Wifi Connecting to....

  //u8g2.clearBuffer();

  //u8g2.print("Connecting to Wifi: ", ssid);

  //u8g2.setCursor(0, 10);
  //u8g2.print("Connecting to WiFi");

  //u8g2.setCursor(0, 20);
  //u8g2.print(ssid);

  //u8g2.sendBuffer();

  //delay(2000);

  //u8g2.clearBuffer();

  //u8g2.setCursor(0, 0);
  //u8g2.print("Connected!");
  
  delay(500);

  u8g2.clearBuffer();

  sprintf(chBuffer, "%s", "WiFi Stats");
  u8g2.drawStr(64 - (u8g2.getStrWidth(chBuffer) / 2), 0, chBuffer);

//Display the SSID of the WiFi router.

  sprintf(chBuffer, "SSID: %s", ssid);
  u8g2.drawStr(0, FONT_ONE_HEIGHT * 3, chBuffer);


//Display the IP.

  char  chIp[81];
  WiFi.localIP().toString().toCharArray(chIp, sizeof(chIp) - 1);
  sprintf(chBuffer, "IP  : %s", chIp);
  u8g2.drawStr(0, FONT_ONE_HEIGHT * 2, chBuffer);


//Display the RSSI.

  sprintf(chBuffer, "RSSI: %d", WiFi.RSSI());
  u8g2.drawStr(0, FONT_ONE_HEIGHT, chBuffer);

  u8g2.sendBuffer();
  delay (5000);
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}

void loop() {

  if ((WiFi.status() == WL_CONNECTED))

  {
    HTTPClient http;
    http.begin ("https://api.coingecko.com/api/v3/simple/price?ids=bitcoin%2Cethereum&vs_currencies=eur%2Cgbp%2Cusd&include_24hr_change=true");
    int httpCode = http.GET();

    if (httpCode > 0) {

    }

    Serial.println ("\nStatuscode: " + String(httpCode));
    delay (100);

    const size_t capacity = JSON_OBJECT_SIZE(2) + 2 * JSON_OBJECT_SIZE(6) + 150;
    DynamicJsonDocument doc(capacity);
    String payload = http.getString();
    const char* json = payload.c_str();

    deserializeJson(doc, json);

    JsonObject bitcoin = doc["bitcoin"];
    float bitcoin_eur = bitcoin["eur"]; // 9473.3
    float bitcoin_eur_24h_change = bitcoin["eur_24h_change"]; // 11.379516678954898
    float bitcoin_gbp = bitcoin["gbp"]; // 8642.89
    float bitcoin_gbp_24h_change = bitcoin["gbp_24h_change"]; // 11.58637677393075
    float bitcoin_usd = bitcoin["usd"]; // 11140.6
    float bitcoin_usd_24h_change = bitcoin["usd_24h_change"]; // 12.464050392648252

    JsonObject ethereum = doc["ethereum"];
    float ethereum_eur = ethereum["eur"]; // 276.02
    float ethereum_eur_24h_change = ethereum["eur_24h_change"]; // 3.5689620753981264
    float ethereum_gbp = ethereum["gbp"]; // 251.82
    float ethereum_gbp_24h_change = ethereum["gbp_24h_change"]; // 3.7613159836416026
    float ethereum_usd = ethereum["usd"]; // 324.6
    float ethereum_usd_24h_change = ethereum["usd_24h_change"]; // 4.577442219792744

    Serial.println("-----------------Bitcoin-----------------");
    
    Serial.print("USD: ");
    Serial.println(bitcoin_usd);
    Serial.print("USD 24hr %: ");
    Serial.println(bitcoin_gbp_24h_change);
    Serial.println("-----------------");
    Serial.print("EUR: ");
    Serial.println(bitcoin_eur);
    Serial.print("EUR 24hr %: ");
    Serial.println(bitcoin_eur_24h_change);
    Serial.println("-----------------");
    Serial.print("GBP: ");
    Serial.println(bitcoin_gbp);
    Serial.print("GBP 24hr %: ");
    Serial.println(bitcoin_gbp_24h_change);

//Screen Outputs----------------------------|

    //u8g2.clearBuffer();

    //u8g2.setFont(u8g2_font_inb38_mf);


//Draws the BTC logo.
    Heltec.display -> clear();
    Heltec.display -> drawXbm(0, 0, BTC_width, BTC_height, BTClogo_bits);
    Heltec.display -> display();

    delay(5000);
    u8g2.begin();
    u8g2.setFont(u8g2_font_6x12_t_symbols);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(2);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);

//USD BTC
    u8g2.setCursor(40, 0);
    u8g2.print("Bitcoin ");
    u8g2.setCursor(0, 20);
    u8g2.print("USD: ");
    u8g2.print(bitcoin_usd, 0);
    u8g2.setCursor(0, 30);
    u8g2.print("USD: 24hr ");
    u8g2.print(bitcoin_usd_24h_change);
    u8g2.print(" %");
    u8g2.sendBuffer();
    
    delay(5000);
    u8g2.clearBuffer();
    u8g2.sendBuffer();

    Serial.println("-----------------Ethereum-----------------");

    Serial.print("USD: ");
    Serial.println(ethereum_usd);
    Serial.print("USD 24hr %: ");
    Serial.println(ethereum_usd_24h_change);
    Serial.println("-----------------");
    Serial.print("EUR: ");
    Serial.println(ethereum_eur);
    Serial.print("EUR 24hr %: ");
    Serial.println(ethereum_eur_24h_change);
    Serial.println("-----------------");
    Serial.print("GBP: ");
    Serial.println(ethereum_gbp);
    Serial.print("GBP 24hr %: ");
    Serial.println(ethereum_gbp_24h_change);

    Serial.println("-------------------------------");
    
//Draws the ETH logo.
    Heltec.display -> clear();
    Heltec.display -> drawXbm(0, 0, ETH_width, ETH_height, ETHlogo_bits);
    Heltec.display -> display();

    delay(5000);
    u8g2.begin();
    u8g2.setFont(u8g2_font_6x12_t_symbols);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(3);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);

//USD ETH
    u8g2.setCursor(40, 0);
    u8g2.print("Ethereum ");
    u8g2.setCursor(0, 20);
    u8g2.print("USD: ");
    u8g2.print(ethereum_usd, 0);
    u8g2.setCursor(0, 30);
    u8g2.print("USD: 24hr ");
    u8g2.print(ethereum_usd_24h_change);
    u8g2.print(" %");
    u8g2.sendBuffer();
    
    delay(5000);
    u8g2.clearBuffer();  
      
    http.end();
    u8g2.sendBuffer();
  }
  
//DUCO
  if ((WiFi.status() == WL_CONNECTED))

  {
    HTTPClient http;
    http.begin ("https://server.duinocoin.com/users/robertbrann18?ids=%2Cbalance%2Cusername=true"); //Replace "<USERNAME>" with your Duino-Coin Username.
    int httpCode = http.GET();

    if (httpCode > 0) {

    }

    Serial.println ("\nStatuscode: " + String(httpCode));
    delay (100);

    const size_t capacity = JSON_OBJECT_SIZE(2) + 2 * JSON_OBJECT_SIZE(6) + 150;
    DynamicJsonDocument doc(capacity);
    String payload = http.getString();
    const char* json = payload.c_str();

    deserializeJson(doc, json);
    JsonObject duinocoin = doc["result"]["balance"];
    float duco_balance = duinocoin["balance"]; //
    const char* duco_user = duinocoin["username"]; //

    Serial.println("-------------------------------");
    Serial.print("Username: ");
    Serial.println(duco_user);
    Serial.print("DUCO Balance: ");
    Serial.println(duco_balance);
    Serial.println("-------------------------------");
    
//Draws the DUCO logo.
    Heltec.display -> clear();
    Heltec.display -> drawXbm(0, 0, DUCO_width, DUCO_height, DUCOlogo_bits);
    Heltec.display -> display();

    delay(5000);
    u8g2.begin();
    u8g2.setFont(u8g2_font_6x12_t_symbols);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(3);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);

    u8g2.setCursor(35, 0);
    u8g2.print("Duino-Coin ");

    u8g2.setCursor(0, 20);
    //u8g2.print("Username: ");
    u8g2.print(duco_user);
    u8g2.setCursor(0, 30);
    u8g2.print("Balance: ");
    u8g2.print(duco_balance);
    
    u8g2.sendBuffer();
    delay(10000);
    u8g2.clearBuffer();

    http.end();
    u8g2.sendBuffer();
  }
}

//Uncomment and replace to your preference.

/*

//EUR BTC
    u8g2.setCursor(40, 0);
    u8g2.print("Bitcoin ");
    u8g2.setCursor(0, 20);
    u8g2.print("GBP: ");
    u8g2.print(bitcoin_gbp, 0);
    u8g2.setCursor(0, 30);
    u8g2.print("GBP: 24hr ");
    u8g2.print(bitcoin_gbp_24h_change);
    u8g2.print(" %");
    
//EUR ETH
    u8g2.setCursor(40, 0);
    u8g2.print("Ethereum ");
    u8g2.setCursor(0, 20);
    u8g2.print("EUR: ");
    u8g2.print(ethereum_eur, 0);
    u8g2.setCursor(0, 30);
    u8g2.print("EUR: 24hr ");
    u8g2.print(ethereum_eur_24h_change);
    u8g2.print(" %");

//GBP BTC
    u8g2.setCursor(40, 0);
    u8g2.print("Bitcoin ");
    u8g2.setCursor(0, 20);
    u8g2.print("GBP: ");
    u8g2.print(bitcoin_gbp, 0);
    u8g2.setCursor(0, 30);
    u8g2.print("GBP: 24hr ");
    u8g2.print(bitcoin_gbp_24h_change);
    u8g2.print(" %");
    
//GBP EUR
    u8g2.setCursor(40, 0);
    u8g2.print("Ethereum ");
    u8g2.setCursor(0, 20);
    u8g2.print("GBP: ");
    u8g2.print(ethereum_gbp, 0);
    u8g2.setCursor(0, 30);
    u8g2.print("GBP: 24hr ");
    u8g2.print(ethereum_gbp_24h_change);
    u8g2.print(" %");
*/
