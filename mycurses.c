#include <stdio.h>
#include "mycurses.h"

// screen buffer
typedef charcell ScreenType[LINES][COLS];
ScreenType screen;

// cursol location
int cursolX, cursolY;

// initializes
void initscr(){
  clear();
  cursolX = 0;
  cursolY = 0;
}

void curs_set(int a){
  switch(a){
  case 0: //
    printf("\033[>5h");
    break;
  case 1: // default
    printf("\033[>5l");
    break;
  }
}

void endwin(){
  curs_set(1);
}

// outputs
int clear(){
  if(erase() == ERR)
    return ERR;
  if(refresh() == ERR)
    return ERR;
  return OK;
}

int erase(){
  int i,j;
  for(i=0; i<LINES; ++i){
    for(j=0; j<COLS; ++j){
      screen[i][j].letter = ' ';
      screen[i][j].color = 0;
    }
  }
  return OK;
}

int move(int y, int x){
  if(y < 0 || LINES <= y)
    return ERR;
  if(x < 0 || COLS <= x)
    return ERR;

  cursolY = y;
  cursolX = x;
  return OK;
}

int addch(char c){
  screen[cursolY][cursolX].letter = c;
  return OK;
}

int addstr(char*str){
  int i;
  for(i=cursolX; str[i]!='\0'; i++){
    if(i < 0 || COLS <= i)
      return ERR;
    screen[cursolY][i].letter = str[i - cursolX];
  }
  return OK;
}

int mvaddch(int y, int x, char c){
  if(move(y,x) == ERR)
    return ERR;
  if(addch(c) == ERR)
    return ERR;
  return OK;
}

int mvaddstr(int y, int x, char*str){
  if(move(y,x) == ERR)
    return ERR;
  if(addstr(str) == ERR)
    return ERR;
  return OK;
}

int refresh(){
  int i,j;
  printf("\033[2J");   // clear screen
  printf("\033[0;0H"); // move cursol to (0,0)
  for(i=0; i<LINES; ++i){
    for(j=0; j<COLS; ++j){
      putc(screen[i][j].letter, stdout);
    }
    putc('\n', stdout);
  }
  return OK;
}
