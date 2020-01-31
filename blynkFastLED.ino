#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define NUM_LEDS 60
#include "FastLED.h"
#define PIN 6 //DIGITAL PIN FOR CONNECTION

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Token";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID";
char pass[] = "PASSWORD";
CRGB leds[NUM_LEDS];
byte counter;
int globalPinValue = 0;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
   FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   FastLED.setBrightness(190);
   pinMode(13, OUTPUT);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V0) //функция, отслеживающая изменение виртуального пина 0
{
  int pinValue = param.asInt(); //переменная текущего состояния виртуального пина
  if (pinValue == 1) {
       rainbow();
  }
}

BLYNK_WRITE(V1){
  int pinValue = param.asInt();
  if(pinValue == 1){
    blackOut();
  }
}

BLYNK_WRITE(V2){
  int pinValue = param.asInt();
  if(pinValue == 1){
    white();
  }
}

void blackOut(){
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void rainbow(){
   for (int i = 0; i < NUM_LEDS; i++ ) {         // от 0 до первой трети
         leds[i] = CHSV(counter + i * 6, 255, 255);  // HSV. Увеличивать HUE (цвет)
         // умножение i уменьшает шаг радуги
         }
        counter++;        // counter меняется от 0 до 255 (тип данных byte)
        FastLED.show();
        delay(5);
}
void white(){
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::White;
  }
  FastLED.show();
}
