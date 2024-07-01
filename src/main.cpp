#include <Arduino.h>
#include <GyverPortal.h>
#include <FastLED.h>
#include "WiFi.h"


// Global variables
#define LED_PIN 26;
#define LED_COUNT 180;
#define AP_SSID "Alien"
#define AP_PASS "bezparolianehodi"

GyverPortal ui;

// Список эффектов
char* effects[5] = {
  "Rainbow",
  "Confetti",
  "Sinelon",
  "Juggle",
  ""
};

// конструктор страницы
void build(GyverPortal& p) {
  GP.BUILD_BEGIN(GP_DARK);
  GP.PAGE_TITLE("ESPLight"); 
  
  GP.TITLE("ESPLight"); GP.BREAK();
  GP.SPAN("Effect:"); GP.BREAK();
  GP.SELECT("Eff_SEL", effects); GP.BREAK();
  GP.BUTTON("clk", "Click");  GP.BREAK();
  GP.BUTTON("ext", "Exit");   GP.BREAK();
  //GP.FILE_UPLOAD("test.txt"); Требует предварительного монтирования файловой системы
  GP.BUILD_END();
}

//Обработчик событий
void action(GyverPortal& p) {
  if (p.click("clk")) Serial.println("Button click");
  if (p.click("ext")) {
    Serial.println("Exit portal");
    p.stop();
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_SSID, AP_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  GyverPortal ui;
  ui.attachBuild(build);
  ui.attach(action);
  ui.start();
  Serial.println("Portal run");
  while (ui.tick());

  Serial.println("Setup end");
}


void loop() {
}