#include "U8glib.h"

//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
U8GLIB_SH1106_128X64_2X u8g(U8G_I2C_OPT_NONE); // I think the 2X option uses double the memory but should be faster

struct Asteroid {
  float x;
  float y;
  float xVel;
  float yVel;
  float radius;

};

const int numAsteroids = 10;
Asteroid asteroids[numAsteroids];// = [{0,0,6,5}, {0,0,6,5}, {0,0,6,5}, {0,0,6,5}];


char* cashString = "0000000.00"; // initialise with as many chars as we're likely to need!
int position[] = {
  0, 0
};

void initDisplay() {
  //u8g.setRot180();
  updateCashString(credit);

  initAsteroids();
}

void initAsteroids() {

  for (int i = 0; i < numAsteroids; i++) {

    Asteroid &p = asteroids[i];

    p.radius = random(2,8);

    p.x = random(p.radius, u8g.getWidth() - p.radius);
    p.y = random(p.radius, u8g.getHeight() - p.radius);
    float angle = random(0, 360);
    p.xVel = cos(radians(angle)) * p.radius*0.75;
    p.yVel = sin(radians(angle)) * p.radius*0.75;

  }


}


boolean updateDisplay() {

  bool screensaver = ((unsigned long)(millis() - timeoutStartTime) > TIMEOUTMILLIS);

  if (screensaver) {
    int h = u8g.getHeight() - 1;
    int w = u8g.getWidth() - 3;

    for (int i = 0; i < numAsteroids; i++) {

      Asteroid &p = asteroids[i];

      p.x += p.xVel;
      p.y += p.yVel;

//      Serial.print(i);
//      Serial.print(" ");
//      Serial.print(p.x);
//      Serial.print(" ");
//      Serial.println(p.xVel);

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
//
//if (p.x + p.radius >= w) {
//       
//        p.x =  p.radius;
//      } else if (p.x - p.radius <= 0) {
//        p.x = w-p.radius;
//
//      }
//
//      if (p.y + p.radius >= h) {
//        p.y =  p.radius;
//      
//      } else if (p.y - p.radius <= 0) {
//       
//        p.y = h-p.radius;
//      }
//
    }
    u8g.firstPage();
    do {

      for (int j = 0; j < numAsteroids; j++) {

        Asteroid &p = asteroids[j];

        u8g.drawCircle(p.x, p.y, p.radius);

      }
      //u8g.drawStr( position[0], position[1], cashString); // only currently accommodates for 3 or 4 digits

    }
    while ( u8g.nextPage() );







    return false;
  }

  if (!displayDirty) return false;
  if (mode == MODE_NORMAL) {

    drawCashValue();

  }
  else {
    drawAdmin() ;

  }


  displayDirty = false;
  return true;

}

void drawCashValue() {

  // Nice fonts what I like :
  //u8g.setFont(u8g_font_fub25); // basically, helvetica bold
  //u8g.setFont(u8g_font_helvB24);
  //u8g.setFont(u8g_font_profont29);
  //u8g.setFont(u8g_font_profont29);
  //u8g.setFont(u8g_font_tpssb);


  // picture loop
  if (mode == MODE_NORMAL) {



    u8g.firstPage();
    do {
      drawCashUpdate();
      //u8g.drawStr( position[0], position[1], cashString); // only currently accommodates for 3 or 4 digits

    }
    while ( u8g.nextPage() );
  }
}



void drawCashUpdate(void) {
  // this logic should probably go somewhere else
  int textwidth;
  int textheight = 35;

  u8g.setFont(u8g_font_fub35n);
  textwidth = u8g.getStrWidth(cashString);
  if (textwidth > 128) {
    u8g.setFont(u8g_font_fub30n);
    textwidth = u8g.getStrWidth(cashString);
    textheight = 30;

  }
  if (textwidth > 128) {
    u8g.setFont(u8g_font_fub25n);
    textwidth = u8g.getStrWidth(cashString);
    textheight = 25;

  }
  if (textwidth > 128) {
    u8g.setFont(u8g_font_fub20n);
    textwidth = u8g.getStrWidth(cashString);
    textheight = 20;

  }
  u8g.setFontPosTop();

  position[0] = (128 - textwidth) / 2 +  1;
  position[1] = (64 - 35) / 2 + 2;

  u8g.drawStr( position[0], position[1], cashString); // only currently accommodates for 3 or 4 digits
  u8g.setFont(u8g_font_7x13B);
  u8g.setFontPosTop();
  if (priceShownIndex == -1) u8g.drawStr( 1, 0, "CREDIT:");
  else  {
    u8g.drawStr( 1, 0, "PRICE:");
    u8g.drawStr( 100, 0, String(key).c_str());
  }
  //  + String(key));
}

void drawAdmin() {
  u8g.setFont(u8g_font_7x13B);
  u8g.setFontPosTop();
  u8g.firstPage();
  do {
    //drawCash();
    u8g.drawStr( 1, 0, "ADMIN:");

    u8g.drawStr( 0, 20, "Total :");
    u8g.drawStr( 50, 20, String(totalCredit).c_str());
  }
  while ( u8g.nextPage() );


}
void drawAdminUpdate(void) {




  //u8g.drawBox(0,0,10,10);


}

void updateCashString(long cashPence) {

  // have to convert to int to avoid stupid annoying issues with sprintf and long
  int cashpence = (int)(cashPence % 100); // int can't be more than 30000 odd
  int cashpounds = (int)(cashPence / 100);

  if ((cashPence > -100) && (cashPence < 0)) sprintf(cashString, "-0.%02d", abs(cashpence) ); // add a minus sign if necessary
  else sprintf(cashString, "%01d.%02d", (cashpounds), abs(cashpence) );

  //  // if your font has a pound sign and a lower case p then use :
  //  if((cashPence>-100) && (cashPence<0)) sprintf(cashString, "-%02dp", abs(cashpence) ); // add a minus sign if necessary
  //  else if((cashPence<100) && (cashPence>=0)) sprintf(cashString, "%02dp", abs(cashpence) );
  //  else if(cashpence == 0) sprintf(cashString, "%01d", (cashpounds));
  //  else sprintf(cashString, "%01d.%02d", (cashpounds), abs(cashpence) );



  displayDirty = true;


}





