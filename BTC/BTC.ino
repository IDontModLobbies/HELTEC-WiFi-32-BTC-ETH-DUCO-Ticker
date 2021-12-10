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

  Serial.print("Connecting to WiFi");
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
    delay (1000);

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

//Draws the BTC logo.
    String BTC_USD = "$" + (String)bitcoin_usd;
    String BTC_USD24H = "24hr: " + (String)bitcoin_usd_24h_change + "%";
    Heltec.display -> clear();
    Heltec.display -> drawXbm(0, 0, BTC_width, BTC_height, BTClogo_bits);
    Heltec.display -> display();

    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(40, 0, "Bitcoin");
    Heltec.display->drawString(40, 20, BTC_USD);
    Heltec.display->drawString(40, 30, BTC_USD24H);
    Heltec.display -> display();
    delay(5000);
    Heltec.display->clear();
  

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
    String ETH_USD = "$" + (String)ethereum_usd;
    String ETH_USD24H = "24hr: " + (String)ethereum_usd_24h_change + "%";
    Heltec.display -> clear();
    Heltec.display -> drawXbm(0, 0, ETH_width, ETH_height, ETHlogo_bits);
    Heltec.display -> display();

    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(40, 0, "Ethereum (USD)");
    Heltec.display->drawString(40, 20, ETH_USD);
    Heltec.display->drawString(40, 30, ETH_USD24H);
    Heltec.display -> display();
    delay(5000);
    Heltec.display->clear();
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
    float duco_bal = duinocoin["balance"]; //
    const char* duco_user = duinocoin["username"]; //

    Serial.println("-------------------------------");
    Serial.print("Username: ");
    Serial.println(duco_user);
    Serial.print("DUCO Balance: ");
    Serial.println(duco_bal);
    Serial.println("-------------------------------");
    
//Draws the DUCO logo.
    String DUCO_USERNAME = (String)duco_user;
    String DUCO_BALANCE = "Balance: " + (String)duco_bal;
    Heltec.display -> clear();
    Heltec.display -> drawXbm(0, 0, DUCO_width, DUCO_height, DUCOlogo_bits);
    Heltec.display -> display();

    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(40, 0, "Duino-Coin");
    Heltec.display->drawString(40, 20, DUCO_USERNAME);
    Heltec.display->drawString(40, 30, DUCO_BALANCE);
    Heltec.display -> display();
    delay(5000);
    Heltec.display->clear();
  }
}

//Replace to your preference.

/*

//EUR BTC
    String BTC_EUR = "€" + (String)bitcoin_eur;
    String BTC_USD24H = "24hr: " + (String)bitcoin_eur_24h_change + "%";
    Heltec.display -> clear();
    Heltec.display -> drawXbm(0, 0, BTC_width, BTC_height, BTClogo_bits);
    Heltec.display -> display();

    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(40, 0, "Bitcoin (EUR)");
    Heltec.display->drawString(40, 20, BTC_EUR);
    Heltec.display->drawString(40, 30, BTC_EUR24H);
    Heltec.display -> display();
    delay(5000);
    Heltec.display->clear();
    
//EUR ETH
    String ETH_EUR = "€" + (String)ethereum_eur;
    String ETH_EUR24H = "24hr: " + (String)ethereum_eur_24h_change + "%";
    Heltec.display -> clear();
    Heltec.display -> drawXbm(0, 0, ETH_width, ETH_height, ETHlogo_bits);
    Heltec.display -> display();

    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(40, 0, "Ethereum (EUR)");
    Heltec.display->drawString(40, 20, ETH_EUR);
    Heltec.display->drawString(40, 30, ETH_EUR24H);
    Heltec.display -> display();
    delay(5000);
    Heltec.display->clear();

//GBP BTC
    String BTC_GBP = (String)bitcoin_gbp;
    String BTC_GBP24H = "24hr: " + (String)bitcoin_gbp_24h_change + "%";
    Heltec.display -> clear();
    Heltec.display -> drawXbm(0, 0, BTC_width, BTC_height, BTClogo_bits);
    Heltec.display -> display();

    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(40, 0, "Bitcoin");
    Heltec.display->drawString(40, 20, BTC_GBP);
    Heltec.display->drawString(40, 30, BTC_GBP24H);
    Heltec.display -> display();
    delay(5000);
    Heltec.display->clear();
    
//GBP EUR
    String ETH_GBP = (String)ethereum_gbp;
    String ETH_GBP24H = "24hr: " + (String)ethereum_gbp_24h_change + "%";
    Heltec.display -> clear();
    Heltec.display -> drawXbm(0, 0, ETH_width, ETH_height, ETHlogo_bits);
    Heltec.display -> display();

    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(40, 0, "Ethereum (USD)");
    Heltec.display->drawString(40, 20, ETH_GBP);
    Heltec.display->drawString(40, 30, ETH_GBP24H);
    Heltec.display -> display();
    delay(5000);
    Heltec.display->clear();
  
*/
