#include "game.h"

bool CheckCollisions(Bird bird, Pipe pipes[])
{
    if (bird.position.y + bird.radius >= SCREEN_HEIGHT)
    {
        return true;
    }
    for (int i=0; i<MAX_PIPES; i++)
    {
        if (CheckCollisionCircleRec(bird.position, bird.radius, pipes[i].top) ||
            CheckCollisionCircleRec(bird.position, bird.radius, pipes[i].bottom))
        {
            return true;
        }
    }
    return false;   
}