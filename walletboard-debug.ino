#include <Adafruit_NeoPixel.h>
#include <U8glib.h>
#include "pins.h"

// Initialize SSD1306 display
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_FAST); // Dev 0, Fast I2C / TWI

// Initialize WS2812b
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()   {
  analogReference(INTERNAL);

  pinMode(BTN_UP, INPUT);
  pinMode(BTN_RIGHT, INPUT);
  pinMode(BTN_DOWN, INPUT);
  pinMode(BTN_LEFT, INPUT);
  pinMode(BTN_EXTRA, INPUT);
  pinMode(BTN_EXTRA2, INPUT);

  // Flip image on screen
  u8g.setRot180();

  // Set WS2812b to white color
  pixel.begin();
  //pixel.setPixelColor(0, 0xFFFFFF);
  //pixel.show();
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

  pixelTick();

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


char pixelMode = 0;
unsigned char r = 0;
unsigned char g = 0;
unsigned char b = 0;
void pixelTick() {

  switch (pixelMode) {
    case 0:
      r++;
      g = 0;
      b = 0;
      if (r == 255) {
        pixelMode = 1;
      }
      break;
    case 1:
      r = 0;
      g++;
      b = 0;
      if (g == 255) {
        pixelMode = 2;
      }
      break;
    case 2:
      r = 0;
      g = 0;
      b++;
      if (b == 255) {
        pixelMode = 3;
        b = 0;
      }
      break;
    case 3:
      r++;
      g++;
      b = 0;
      if (r == 255) {
        pixelMode = 5;
        r = 0;
        g = 0;
      }
      break;
    case 5:
      r++;
      g = 0;
      b++;
      if (r == 255) {
        pixelMode = 6;
        r = 0;
        b = 0;
      }
      break;
    case 6:
      r = 0;
      g++;
      b++;
      if (g == 255) {
        pixelMode = 7;
        g = 0;
        b = 0;
      }
      break;
    case 7:
      r++;
      g++;
      b++;
      if (g == 255) {
        pixelMode = 0;
      }
      break;
  }

  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
}
