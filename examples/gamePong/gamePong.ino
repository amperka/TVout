// библиотека для работы с композитным видео выходом
#include <TVout.h>

// создаём объект TV класса TVout
TVout TV;

// максимальное количесво очков
#define MAX_SCORE         7
// длина ракеток
#define PADDLE_HEIGHT     10
// невидимые боковые грани рекакетки
// для отбивания в крайних точках ракетки
#define PADDLE_OFFSET     2

// пины подключения джойстиков каждого игрока
#define PLAYER_LEFT_PIN   A5
#define PLAYER_RIGHT_PIN  A0

// переменные для хранения размеров экрана
int hres, vres;
// координаты шара
int ballX, ballY;
// направление шара
int ballDX = 1;
int ballDY = 1;
// очки игроков
int playerScoreLeft = 0;
int playerScoreRight = 0;
int leftPaddleY = 0;
int rightPaddleY = 0;

// состояния системы
enum State
{
    RESET_GAME,
    NEXT_LEVEL,
    PLAY_GAME,
    STATE_MISS,
};
 
// объявляем переменную state
State state;

bool missed = 0;

void setup()
{
  
  // инициализируем коммуникацию с телевизиром
  TV.begin(NTSC, 136, 96);
  // ждём 1 секунду
  delay(1000);
  // считываем размеры экрана
  hres = TV.hres();
  vres = TV.vres();
  // сбрасываем игру
  state = RESET_GAME;

}

void loop()
{
  switch (state) {
    case RESET_GAME:
      // очищаем экран
      TV.clearScreen();
      // выбираем шрифт «4×6»
      TV.selectFont(font4x6);
      // печатем на экране слово «Амперка»
      TV.print(55, 0, "Amperka");
      delay(1000);
      // выбираем шрифт «8×8»
      TV.selectFont(font8x8);
      // печатем на экране название игры «Arduino Pong"»
      TV.print(20, 30, "Arduino Pong");
      delay(1000);
      // на старт, внимание, вперёд
      for (int i = 3; i != 0; i-- ) {
        TV.print(hres / 2, 60, i);
        TV.tone(1000, 300);
        delay(1000);
      }
      TV.tone(2000, 300);
      // выбираем шрифт «4×6»
      TV.selectFont(font4x6);
      // очищаем экран
      TV.clearScreen();
      // обнуляем счёт обоих игроков
      playerScoreLeft = 0;
      playerScoreRight = 0;
      // переходим на следующий уровень
      state = NEXT_LEVEL;
      break;
    case NEXT_LEVEL:
      // сброс шарика и ракеток
      resetBallAndPaddles();
      // рисуем игровое поле на экране
      drawBox();
      // выводим очки игроков на экране
      drawScores();
      // рисуем игровые ракетки
      drawPaddles();
      // переходим в состояние игры
      state = PLAY_GAME;
      break;
    case PLAY_GAME:
    // если мяч достиг верхеней / нижней границицы поля
    if (ballY == vres || ballY == 0) {
      ballDY *= -1;
    }
    // если мяч приближается к правой стороне
    if (ballX >= hres - 2) { 
      // если мяч отбился правой ракеткой 
      if (ballY > rightPaddleY - PADDLE_OFFSET && 
          ballY < (rightPaddleY + PADDLE_HEIGHT + PADDLE_OFFSET) && ballDX > 0 ) {
        ballDX = -1;
      }
    }
    // если мяч достиг правой стены
    if (ballX == hres - 1) {
      missed = true;
      state = STATE_MISS;
      playerScoreLeft++;
      break;
    }
    
    // если мяч приближается к правой стороне
    if (ballX <= 2) {
      // если мяч отбился левой ракеткой
      if (ballY > leftPaddleY - PADDLE_OFFSET && 
          ballY < (leftPaddleY + PADDLE_HEIGHT + PADDLE_OFFSET) && ballDX < 0 ) {
        ballDX = 1;
      }
    }
    // если мяч достиг левой стены
    if (ballX == 0) {
      missed = false;
      state = STATE_MISS;
      playerScoreRight++;
      break;
    }
    
    // обновляем положения ракеток
    leftPaddleY =  map(analogRead(PLAYER_LEFT_PIN), 0, 1024, 0, vres - PADDLE_HEIGHT);
    rightPaddleY = map(analogRead(PLAYER_RIGHT_PIN), 0, 1024, 0, vres - PADDLE_HEIGHT);
    // обновляем положение шарика
    drawBall();
    // меням местоположение шарика на следущий шаг
    ballX += ballDX;
    ballY += ballDY;
    drawPaddles();
    // обновляем положение шарика
    drawBall();
    TV.delayFrame(1);
      break;
    
    case STATE_MISS:
      // если кто то пропустид мяч
      if (playerScoreLeft == MAX_SCORE) {
        TV.print(16, vres / 2, "Winner!");
        TV.tone(2000, 500);
        TV.delayFrame(120);
        state = RESET_GAME;
        while(1);
        break;
      } else if (playerScoreRight == MAX_SCORE) {
        TV.print(hres / 2 + 16, vres / 2, "Winner!");
        TV.tone(2000, 500);
        TV.delayFrame(120);
        state = RESET_GAME;
        while(1);
        break;
      }
      if (missed) {
        TV.print(hres / 2 + 16, vres / 2, "Missed!");
        TV.tone(500, 300);
      } else {
        TV.print(16, vres / 2, "Missed!");
        TV.tone(500, 300);
      }     
      delay(1000);
      TV.clearScreen();
      state = NEXT_LEVEL;
      break;
  }
}

// сброс шарика и ракеток
void resetBallAndPaddles() {
  randomSeed(analogRead(A2));
  int noise = random(vres);
  ballX = hres / 2;
  ballY = random(vres);
  ballDX = (noise & 0x01) ?  1 : -1;
  ballDY = (noise & 0x02) ? -1 :  1;

  leftPaddleY = vres / 2;
  rightPaddleY = vres / 2;
}

// вывод очков на дисплей
void drawScores() {
  TV.printChar((hres / 4), 4, '0' + playerScoreLeft);
  TV.printChar((hres / 4) + (hres / 2), 4, '0' + playerScoreRight);
}

// вывод ракеток на дисплей
void drawPaddles() {
  // стираем предыдущие ракетки
  // стираем всю возможную область их местоположения
  TV.drawRect(0, 0, 1, vres, 0, 0);
  TV.drawRect(hres - 2, 0, 1, vres, 0, 0);

  // выводим текущее положение ракеток
  TV.drawRect(0, leftPaddleY, 1, PADDLE_HEIGHT, WHITE, true);
  TV.drawRect(hres - 2, rightPaddleY, 1, PADDLE_HEIGHT, WHITE, true);
}

// вывод шарика
void drawBall() {
  // рисуем шарик
  TV.setPixel(ballX, ballY, INVERT);
}

// отрисовка игрового поля на экране
void drawBox() {
  TV.clearScreen();
  // середина поля
  for (int i = 0; i < vres; i += 6) {
    TV.drawLine(hres / 2, i, hres / 2, i + 2, 1);
  }
  // верхняя граница поля
  TV.drawLine(0, 0, hres, 0, WHITE);
  // нижняя граница поля
  TV.drawLine(0, vres - 2, hres, vres - 2, WHITE);
}
