#include <Adafruit_NeoPixel.h>

#define GAP_BETWEEN_LIGHTS 3

struct State_struct {
  unsigned long previousMillis;
  int simplePixelIndex;
  uint32_t rainbowHSVcolor;
  int theaterColorWheel;
  byte theaterStep;
};


class NeopixelFlasher {
    State_struct pixelsState;
    Adafruit_NeoPixel pixels;
    int interval;

  public:
    NeopixelFlasher(int numpixels, int pin, int intervalOfLight ) {
      pixels = Adafruit_NeoPixel(numpixels, pin, NEO_GRB + NEO_KHZ800);
      interval = intervalOfLight;
      pixels.begin();
      pixelsState = {0, 0, 0, 0, 0};
    }

    void Update() {
      unsigned long currentMillis = millis();
      if (currentMillis - pixelsState.previousMillis > interval) {
        pixels.setPixelColor(pixelsState.simplePixelIndex, pixels.Color(0, 150, 0));
        pixels.show();
        pixelsState.simplePixelIndex = pixelsState.simplePixelIndex + 1;
        if (pixelsState.simplePixelIndex >= pixels.numPixels()) {
          pixelsState.simplePixelIndex = 0;
          pixels.clear();
        }
        pixelsState.previousMillis = currentMillis;
      }
    }

    void UpdateRainbow() {
      unsigned long currentMillis = millis();
      if (currentMillis - pixelsState.previousMillis > interval) {
        pixels.rainbow(pixelsState.rainbowHSVcolor) ;
        pixels.show();
        pixelsState.rainbowHSVcolor += 256;
        if (pixelsState.rainbowHSVcolor >= 65536) {
          pixelsState.rainbowHSVcolor  = 0;
        }
        pixelsState.previousMillis = currentMillis;
      }
    }


    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos) {
      uint32_t packedRGB;
      WheelPos = 255 - WheelPos;
      // Serial.print("Wheel= ");
      if (WheelPos < 85) {
        packedRGB = pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
        // return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
      }
      if (WheelPos < 170) {
        WheelPos -= 85;
        packedRGB = pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
        // return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
      }
      if (WheelPos >= 170)  {
        WheelPos -= 170;
        packedRGB = pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        // return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
      }
      // Serial.println(packedRGB);
      return packedRGB;
    }

    //Theatre-style crawling lights with rainbow effect
    void UpdateTheaterRainbow() {
      unsigned long currentMillis = millis();
      if (currentMillis - pixelsState.previousMillis > interval) {
        for (int i = 0; i < pixels.numPixels(); i = i + GAP_BETWEEN_LIGHTS) {
          pixels.setPixelColor(i + pixelsState.theaterStep, Wheel( (i + pixelsState.theaterColorWheel) % 255)); //turn every third pixel on
        }
        pixels.show();
        for (int i = 0; i < pixels.numPixels(); i = i + GAP_BETWEEN_LIGHTS) {
          pixels.setPixelColor(i + pixelsState.theaterStep, 0); //turn every third pixel off
        }
        pixelsState.theaterColorWheel++ ;
        pixelsState.theaterStep++;
        if (pixelsState.theaterColorWheel >= 256) {
          pixelsState.theaterColorWheel  = 0;
        }
        if (pixelsState.theaterStep >= GAP_BETWEEN_LIGHTS) {
          pixelsState.theaterStep  = 0;
        }

        pixelsState.previousMillis = currentMillis;
      }

    }

};
