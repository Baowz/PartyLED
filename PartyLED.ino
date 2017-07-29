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

#define DATA_PIN           3
#define OPEN_PIN           A0
#define LED_TYPE           WS2812B
#define COLOR_ORDER        GRB
#define NUM_LEDS           1014
CRGB leds[NUM_LEDS];
#define FRAMES_PER_SECOND  120
#define BRIGHTNESS         255

void setup() 
{
  delay(3000);

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  randomSeed(analogRead(OPEN_PIN));
    
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
    for(int i=0; i <= NUM_LEDS; i++) 
    {
      leds[i] = CRGB::Black;
    }
    int speedLED = 15;
    int whiteLED = random(0,NUM_LEDS);
    int whiteLED_initial = whiteLED;
    int whiteLED_diff = 0; 
    int decrease_speed = random(0, NUM_LEDS-speedLED);
    float counter = 0;
    
    while(speedLED > 0)
    {
    int r   = (sin(counter/100)+1)*(255/2); //rotates colors.
    int g   = (sin(counter/100 + 3.14*4/3)+1)*(255/2);
    int b   = (sin(counter/100 + 3.14*2/3)+1)*(255/2);
    
      leds[whiteLED] = CRGB(r, g, b);
      counter += 1.2;
      FastLED.show();
      leds[whiteLED] = CRGB::Black;
      if(((whiteLED-whiteLED_initial)+NUM_LEDS)%NUM_LEDS > decrease_speed)
      { 
        speedLED--;
        whiteLED_initial = whiteLED; 
        decrease_speed = random(0, (NUM_LEDS/4)+speedLED*20);
      }
      whiteLED = (whiteLED+speedLED)%NUM_LEDS;
    }  
    for(int j=0; j < 11; j++)
    {
      for(int i=0; i <= NUM_LEDS; i++) 
      {
        leds[i] = CRGB::Red;
      }
      leds[whiteLED] = CRGB::Black;
      FastLED.show();
      delay(500);
      for(int k=0; k <= NUM_LEDS; k++) 
      {
        leds[k] = CRGB::Black;
      }
      leds[whiteLED] = CRGB::White;
      FastLED.show();
      delay(500);
    }
    delay(5000);
    state = 3;
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
  }
  else if (state == 2)
  {
    for(int i=0; i <= NUM_LEDS; i++) 
    {
      leds[i] = CRGB::White;
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
