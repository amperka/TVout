// библиотека для работы с композитным видео выходом
#include <TVout.h>
// файлы изображений
#include "schematic.h"
#include "TVOlogo.h"

// создаём объект TV класса TVout
TVout TV;

int zOff = 150;
int xOff = 0;
int yOff = 0;
// размер сторон куба
int sideSize = 50;
int viewPlane = 64;
// угол куба
float angle = PI / 60;

// массив координат куба
float cube3D[8][3] = {
  {xOff - sideSize, yOff + sideSize, zOff - sideSize},
  {xOff + sideSize, yOff + sideSize, zOff - sideSize},
  {xOff - sideSize, yOff - sideSize, zOff - sideSize},
  {xOff + sideSize, yOff - sideSize, zOff - sideSize},
  {xOff - sideSize, yOff + sideSize, zOff + sideSize},
  {xOff + sideSize, yOff + sideSize, zOff + sideSize},
  {xOff - sideSize, yOff - sideSize, zOff + sideSize},
  {xOff + sideSize, yOff - sideSize, zOff + sideSize}
};

unsigned char cube2D[8][2];

void setup()
{
  // инициализируем коммуникацию с телевизиром
  // выбираем режим PAL / NTSC и разрешние экрана
  TV.begin(PAL);
  // выбираем шрифт 6x8
  TV.selectFont(font6x8);
  intro();
  // выводим строку
  TV.println("Hello!\r\nI am the TVout library for Arduino\n");
  // ждём 3 секунды
  TV.delay(3000);
  // выводим строку
  TV.println("I generate PAL or NTSC composite video signal\n");
  // ждём 3 секунды
  TV.delay(3000);
  // выводим строку
  TV.println("My schematic:");
  // ждём 2 секунды
  TV.delay(2000);
  // очищаем экран
  TV.clearScreen();
  // выводим изображение
  TV.bitmap(0,0,schematic);
  // ждём 5 секунд
  TV.delay(5000);
  // очищаем экран
  TV.clearScreen();
  // выводим строку
  TV.println("Lets see what\nI can do");
  // ждём 2 секунды
  TV.delay(2000);

  // шрифты
  // очищаем экран
  TV.clearScreen();
  // выводим строку в заданных координатах
  TV.println("Multiple fonts:");
  // выбираем шрифт «4×6»
  TV.selectFont(font4x6);
  // выводим строку
  TV.println("4x6 font FONT");
  // выбираем шрифт «6×8»
  TV.selectFont(font6x8);
  // выводим строку
  TV.println("6x8 font FONT");
  // выбираем шрифт «8×8»
  TV.selectFont(font8x8);
  // выводим строку
  TV.println("8x8 font FONT");
  // ждём 2 секунды
  TV.delay(2000);
  
  // Draw Basic Shapes
  // очищаем экран
  TV.clearScreen();
  // выбираем шрифт «6×8»
  TV.selectFont(font6x8);
  // выводим строку
  TV.print(9,44,"Draw Basic Shapes");
  // ждём 2 секунды
  TV.delay(2000);
  
  // круги
  // очищаем экран
  TV.clearScreen();
  // рисуем круг в центре экрана белым цветом
  // с радиусом «TV.vres()/3» без закраски
  TV.drawCircle(TV.hres() / 2, TV.vres() / 2, TV.vres() / 3, WHITE);
  TV.delay(500);
  // рисуем круг в центре экрана белым цветом
  // с радиусом «TV.vres()/2» с инвертацией цвета
  TV.drawCircle(TV.hres() / 2, TV.vres() / 2, TV.vres() / 2, WHITE, INVERT);
  // ждём 2 секунды
  TV.delay(2000);
  
  // линии и квадраты
  // очищаем экран
  TV.clearScreen();
  // рисуем квадрат с координатами (20,20) 
  TV.drawRect(20, 20, 80, 56, WHITE);
  TV.delay(500);
  TV.drawRect(10, 10, 100, 76, WHITE,INVERT);
  TV.delay(500);
  TV.drawLine(60, 20, 60, 76, INVERT);
  TV.drawLine(20, 48, 100, 48, INVERT);
  TV.delay(500);
  TV.drawLine(10, 10, 110, 86, INVERT);
  TV.drawLine(10, 86, 110, 10, INVERT);
  TV.delay(2000);
  TV.drawLine(10, 86, 110, 10, INVERT);
  // очищаем экран
  TV.clearScreen();
  // инициализируем генератор псевдослучайных чисел
  randomSeed(analogRead(A0));
}

void loop()
{
  // вращение куба в 3D
  int rsteps = random(10, 60);
  switch(random(6)) {
    case 0:
      for (int i = 0; i < rsteps; i++) {
        zrotate(angle);
        // рисуем куб
        printcube();
      }
      break;
    case 1:
      for (int i = 0; i < rsteps; i++) {
        zrotate(2 * PI - angle);
        // рисуем куб
        printcube();
      }
      break;
    case 2:
      for (int i = 0; i < rsteps; i++) {
        xrotate(angle);
        // рисуем куб
        printcube();
      }
      break;
    case 3:
      for (int i = 0; i < rsteps; i++) {
        xrotate(2*PI - angle);
        // рисуем куб
        printcube();
      }
      break;
    case 4:
      for (int i = 0; i < rsteps; i++) {
        yrotate(angle);
        // рисуем куб
        printcube();
      }
      break;
    case 5:
      for (int i = 0; i < rsteps; i++) {
        yrotate(2 * PI - angle);
        // рисуем куб
        printcube();
      }
      break;
  }
}


// функция вывода логотипа на экран
void intro() {
  int w, l, wb;
  int index;
  w = pgm_read_byte(TVOlogo);
  l = pgm_read_byte(TVOlogo + 1);
  if (w & 7) {
    wb = w / 8 + 1;
  } else {
    wb = w / 8;
  }
  index = wb * (l - 1) + 2;
  for (int i = 1; i < l; i++ ) {
    TV.bitmap((TV.hres() - w) / 2, 0, TVOlogo, index, w, i);
    index -= wb;
    TV.delay(50);
  }
  for (int i = 0; i < (TV.vres() - l) / 2; i++) {
    TV.bitmap((TV.hres() - w) / 2, i, TVOlogo);
    TV.delay(50);
  }
  TV.delay(3000);
  TV.clearScreen();
}

// функция отрисовки куба
void printcube() {
  for (int i = 0; i < 8; i++) {
    cube2D[i][0] = (unsigned char)((cube3D[i][0] * viewPlane / cube3D[i][2]) + (TV.hres() / 2));
    cube2D[i][1] = (unsigned char)((cube3D[i][1] * viewPlane / cube3D[i][2]) + (TV.vres() / 2));
  }
  TV.delayFrame(1);
  TV.clearScreen();
  drawCube();
}

// функция вращения куба по оси X
void xrotate(float q) {
  float ty, tz, temp;
  for(int i = 0; i < 8; i++) {
    ty = cube3D[i][1] - yOff;
    tz = cube3D[i][2] - zOff;
    temp = ty * cos(q) - tz * sin(q);
    tz = ty * sin(q) + tz * cos(q);
    ty = temp;
    cube3D[i][1] = ty + yOff;
    cube3D[i][2] = tz + zOff;
  }
}

// функция вращения куба по оси Y
void yrotate(float q) {
  float tx,tz,temp;
  for(int i = 0; i < 8; i++) {
    tx = cube3D[i][0] - xOff;
    tz = cube3D[i][2] - zOff;
    temp = tz * cos(q) - tx * sin(q);
    tx = tz * sin(q) + tx * cos(q);
    tz = temp;
    cube3D[i][0] = tx + xOff;
    cube3D[i][2] = tz + zOff;
  }
}

// функция вращения куба по оси Z
void zrotate(float q) {
  float tx, ty, temp;
  for(int i = 0; i < 8; i++) {
    tx = cube3D[i][0] - xOff;
    ty = cube3D[i][1] - yOff;
    temp = tx * cos(q) - ty * sin(q);
    ty = tx * sin(q) + ty * cos(q);
    tx = temp;
    cube3D[i][0] = tx + xOff;
    cube3D[i][1] = ty + yOff;
  }
}

// рисуем куб
void drawCube() {
  TV.drawLine(cube2D[0][0], cube2D[0][1], cube2D[1][0],cube2D[1][1], WHITE);
  TV.drawLine(cube2D[0][0], cube2D[0][1], cube2D[2][0],cube2D[2][1], WHITE);
  TV.drawLine(cube2D[0][0], cube2D[0][1], cube2D[4][0],cube2D[4][1], WHITE);
  TV.drawLine(cube2D[1][0], cube2D[1][1], cube2D[5][0],cube2D[5][1], WHITE);
  TV.drawLine(cube2D[1][0], cube2D[1][1], cube2D[3][0],cube2D[3][1], WHITE);
  TV.drawLine(cube2D[2][0], cube2D[2][1], cube2D[6][0],cube2D[6][1], WHITE);
  TV.drawLine(cube2D[2][0], cube2D[2][1], cube2D[3][0],cube2D[3][1], WHITE);
  TV.drawLine(cube2D[4][0], cube2D[4][1], cube2D[6][0],cube2D[6][1], WHITE);
  TV.drawLine(cube2D[4][0], cube2D[4][1], cube2D[5][0],cube2D[5][1], WHITE);
  TV.drawLine(cube2D[7][0], cube2D[7][1], cube2D[6][0],cube2D[6][1], WHITE);
  TV.drawLine(cube2D[7][0], cube2D[7][1], cube2D[3][0],cube2D[3][1], WHITE);
  TV.drawLine(cube2D[7][0], cube2D[7][1], cube2D[5][0],cube2D[5][1], WHITE);
}
