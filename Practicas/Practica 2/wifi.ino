#include <WiFiNINA.h>

#define SSID        "nombre wifi"
#define PASSWORD    "contraseña"

byte mac[6];

void Wifi_ON() {
    Serial.println("Connecting to wifi... ");

    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        // delay(1000)
    }

    Serial.println("WiFi Connected!");
    WiFi.macAddress(mac);
    Seria.print("MAC: ");
    printMacAddress(mac);
}

void printMacAddress(byte mac[]) {
    for(int i = 5; i >=0; i--){
        if (mac[i] < 16) Serial.print("0");
        Serial.print(mac[i], HEX);
        if( i > 0 ) Serial.print(":");
    }
    
    Serial.println();
}