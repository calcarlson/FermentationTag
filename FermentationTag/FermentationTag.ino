#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
//#include "Adafruit_SSD1306.h"
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>

//
//
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 OLED(OLED_RESET);
//
#define DHTPIN D3
#define DHTTYPE DHT22
DHTesp dht;

void setup() {
OLED.begin();
OLED.clearDisplay();

Serial.begin(115200);
pinMode(DHTPIN,INPUT);
pinMode(2,OUTPUT);
dht.setup(DHTPIN,DHTesp::DHT22);
////display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
////OLED.begin(SSD1306_SWITCHAPVCC,0x3c);
////display.display();
}

void loop() {
digitalWrite(2, !digitalRead(2));
delay(dht.getMinimumSamplingPeriod());
OLED.setTextSize(1);
OLED.setTextColor(WHITE,BLACK);
OLED.setCursor(0,0);
OLED.display();


  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  //OLED.println(dht.getStatusString());
  OLED.println("   Temp.");
  OLED.print("  ");
  OLED.setTextSize(2);
  OLED.println(dht.toFahrenheit(temperature), 1);
  OLED.setTextSize(1);
  OLED.println(" Humidity");
  OLED.print("  ");
  OLED.setTextSize(2);
  OLED.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
   delay(100);
}
