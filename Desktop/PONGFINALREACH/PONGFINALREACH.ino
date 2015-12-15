
#include <Adafruit_GFX.h>   
#include <RGBmatrixPanel.h> 
//Defines pins on screen
#define A   A0
#define LAT A3
#define OE  9
#define CLK  8 
#define C   A2
#define B   A1
//definiton of variables and colors
int ballSpeed = 220;
int pHeight=1;
int pWidth=6;
int pA = 0; //paddle A
int pB = 0; //paddle B
int ballUpdown = 1; //Direction y
int ballSize=1;
int ballLeftRight = 1; // x Direction
int originalPaddleA, originalPaddleB;
int ballA, ballB, orignalBallA, originalBallB;
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
uint16_t black = matrix.Color444(0, 0, 0);
uint16_t white = matrix.Color444(15, 15, 15);
uint16_t yellow = matrix.Color444(15, 15, 0);

//initially makes screen screen
void clear() {
  matrix.fillScreen(black);

}
//sets up the beginning of the game
void setup() {
  matrix.begin();
  clear();
}
//sets up the both potentiometers
void loop() {
  int theHeight = matrix.height();
  int theWidth = matrix.width();
  int potentiometer1= analogRead(A5);
  int potentiometer2=analogRead(A4);
  
  originalPaddleA = pA;
  originalPaddleB = pB;
 
 
  pA = map(potentiometer1, 0, 1023, 0, theWidth)- 3 ;
  pB= map(potentiometer2, 0, 1023, 0, theHeight)-1;
 if (millis() % (110) < 2) {
    makeBallMove();
  }
  if ( originalPaddleB != pB || originalPaddleA != pA) {
    matrix.fillRect(originalPaddleA, originalPaddleB, pWidth, pHeight,black);
  }
  matrix.fillRect(pA, pB, pWidth, pHeight,white);
  
}


void makeBallMove() {
  //Changes direction if the ball accidently goes of the LED
  if (ballA < 0 || ballA > matrix.width()-1) {
    ballLeftRight= -ballLeftRight;

  }
   // Verifies if ball and paddle occupy the same space on LED
  if (inPaddle(ballA, ballB, pA, pB, pWidth, pHeight)) {
    ballUpdown = -ballUpdown;
    
  }
 if (ballB > matrix.height()-1 || ballB < 0) {
    ballUpdown = -ballUpdown;
 
  }  
 

 //Constantly changes balls position
  ballA = ballLeftRight+ballA;
  ballB =ballUpdown+ballB;
 
  // Gets rid of previous position of ball
  if (orignalBallA!= ballA|| originalBallB != ballB) {
    matrix.fillRect(orignalBallA, originalBallB, ballSize, ballSize,black);
  }
 
  // Fills in ball's current position
  matrix.fillRect(ballA, ballB, ballSize, ballSize,white);
 
  orignalBallA= ballA;
  originalBallB = ballB;
}
boolean inPaddle(int x, int y, int rectX, int rectY, int rectWidth, int rectHeight) {
  boolean play= false;
   
  if (  ((x >= rectX) && x <= (rectX + rectWidth))&& (y >= rectY && y <= (rectY + rectHeight))) {
       play=true;
  }
 
  return play;  
}
