#include "FastLED.h"

FASTLED_USING_NAMESPACE

int Button1 =  2;
int LED1   =  4;
int Button2 =  6;
int LED2   =  8;
int Button3 = 10;
int LED3   = 12;
int reading1;
int reading2;
int reading3;
int state;

#define DATA_PIN            3
#define LED_TYPE           WS2812B
#define COLOR_ORDER        GRB
#define NUM_LEDS           1014
CRGB leds[NUM_LEDS];
#define FRAMES_PER_SECOND  120
#define BRIGHTNESS         250

void setup() 
{
  delay(3000);

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
    
  Serial.begin(9600);
  pinMode(Button1, INPUT);
  pinMode(LED1,  OUTPUT);
  pinMode(Button2, INPUT);
  pinMode(LED2,  OUTPUT);
  pinMode(Button3, INPUT);
  pinMode(LED3,  OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  reading1 = digitalRead(Button1);
  reading2 = digitalRead(Button2);
  reading3 = digitalRead(Button3);
  uint8_t gHue = 0;                  // rotating "base color" used by many of the patterns
  
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
    int speedLED = 15;
    int whiteLED = random(0,NUM_LEDS);
    int whiteLED_initial = whiteLED;
    int whiteLED_diff = 0; 
    int decrease_speed = random(0, NUM_LEDS);
    while(speedLED > 0)
    {
      leds[whiteLED] = CRGB::White;
      FastLED.show();
      leds[whiteLED] = CRGB::Black;
       
      if(((whiteLED-whiteLED_initial)+NUM_LEDS)%NUM_LEDS > decrease_speed)
      { 
        speedLED--;
        whiteLED_initial = whiteLED; 
        //decrease_speed = random(0, NUM_LEDS);
      }

      whiteLED = (whiteLED+speedLED)%NUM_LEDS;
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

