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
    State_struct state;
    Adafruit_NeoPixel pixels;
    int interval;

  public:
    NeopixelFlasher(int numpixels, int pin, int intervalOfLight ) {
      pixels = Adafruit_NeoPixel(numpixels, pin, NEO_GRB + NEO_KHZ800);
      interval = intervalOfLight;
      pixels.begin();
      state = {0, 0, 0, 0, 0};
    }

    void Update() {
      unsigned long currentMillis = millis();
      if (currentMillis - state.previousMillis > interval) {
        pixels.setPixelColor(state.simplePixelIndex, pixels.Color(0, 150, 0));
        pixels.show();
        state.simplePixelIndex = state.simplePixelIndex + 1;
        if (state.simplePixelIndex >= pixels.numPixels()) {
          state.simplePixelIndex = 0;
          pixels.clear();
        }
        state.previousMillis = currentMillis;
      }
    }

    void UpdateRainbow() {
      unsigned long currentMillis = millis();
      if (currentMillis - state.previousMillis > interval) {
        pixels.rainbow(state.rainbowHSVcolor) ;
        pixels.show();
        state.rainbowHSVcolor += 256;
        if (state.rainbowHSVcolor >= 65536) {
          state.rainbowHSVcolor  = 0;
        }
        state.previousMillis = currentMillis;
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
      if (currentMillis - state.previousMillis > interval) {
        for (int i = 0; i < pixels.numPixels(); i = i + GAP_BETWEEN_LIGHTS) {
          pixels.setPixelColor(i + state.theaterStep, Wheel( (i + state.theaterColorWheel) % 255)); //turn every third pixel on
        }
        pixels.show();
        for (int i = 0; i < pixels.numPixels(); i = i + GAP_BETWEEN_LIGHTS) {
          pixels.setPixelColor(i + state.theaterStep, 0); //turn every third pixel off
        }
        state.theaterColorWheel++ ;
        state.theaterStep++;
        if (state.theaterColorWheel >= 256) {
          state.theaterColorWheel  = 0;
        }
        if (state.theaterStep >= GAP_BETWEEN_LIGHTS) {
          state.theaterStep  = 0;
        }

        state.previousMillis = currentMillis;
      }

    }

};
