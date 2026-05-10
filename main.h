#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"

#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 800

#define GRAVITY 0.4f
#define JUMP_STENGTH -7.0f
#define PIPE_SPEED 3.0f

typedef enum GameState
{
    STATE_START,
    STATE_GAMEPLAY,
    STATE_GAMEOVER
}GameState;


extern int score;
extern int highScore;

#endif 