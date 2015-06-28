#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4

struct Asteroid {
  float x;
  float y;
  float xVel;
  float yVel;
  float radius;

};

const int numAsteroids = 20;
Asteroid asteroids[numAsteroids];// = [{0,0,6,5}, {0,0,6,5}, {0,0,6,5}, {0,0,6,5}];
Adafruit_SSD1306 display(OLED_RESET);



void setup() {
  
  Serial.begin(115200);
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  initAsteroids();
}

void loop() {
  // put your main code here, to run repeatedly:
  updateDisplay();
}


void initAsteroids() {

  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(0xff); 
 
  
  for (int i = 0; i < numAsteroids; i++) {

    Asteroid &p = asteroids[i];

    p.radius = 4;

    p.x = random(p.radius, 128 - p.radius);
    p.y = random(p.radius, 64 - p.radius);
    float angle = random(0, 360);
    p.xVel = cos(radians(angle)) * 5;
    p.yVel = sin(radians(angle)) * 5;

  }


}


boolean updateDisplay() {

  int h = 64;
  int w = 128;
  
 // display.dim(millis()%2000<1000); 
  
  //display.ssd1306_command(SSD1306_SETCONTRAST);
  //display.ssd1306_command((millis()%2000<1000) ? 0 : 0xff); 
  //display.ssd1306_command((sin(radians((float)millis()*0.2f)) + 1.0f) * 0xff);
  
  display.clearDisplay();

  for (int i = 0; i < numAsteroids; i++) {

    Asteroid &p = asteroids[i];

    p.x += p.xVel;
    p.y += p.yVel;


    if (p.x + p.radius >= w) {
      p.xVel *= -1;
      p.x = w - p.radius;
    } else if (p.x - p.radius <= 0) {
      p.xVel *= -1;
      p.x = p.radius;

    }

    if (p.y + p.radius >= h) {
      p.y = h - p.radius;
      p.yVel *= -1;
    } else if (p.y - p.radius <= 0) {
      p.yVel *= -1;
      p.y = p.radius;
    }


    display.fillCircle(p.x, p.y, p.radius, WHITE);

  }
  
 // display.fillRect(0,0,128,64,WHITE);
  display.display();

}

