/// @file    Cylon.ino
/// @brief   An animation that moves a single LED back and forth (Larson Scanner effect)
/// @example Cylon.ino
#include <Adafruit_TinyUSB.h>
#include <FastLED.h>
_FL_DEFPIN(0, 2, 0);  // P0.25 -- D00 /  UART RX
// How many leds in your strip?
#define NUM_LEDS 24

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 0
#define CLOCK_PIN 13

const int trigPin = 10;
const int echoPin = 9;
const int buzzer = 1;

float duration, distance;
// Define the array of leds
CRGB leds[NUM_LEDS];
// #define Serial SerialUSB

void setup() {
  // Serial.begin(57600);
  // Serial.println("resetting");
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
}

void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); }
}


float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}


int lastTime;
void loop() {
  static uint8_t hue = 0;
  measureDistance();
  // if (millis() - lastTime > 30 * 1000) {
    if (distance < 100) {
      lastTime = millis();
      Serial.println("buzz");
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
    }
  // }


  //   tone(buzzer, 1000); // Send 1KHz sound signal...
  // delay(1000);        // ...for 1 sec
  // noTone(buzzer);     // Stop sound...
  // delay(1000);        // ...for 1sec
  // Serial.print("x");
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  // Serial.print("x");

  // Now go in the other direction.
  for (int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
}
