
#include "FastLED.h"

FASTLED_USING_NAMESPACE

int Knapp1 = 2;
int LED1 = 4;
int Knapp2 = 6;
int LED2 = 8;
int Knapp3 = 10;
int LED3 = 12;
int reading1;
int reading2;
int reading3;
int state;

#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    1014
CRGB leds[NUM_LEDS];
#define FRAMES_PER_SECOND  120

#define BRIGHTNESS          250
void setup() 
{
  delay(3000);

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
    
  Serial.begin(9600);
  pinMode(Knapp1, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(Knapp2, INPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Knapp3, INPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(Knapp1, LOW);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  reading1 = digitalRead(Knapp1);
  reading2 = digitalRead(Knapp2);
  reading3 = digitalRead(Knapp3);
  uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
  uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  int maks = 5;
  if(reading1 == HIGH)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    state = 1;
  }
  else if (reading2 == HIGH)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    state = 2;
  }
  else if(reading3 == HIGH)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    state = 3;
  }
  if (state == 1)
  {
    for(int i=0; i <= NUM_LEDS; i++) 
    {
      leds[i] = CRGB::Red;
    }
  }
  else if (state == 2)
  {
    for(int i=0; i <= NUM_LEDS; i++) 
    {
      leds[i] = CRGB::Blue;
    }
  }
  else if (state == 3)
  {
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    for( int i = 0; i < NUM_LEDS; i++) //9948
    { 
      leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    }
  }
  FastLED.show();
  Serial.println(state);
}

