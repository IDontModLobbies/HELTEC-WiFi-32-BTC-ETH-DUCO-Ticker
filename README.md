BTC & ETH Ticker
Duino-Coin Balance
     for 
HELTEC WiFi 32 


IDontModLobbies
WiFi Boot Logo

Displays BTC
Price
Percentage change in the past 24 hrs.

Displays ETH
Price
Percentage change in the past 24 hrs.

Displays Duino-Coin
Username
Balance


Install Heltec ESP32 Dev-boards library. 
Click Sketch on the top of the program, hover on the Include Library field and click the Manage Libraries... entry.
In the search box type Heltec ESP32 Dev-boards - a package by Heltec should come up. Install the newest version.
When the library finishes installing you can click the Close button.


Make sure you replace the following in order for code to work.
Replace "<NETWORK_NAME>" with yours.
const char* ssid     = "<NETWORK_NAME>";

Replace "<PASSWORD>" with yours.
const char* password = "<PASSWORD>";         

Replace "<USERNAME>" with your Duino-Coin Username.
http.begin ("https://server.duinocoin.com/users/<USERNAME>?ids=%2Cbalance%2Cusername=true");    