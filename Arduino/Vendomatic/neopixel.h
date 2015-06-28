#include <float.h>

int numPixels = NUM_ROWS * PIXELS_PER_ROW; 
float pixelHighlight = 0; 

unsigned long timeoutStartTime = 0;
int coinDropCountdown = -1; 

boolean ledsOff = false; 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, NEOPIXEL, NEO_GRB + NEO_KHZ800); 
int rgb[] = { 0,0,0}; 

void initNeopixels() { 
  strip.begin(); 
  strip.show();
}


void setHSBPixel(int pixel, int hue, int sat, int brightness) { 
    
    H2R_HSBtoRGB(hue%360, sat, brightness, rgb); 
    strip.setPixelColor(pixel, rgb[0], rgb[1], rgb[2]); 

}

void updateLeds(int highlightrow = -1, boolean vending = false){
  
  if((unsigned long) (millis()-timeoutStartTime) > TIMEOUTMILLIS) { 
    if(!ledsOff) { 
      for(int i = 0; i<numPixels; i++) { 
        strip.setPixelColor(i, 0,0,0); 
      } 
      strip.show(); 
      ledsOff = true; 
    }
    return; 
    
  }
  ledsOff = false; 
  int saturation, brightness;
  saturation = 100; 
  brightness = (highlightrow == -1) ? 50:  60; 
  if(vending) brightness = 10; 
  
  
  
  
  float sinvalue = (float)(millis()*0.001f); //fmod((double)millis()*0.02f ,PI*2.0f); 
  float hue = (sin(sinvalue) +1) *180;
 
  
  for (int y = 0; y<NUM_ROWS;  y++) { 
    
    
    
    for(int x = 0; x<PIXELS_PER_ROW; x++) {
      int xfixed = (y%2==0)? PIXELS_PER_ROW-1 - x : x; 
      int index = (y*PIXELS_PER_ROW) + xfixed; 
//      
//      if(((y*PIXELS_PER_ROW) + x) == floor(pixelHighlight)) {
//        saturation = 0; 
//      } 
//         
     
      if (y==highlightrow) {
        int b = vending ? (sin((float)(millis()*0.02f +x )) +1) *128 : 255; 
        strip.setPixelColor(index, b,b,b); 
      }
      else {

         if(highlightrow>=0) setHSBPixel(index, vending ? 220: 0 , saturation,30); 
         else setHSBPixel(index,hue+index , saturation,brightness);         
      }//
      
      if(abs(index- (numPixels-coinDropCountdown))<2) setHSBPixel(index,0,0,100);  
    
    }  
  }
  strip.show(); 
  pixelHighlight+=1; 
  if(pixelHighlight>=numPixels) pixelHighlight = 0; 
  coinDropCountdown-=3; 

}

