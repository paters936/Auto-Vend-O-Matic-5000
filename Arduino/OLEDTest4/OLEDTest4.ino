// Animated pendant for Adafruit Pro Trinket and SSD1306 OLED display,
// inspired by the After Dark "Flying Toasters" screensaver.
// Triggered with vibration switch between digital pins 3 and 4.


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmaps.h" // Toaster graphics data is in this header file

Adafruit_SSD1306 display(4);

#define N_FLYERS   4 // Number of flying things

struct Flyer {       // Array of flying things
  int16_t x, y;      // Top-left position * 16 (for subpixel pos updates)
  int8_t  depth;     // Stacking order is also speed, 12-24 subpixels/frame
  uint8_t frame;     // Animation frame; Toasters cycle 0-3, Toast=255
  boolean isToast; 
} flyer[N_FLYERS];



void setup() {

  randomSeed(analogRead(2));           // Seed random from unused analog input
  DDRB  = DDRC  = DDRD  = 0x00;        // Set all pins to inputs and
  PORTB = PORTC = PORTD = 0xFF;        // enable pullups (for power saving)

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Init screen
  
  display.clearDisplay();
  
  for(uint8_t i=0; i<N_FLYERS; i++) {  // Randomize initial flyer states
    flyer[i].x     = (-32 + random(160)) * 16;
    flyer[i].y     = (-32 + random( 96)) * 16;
    flyer[i].frame = random(3) ? random(4) : 255; // 66% toaster, else toast
    flyer[i].depth = 10 + random(16);             // Speed / stacking order
  }
  qsort(flyer, N_FLYERS, sizeof(struct Flyer), compare); // Sort depths

 
}

void loop() {
  uint8_t i, f;
  int16_t x, y;
  
  boolean resort = false;     // By default, don't re-sort depths

  display.display();          // Update screen to show current positions
  display.clearDisplay();     // Start drawing next frame

  for(i=0; i<N_FLYERS; i++) { // For each flyer...

    // First draw each item...
    f = (flyer[i].isToast) ? 4 : (flyer[i].frame++ & 3); // Frame #
    
    x = flyer[i].x / 16;
    y = flyer[i].y / 16;
    //display.drawBitmap(x, y, (const uint8_t *)pgm_read_word(&mask[f]), 32, 32, BLACK);
    display.drawCircle(x+16,y+16,10,WHITE);
    display.drawBitmap(x, y, (const uint8_t *)pgm_read_word(&img[ f]), 32, 32, WHITE);

    // Then update position, checking if item moved off screen...
    flyer[i].x -= flyer[i].depth * 2; // Update position based on depth,
    flyer[i].y += flyer[i].depth;     // for a sort of pseudo-parallax effect.
    if((flyer[i].y >= (64*16)) || (flyer[i].x <= (-32*16))) { // Off screen?
      if(random(7) < 5) {         // Pick random edge; 0-4 = top
        flyer[i].x = random(160) * 16;
        flyer[i].y = -32         * 16;
      } else {                    // 5-6 = right
        flyer[i].x = 128         * 16;
        flyer[i].y = random(64)  * 16;
      }
      boolean isToast = random(3); 
      flyer[i].frame = isToast ? random(4) : 255; // 66% toaster, else toast
      flyer[i].depth = 10 + random(16);
      flyer[i].isToast = isToast;
      resort = true;
    }
  }
  // If any items were 'rebooted' to new position, re-sort all depths
  //if(resort) qsort(flyer, N_FLYERS, sizeof(struct Flyer), compare);

}

// Flyer depth comparison function for qsort()
static int compare(const void *a, const void *b) {
  return ((struct Flyer *)a)->depth - ((struct Flyer *)b)->depth;
}


