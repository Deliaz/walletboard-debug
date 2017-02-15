#include <Adafruit_NeoPixel.h>
#include <U8glib.h>
#include "pins.h"

// Initialize SSD1306 display
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI

// Initialize WS2812b
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()   {
  analogReference(INTERNAL);

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);

  // Flip image on screen
  u8g.setRot180();

  // Set WS2812b to white color
  pixel.setPixelColor(1, 0xFFFFFF);
}


void loop() {

  //Display loop
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  
}

// Main dwar loop
void draw(void) {
  //  u8g.setFont(u8g_font_helvR08);
  u8g.setFont(u8g_font_6x13);

  // Button Extra 1
  u8g.drawStr( 0, 12, "X1:");
  u8g.drawStr( 20, 12, digitalRead(BTN_EXTRA) ? "1" : "0");

  // Button Extra 2
  u8g.drawStr( 36, 12, "X2:");
  u8g.drawStr( 56, 12, digitalRead(BTN_EXTRA2) ? "1" : "0");

  // Button Up
  u8g.drawStr( 76, 12, "U:");
  u8g.drawStr( 96, 12, digitalRead(BTN_UP) ? "1" : "0");

  // Button Right
  u8g.drawStr( 0, 24, "R:");
  u8g.drawStr( 20, 24, digitalRead(BTN_RIGHT) ? "1" : "0");

  // Button Down
  u8g.drawStr( 34, 24, "D:");
  u8g.drawStr( 54, 24, digitalRead(BTN_DOWN) ? "1" : "0");

  // Button Left
  u8g.drawStr( 74, 24, "L:");
  u8g.drawStr( 94, 24, digitalRead(BTN_LEFT) ? "1" : "0");

  // Battery ADC
  u8g.drawStr( 0, 42, "ADC Bat:");
  char bufBat[4];
  snprintf (bufBat, 4, "%d", analogRead(ADC_BATTERY));
  u8g.drawStr(52, 42, bufBat);

  // USB ADC
  u8g.drawStr( 0, 54, "ADC Usb:");
  char bufUsb[4];
  snprintf (bufUsb, 4, "%d", analogRead(ADC_USB));
  u8g.drawStr(52, 54, bufUsb);
}
