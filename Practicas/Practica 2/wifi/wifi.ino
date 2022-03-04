/** 
 * Author: MrFrenzoid 
 * Date: 04/03/2022
 * Device: Arduino NANO 33 IoT With headers.
 * Libraries: WiFiNINA
 */

#include <WiFiNINA.h>

// SSID and PASSWORD
#define SSID        "arduino"
#define PASSWORD    "okokokok"


// Wifi retryies counter.
int retrycount = 0;

// wifi staus, used to stuff once connected once.
bool connected = false;


void setup() {
  // setup serial output
  Serial.begin(9600);
  
  // Setup leds
  pinMode(LED_BUILTIN, OUTPUT);

  // Turn led on on start.
  led_on();

  // Try connecting to wifi.
  wifi_connect();
}

void loop() {
  /** If the device is not connected to the wifi network,
   *  blink the led and try to connect,
   *  and if it succesfully connects, turn the led off.
   */
  if (WiFi.status() != WL_CONNECTED) {
    if(connected == true) {
      Serial.println("Connection lost!, retrying...");
      connected = false;
    }
    
    retrycount += 1;
    led_blink(1000);
    wifi_connect();

    if ( retrycount == 5) Serial.println("Error connecting to wifi network " + (String)SSID + " after 5 tries, still retrying...");
  } else {
    if (!connected) {
      
      connected = true;
      retrycount = 0;
      led_off();
      Serial.println("Wifi connected succefully!");
      
    }
  }
}

void wifi_connect() {
    WiFi.begin(SSID, PASSWORD);
}

void led_on() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void led_off() {
  digitalWrite(LED_BUILTIN, LOW);
}

void led_blink(int del) {
  led_on();
  delay(del);
  led_off();
}
