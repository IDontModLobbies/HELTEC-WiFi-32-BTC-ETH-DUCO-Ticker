
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


Make sure you replace the following in order for code to work.

const char* ssid     = "<NETWORK_NAME>";     //Replace "<NETWORK_NAME>" with yours.
const char* password = "<PASSWORD>";         //Replace "<PASSWORD>" with yours.

http.begin ("https://server.duinocoin.com/users/<USERNAME>?ids=%2Cbalance%2Cusername=true");        //Replace "<USERNAME>" with your Duino-Coin Username.
