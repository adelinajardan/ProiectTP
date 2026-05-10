#ifndef BIRD_H
#define BIRD_H

#include "main.h"

typedef struct Bird
{
    Vector2 position;
    float velocity;
    float radius;
    Texture2D texture;
}Bird;

void InitBird(Bird *bird);
void UpdateBird(Bird *bird);
void DrawBird (Bird *bird);

#endif