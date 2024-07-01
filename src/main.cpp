#include <Arduino.h>
#include <GyverPortal.h>
#include <FastLED.h>
#include "WiFi.h"
#include "Math.h"

// Global variables
#define LED_PIN 26
#define LED_COUNT 180
#define AP_SSID "Alien"
#define AP_PASS "bezparolianehodi"

// FastLED
struct CRGB leds[LED_COUNT];

int eff_index;
bool power = true;
int BRIGHT;
float SPEED = 20;
int STEP = 20;
int ihue = 0;
int thissat = 255;
unsigned long lastmillis = 0;
GPcolor rgb(0, 0, 0);

int currentEffect = 0;

GyverPortal ui;

// Список эффектов
String effects[6] = {
    "Static",
    "Rainbow LOOP",
    "Rainbow Fade",
    "Rainbow Cycle",
    "Fire",
    ""};

void oneColorAll()
{ //-SET ALL LEDS TO ONE COLOR
  for (int i = 0; i < LED_COUNT; i++)
  {
    leds[i].setRGB(rgb.r, rgb.g, rgb.b);
  }
  FastLED.setBrightness(BRIGHT);
  FastLED.show();
}

void clearLED()
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    leds[i].setRGB(0, 0, 0);
  }
  FastLED.setBrightness(0);
  FastLED.show();
}

void rainbowFade()
{ //-m2-FADE ALL LEDS THROUGH HSV RAINBOW
  if (lastmillis + SPEED < millis() && power)
  {
    ihue++;
    if (ihue > 255)
    {
      ihue = 0;
    }
    for (int idex = 0; idex < LED_COUNT; idex++)
    {
      leds[idex] = CHSV(ihue, thissat, 255);
    }
    LEDS.setBrightness(BRIGHT);
    LEDS.show();
    lastmillis = millis();
  }
}

void rainbowLoop()
{ //-m3-LOOP HSV RAINBOW
  if (lastmillis + SPEED < millis() && power)
  {
    for(int idex = 0; idex < LED_COUNT; idex++){
      ihue = ihue + STEP;

      if (ihue > 255)
      {
        ihue = 0;
      }
        leds[idex] = CHSV(ihue, thissat, 255);

      FastLED.setBrightness(BRIGHT);
      FastLED.show();
      lastmillis = millis();
    }
  }
}

void rainbowCycle(){
  byte r, g, b;
  if(lastmillis + 500 < millis() && power){
    for(uint16_t i = 0; i < 256 * 2; i++){
      for(uint16_t j = 0; j < LED_COUNT; j++){
        byte WheelPos = ((j * 256 / LED_COUNT) + i) & 255;
        if(WheelPos < 85){
          r = WheelPos * 3;
          g = 255 - WheelPos * 3;
          b = 0;
        }else if(WheelPos < 170){
          r = 255 - WheelPos * 3;
          g = 0;
          b = WheelPos * 3;
        }else{
          r = 0;
          g = WheelPos * 3;
          b = 255 - WheelPos * 3;
        }
        leds[j].setRGB(r, g, b);
      }
       FastLED.show();
    }
    FastLED.setBrightness(BRIGHT);
    lastmillis = millis();
  }
}

void Fire(){
  if(lastmillis + SPEED < millis() && power){
    int temprand;
      for (int i = 0; i < LED_COUNT; i++ ) {
        temprand = random(100, 255);
        leds[i].r = temprand;
        leds[i].b = 0; leds[i].g = 30;
      }
      LEDS.show();
    FastLED.setBrightness(BRIGHT);
    lastmillis = millis();
  }
};

// конструктор страницы
void build(GyverPortal &p)
{
  GP.BUILD_BEGIN(GP_DARK);
  GP.PAGE_TITLE("ESPLight");

  GP.TITLE("ESPLight");
  GP.BREAK();

  GP.BLOCK_BEGIN("Effect");
  GP.SPAN("Effect:");
  GP.SELECT("Eff_SEL", effects, eff_index, true, 0, 0);
  GP.RELOAD_CLICK("Eff_SEL");
  GP.BLOCK_END();
  GP.BREAK();

  GP.BLOCK_BEGIN("Settings");
  GP.TITLE("Settings");
  GP.SPAN(effects[eff_index]);
  GP.BREAK();
  switch (eff_index)
  {
  case 0:
    GP.BOX_BEGIN();
    GP.SPAN("POWER:");
    GP.SWITCH("POWER", power);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("RGB:");
    GP.COLOR("RGB", rgb);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("Brightness:");
    GP.SLIDER("BRIGHT", BRIGHT, 0, 255);
    GP.BOX_END();
    break;
  case 1:
    GP.BOX_BEGIN();
    GP.SPAN("POWER:");
    GP.SWITCH("POWER", power);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("Brightness:");
    GP.SLIDER("BRIGHT", BRIGHT, 0, 255);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("Speed:");
    GP.SLIDER("SPEED", SPEED, 0, 100, 2);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("Step:");
    GP.SLIDER("STEP", STEP, 0, LED_COUNT);
    GP.BOX_END();

    break;
  case 2:
    GP.BOX_BEGIN();
    GP.SPAN("POWER:");
    GP.SWITCH("POWER", power);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("Brightness:");
    GP.SLIDER("BRIGHT", BRIGHT, 0, 255);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("Speed:");
    GP.SLIDER("SPEED", SPEED, 0, 100, 2);
    GP.BOX_END();
    break;
  case 3:
    GP.BOX_BEGIN();
    GP.SPAN("POWER:");
    GP.SWITCH("POWER", power);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("Brightness:");
    GP.SLIDER("BRIGHT", BRIGHT, 0, 255);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("Speed:");
    GP.SLIDER("SPEED", SPEED, 0, 100, 2);
    GP.BOX_END();
    break;
  case 4:
    GP.BOX_BEGIN();
    GP.SPAN("POWER:");
    GP.SWITCH("POWER", power);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("Brightness:");
    GP.SLIDER("BRIGHT", BRIGHT, 0, 255);
    GP.BOX_END();
    GP.BOX_BEGIN();
    GP.SPAN("Speed:");
    GP.SLIDER("SPEED", SPEED, 0, 100, 2);
    GP.BOX_END();
    break;
  default:
    break;
  }

  GP.BLOCK_END();
  GP.BREAK();
  GP.BUILD_END();
}

// Обработчик событий
void action(GyverPortal &p)
{
  if (p.click())
  {
    p.clickInt("Eff_SEL", eff_index);
    p.clickBool("POWER", power);
    p.clickColor("RGB", rgb);
    p.clickInt("BRIGHT", BRIGHT);
    p.clickFloat("SPEED", SPEED);
    if(!power){
      currentEffect = -1;
      clearLED();
    }else{
      currentEffect = eff_index;
    }
  }
  if (p.update())
  {
  }
}

void WebServerTask(void *pvParameters)
{
  GyverPortal ui;
  ui.attachBuild(build);
  ui.attach(action);
  ui.start();
  while (ui.tick());
  Serial.println("Portal run");
}

void LEDTask(void *pvParameters)
{
  while (true)
  {
    switch (currentEffect)
      {
      case 0:
        oneColorAll();
        break;
      case 1:
        rainbowLoop();
        break;
      case 2:
        rainbowFade();
        break;
      case 3:
        rainbowCycle();
      break;
      case 4:
        Fire();
      break;
      default:
        
      break;
      }
  }
}
TaskHandle_t WebServerTaskHandle;
TaskHandle_t LEDTaskHandle;

void setup()
{
  Serial.begin(9600);
  IPAddress ip(192, 168, 31, 239);
  IPAddress gateway(192, 168, 31, 1);
  IPAddress subnet(255, 255, 255, 0);

  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, LED_COUNT).setCorrection(TypicalLEDStrip);

  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_SSID, AP_PASS);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  Serial.println(xPortGetCoreID());

  xTaskCreatePinnedToCore(
      WebServerTask, 
      "WebServerTask", 
      10000,           
      NULL,            
      1,               
      &WebServerTaskHandle,  
      0                
  );

  xTaskCreatePinnedToCore(
      LEDTask, 
      "LEDTask", 
      10000,           
      NULL,           
      1,              
      &LEDTaskHandle,  
      1               
  );
  Serial.println("Setup end");
}

void loop()
{
}