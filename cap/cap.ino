
#include <FastLED.h>
#define CLOCK 6 //D-
#define DATA 7  //D+
#define NUM_LEDS 60       // ??
#define DATA_PIN 2
#define COLOR_ORDER RGB
#define CHIPSET WS2812B //maybe??
#define BRIGHTNESS 60   // 0-255
#define VOLTAGE 5
#define MAX_AMPS 500    //in mA

CRGB leds[NUM_LEDS];
String barcodeData = "";
bool dataComplete = false;

void setup() {
  delay(1000);
  FastLED.addLeds<CHIPSET,DATA_PIN,COLOR_ORDER>(leds,NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE,MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  Serial.begin(9600);
  attachInterrupt(CLOCK, scan, FALLING);
}
uint8_t lastscan;

void scan() {
  volatile int scanval = 0;
  for(int i = 0; i<11; i++)
  {
    while(digitalRead(CLOCK));
    scanval |= digitalRead(DATA) << i;
    while(!digitalRead(CLOCK));
  }
  scanval = (scanval>>1) & 255;
  Serial.println(scanval);
  lastscan = scanval;
}
void loop() {
  
  
}
// 1 blue success, 2 red fail, 3 Green charge, else off
void setLEDS(int color) {
  for(int i = 0; i<NUM_LEDS; i++){
    leds[i] = (color == 1) ? CRGB::Blue
              :(color == 2) ? CRGB::Red
              :(color == 3) ? CRGB::Green
              : CRGB(0,0,0);
  }
  FastLED.show();
}