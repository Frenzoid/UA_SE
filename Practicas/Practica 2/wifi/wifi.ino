/** 
 * Author: MrFrenzoid 
 * Date: 04/03/2022
 * Libraries: WiFiNINA
 */

#include <WiFiNINA.h>

// SSID and PASSWORD
#define SSID        "arduino"
#define PASSWORD    "okokokok"

void setup() {
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
      led_blink(1000);
      wifi_connect();
  } else led_off();
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
