
int numPixels = NUM_ROWS * PIXELS_PER_ROW; 
float pixelHighlight = 0; 

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
  
  int saturation, brightness;
  saturation = 100; 
  brightness = (highlightrow == -1) ? 0:  50; 
  if(vending) brightness = 100; 
  
  for (int y = 0; y<NUM_ROWS;  y++) { 
    
    
    
    for(int x = 0; x<PIXELS_PER_ROW; x++) {
      int xfixed = (y%2==0)? PIXELS_PER_ROW-1 - x : x; 
      int index = (y*PIXELS_PER_ROW) + xfixed; 
//      
//      if(((y*PIXELS_PER_ROW) + x) == floor(pixelHighlight)) {
//        saturation = 0; 
//      } 
//         
     int sinvalue = millis()%10000; 
      if(y==highlightrow) {
        
        int b = vending ? ((sin(sinvalue*0.02)+x) +1) *128 : 255; 
        strip.setPixelColor(index, b,b,b); 
      }
      else {
        if(random()<0.01) strip.setPixelColor(index, 255,255,255);
        else setHSBPixel(index, (int)(sinvalue*0.1)+index, saturation,brightness); 
      }//
    
    }  
  }
  strip.show(); 
  pixelHighlight+=1; 
  if(pixelHighlight>=numPixels) pixelHighlight = 0; 

}

