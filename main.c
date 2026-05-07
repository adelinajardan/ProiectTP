#include "raylib.h"
#include "main.h"
#include "bird.h"
#include "pipes.h"
#include "game.h"


int main(void) {
    
    
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT, "Flappy Bird by ADE");
    
    SetTargetFPS(60);

    Texture2D background=LoadTexture("assets/background.png");
    Bird bird;
    Pipe pipes[MAX_PIPES];
    GameState gameState=STATE_START;
    InitBird(&bird);
    InitPipes(pipes);


    if (background.id==0)
    {
        TraceLog(LOG_ERROR, "error la incarcare img");
    }

    
    while (!WindowShouldClose()) 
    {
        if (gameState==STATE_START)
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                gameState=STATE_GAMEPLAY;
                InitBird(&bird);
                InitPipes(pipes);
            }
        }
        else if (gameState==STATE_GAMEPLAY)
        {
            UpdateBird(&bird);
            UpdatePipes(pipes);
            if (CheckCollisions(bird, pipes))
            {
                gameState=STATE_GAMEOVER;
            }
        }
        else if (gameState==STATE_GAMEOVER)
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                InitBird(&bird);
                InitPipes(pipes);
                gameState=STATE_START;
            }
        }
        
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexturePro(
                background,
                (Rectangle){0,0,background.width, background.height},
                (Rectangle){0,0,SCREEN_WIDTH, SCREEN_HEIGHT},
                (Vector2){0,0},
                0.0f,
                WHITE
            );

            if (gameState == STATE_START)
            {
                DrawText("FLAPPY BIRD",SCREEN_WIDTH/2-140,SCREEN_HEIGHT/2-50,40,DARKGRAY);
                DrawText("Press SPACE to JUMP and START", SCREEN_WIDTH/2-180, SCREEN_HEIGHT/2+20, 20, GRAY);
            }
            else if (gameState == STATE_GAMEPLAY)
            {
                DrawBird(&bird);
                DrawPipes(pipes);
            }
            else if (gameState == STATE_GAMEOVER)
            {
                DrawPipes(pipes);
                DrawBird(&bird);
                DrawRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK,0.5f));
                DrawText("GAME OVER! Press SPACE to Restart", SCREEN_WIDTH/2-120, SCREEN_HEIGHT/2-40, 40, RED);
            }

    
        EndDrawing();
    }

    UnloadTexture(background);  
    CloseWindow();
    return 0;
}