#include "bird.h"

void InitBird(Bird *bird)
{
    bird->position =(Vector2){100,SCREEN_HEIGHT/2.0f};
    bird->velocity = 0.0f;
    bird->radius= 20.0f;
    bird->color = GOLD;
    
}

void UpdateBird(Bird *bird)
{
    bird->velocity +=GRAVITY;
    bird->position.y += bird->velocity;
    if (IsKeyPressed(KEY_SPACE))
    {
        bird->velocity = JUMP_STENGTH;
    }
    if (bird->position.y- bird->radius <0)
    {
        bird->position.y = bird->radius;
        bird->velocity=0;
    }
}

void DrawBird (Bird *bird)
{
    DrawCircleV(bird->position, bird->radius, bird->color);
}