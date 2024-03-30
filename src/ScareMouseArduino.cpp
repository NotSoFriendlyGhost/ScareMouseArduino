#include <Arduino.h>
#include <avr/wdt.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HX711.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

HX711 scale;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int loadCell = A0;
bool notStarted = 1;
int startPin = 8;
int samplingRate = 100;
int pixelLocation = 1;
int startSample, endSample;
bool firstSample = true;
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

void setup() {
  // put your setup code here, to run once:
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(452.17);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Welcome to ScareMouse! Press the button to continue.");
  display.display();
  pinMode(startPin, INPUT);
  wdt_disable();
  wdt_enable(WDTO_1S);
  while (notStarted) {
    if (digitalRead(startPin) == HIGH) {
      notStarted = 0;
    }
    wdt_reset();
  }
  Serial.begin(9600);
  display.clearDisplay();
  display.setCursor(0, 50);
  display.println("Collecting...");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.read() == 'R') {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Done collecting. Press button again to reset.");
    display.display();
    while (digitalRead(startPin) == LOW) {
      wdt_reset();
    }
    while (1);
  }
  delay(1000 / samplingRate);
  int sample = scale.get_units();//analogRead(loadCell);
  Serial.println(sample);  //data
  if (firstSample) startSample = sample;
  else endSample = sample;
  if (pixelLocation <= 128 && !firstSample) {
    //display.drawPixel(pixelLocation, 32-sample/10, SSD1306_WHITE);
    display.drawLine(pixelLocation - 1, 32 - startSample, pixelLocation, 32 - endSample, WHITE);
    display.display();
  } else {
    display.clearDisplay();
    display.setCursor(0, 50);
    display.println("Collecting...");
    pixelLocation = 1;
  }
  startSample = endSample;
  firstSample = false;
  pixelLocation++;
  wdt_reset();
}
