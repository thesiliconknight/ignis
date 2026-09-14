#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// pins
#define RELAY PC3  
#define NTC_PIN PD2
#define R_LED PA1
#define G_LED PA2
#define B_START PD4
#define B_UP PC5
#define B_DN PC4

float setpt = 220.0; 
float t_now = 0.0;
bool active = false; 
bool firing = false;

Adafruit_SSD1306 oled(128, 32, &Wire, -1);

void setup() {
  pinMode(RELAY, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  
  // internal pullups for the tact switches
  pinMode(B_START, INPUT_PULLUP);
  pinMode(B_UP, INPUT_PULLUP);
  pinMode(B_DN, INPUT_PULLUP);
  
  digitalWrite(RELAY, LOW);
  digitalWrite(R_LED, LOW);
  digitalWrite(G_LED, LOW);

  Wire.begin();
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while(true); // stuck here if screen is dead
  }
  
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 10);
  oled.print("waking up...");
  oled.display();
  delay(1000);
}

void loop() {
  // hacky debounce lol
  if (!digitalRead(B_START)) {
    active = !active;
    delay(300); 
  }
  if (!digitalRead(B_UP)) {
    setpt += 5.0;
    delay(150);
  }
  if (!digitalRead(B_DN)) {
    setpt -= 5.0;
    delay(150);
  }

  int raw_adc = analogRead(NTC_PIN);
  
  // if thermistor unplugs it reads max/min usually
  if (raw_adc == 0 || raw_adc > 4090) {
    digitalWrite(RELAY, LOW);
    active = false;
    oled.clearDisplay();
    oled.setCursor(0,0);
    oled.print("ERR: SENSOR DED");
    oled.display();
    delay(500);
    return; 
  }

  // steinhart hart magic math
  float res = 100000.0 / ((4095.0 / (float)raw_adc) - 1.0);
  float kelvin = log(res / 100000.0);
  kelvin /= 3950.0;
  kelvin += 1.0 / (25.0 + 273.15);
  t_now = (1.0 / kelvin) - 273.15;

  // relay logic
  if (active) {
    if (t_now < (setpt - 2.0)) {
      digitalWrite(RELAY, HIGH);
      firing = true;
    } else if (t_now >= setpt) {
      digitalWrite(RELAY, LOW);
      firing = false;
    }
  } else {
    digitalWrite(RELAY, LOW);
    firing = false;
  }

  // blinkies
  if (active && firing) {
    digitalWrite(R_LED, HIGH);
    digitalWrite(G_LED, LOW);
  } else if (active && !firing) {
    digitalWrite(R_LED, LOW);
    digitalWrite(G_LED, HIGH);
  } else {
    digitalWrite(R_LED, LOW);
    digitalWrite(G_LED, LOW);
  }

  // draw screen stuff
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setCursor(0, 0);
  oled.print("Tgt:");
  oled.print(setpt, 0);
  
  oled.setCursor(80, 0);
  if(active) {
    oled.print(firing ? "HOT" : "OK");
  } else {
    oled.print("OFF");
  }

  oled.setTextSize(2);
  oled.setCursor(20, 15);
  oled.print(t_now, 1);
  oled.print("C");
  oled.display();
  
  delay(50); // don't freeze
}
