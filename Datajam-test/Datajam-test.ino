#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    32
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  100


void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
uint8_t gHue = 150; // rotating "base color" used by many of the patterns

uint8_t pos1 = 16; 
uint8_t pos2 = 0;

int moduloclock(int argi, int adj)
{ argi += 1;
  return(argi % 16 + adj); 
}

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  sinelon();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 200 ) { gHue += 10; } // slowly cycle the "base color" through the rainbow
  EVERY_N_MILLISECONDS( 600 ) { pos1 = moduloclock(pos1, 16); }
  EVERY_N_MILLISECONDS( 300 ) { pos2 = moduloclock(pos2, 0); }
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void sinelon(){
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds,NUM_LEDS, 10);
  
  leds[pos1] += CHSV( gHue, 255, 192);
  leds[pos2] += CHSV( gHue, 255, 192);
}


