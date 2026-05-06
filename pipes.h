#ifndef PIPES_H
#define PIPES_H

#include "main.h"

#define MAX_PIPES 4


typedef struct Pipe
{
    Rectangle top;
    Rectangle bottom;
    float xPos;
    bool active;
}Pipe;

void InitPipes(Pipe pipes[]);
void UpdatePipes(Pipe pipes[]);
void DrawPipes(Pipe pipes[]);
#endif