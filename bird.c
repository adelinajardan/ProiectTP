#include "bird.h"

void InitBird(Bird *bird)
{
    bird->position =(Vector2){100,SCREEN_HEIGHT/2.0f};
    bird->velocity = 0.0f;
    bird->radius= 20.0f;
    //bird->color = GOLD;
    
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
    if (bird->texture.id <=0) return;

    Rectangle source={0,0,(float)bird->texture.width,(float)bird->texture.height};

    float birdWidth =bird->radius*3.5f;
    float birdHeight = bird->radius*2.8f;

    Rectangle dest={
        bird->position.x,
        bird->position.y,
        birdWidth,
        birdHeight
    };
    Vector2 origin={birdWidth/2.0f, birdHeight/2.0f};
    float rotation=bird->velocity*3.0f;
    DrawTexturePro(bird->texture,source,dest,origin,rotation,WHITE);
}