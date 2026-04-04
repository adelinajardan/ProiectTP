#define PLATFORM_DESKTOP
#include "raylib.h"

int main(void) {
    InitWindow(450, 700, "Flappy Bird Background");

    // ÎNCĂRCARE: Se face o singură dată la început
    Texture2D background = LoadTexture("background.png"); 

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // DESENARE: Afișăm imaginea la coordonatele (0, 0)
            DrawTexture(background, 0, 0, WHITE);

            // Aici vine restul jocului tău...
            DrawCircle(225, 350, 20, YELLOW); 

        EndDrawing();
    }

    // DESCARCARE: Eliberăm memoria la final
    UnloadTexture(background);
    CloseWindow();

    return 0;
}