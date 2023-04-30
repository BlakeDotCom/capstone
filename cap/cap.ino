#include <FastLED.h>
#include <PS2Keyboard.h>

const int DataPin = 8;
const int IRQpin =  5;
PS2Keyboard keyboard;

#define NUM_LEDS 60       // ??
#define DATA_PIN 2
#define COLOR_ORDER RGB
#define CHIPSET WS2812B //maybe??
#define BRIGHTNESS 60   // 0-255
#define VOLTAGE 5
#define MAX_AMPS 500    //in mA

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<CHIPSET,DATA_PIN,COLOR_ORDER>(leds,NUM_LEDS);
  FastLED.setMaxPowerInVoltsaAndMilliamps(VOLTAGE,MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  keyboard.begin(DataPin, IRQpin, PS2Keymap_US);
 
  //testing code remove after done testing 
  Serial.begin(9600);
  Serial.println("International Keyboard Test:");
   //testing code remove after done testing 
}

void loop() {
  if (keyboard.available()) {
    char c = keyboard.read();
   }
  Serial.print(c);

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