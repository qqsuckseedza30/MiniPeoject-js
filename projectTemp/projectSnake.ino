#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
//Pines de comunicación SPI
#define TFT_SCLK 2   //Pin_SCK
#define TFT_MOSI 3   //Pin_SDA
#define TFT_RST 10   //Pin_Res
#define TFT_DC 6     //Pin_DC
#define TFT_CS 7     //Pin_CS
//Definicion de medidas de la pantalla
#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 160
//Definición de los pines del Joystick
#define BUTTON_LEFT 8     //Izquierda
#define BUTTON_UP 9       //Arriba
#define BUTTON_CENTER 4   //Centro
#define BUTTON_DOWN 5     //Abajo
#define BUTTON_RIGHT 13   //Derecha
//Objeto Pantalla TFT
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
void setup() {
  //Declaración de los pines y activación de las resistencias PullUp
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_CENTER, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  
  //Se inicia la pantalla
  tft.initR(INITR_BLACKTAB);
}
//Definición de variables
int x = 50;
int y = 80;
int step=1;
int w=15;
int h=13;
int goal[]={60,100};
//Definición de la función snake
void snake(){
  //Definición de variables de control del Joystick
  int leftValue = digitalRead(BUTTON_LEFT);
  int upValue = digitalRead(BUTTON_UP);
  int centerValue = digitalRead(BUTTON_CENTER);
  int downValue = digitalRead(BUTTON_DOWN);
  int rightValue = digitalRead(BUTTON_RIGHT);
  if(leftValue == LOW){
    x = x - step;
  }
  if(rightValue == LOW){
    x = x + step;
  }
  if(upValue == LOW){
    y = y - step;
  }
  if(downValue == LOW){
    y = y + step;
  }
  if(centerValue == LOW){
    tft.fillScreen(ST7735_BLACK);
    tft.fillRect(goal[0],goal[1], w, h, ST7735_ORANGE);
  }
  if(x < 0){
    x = SCREEN_WIDTH-1;
  }
  if(x > SCREEN_WIDTH-1){
    x = 0;
  }
  if(y < 0){
    y = SCREEN_HEIGHT-1;
  }
  if(y > SCREEN_HEIGHT-1){
    y = 0;
  }
  if (x >= goal[0] && x <= (goal[0] + w) && y >= goal[1] && y <= (goal[1] + h)) {
    tft.fillScreen(ST7735_BLACK);
    goal[0] = random(20,80);
    goal[1] = random(20,150);
    tft.fillRect(goal[0],goal[1], w, h, ST7735_ORANGE);
  }
  tft.fillCircle(x,y,4,ST7735_BLUE);
  delay(50);
}
void loop() {
  //Se llama a la función snake
  snake();
}