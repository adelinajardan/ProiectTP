#define PLATFORM_DESKTOP
#include "raylib.h"

int main(void) {
    const int ecranLatime = 450;
    const int ecranInaltime = 700;

    InitWindow(ecranLatime, ecranInaltime, "Flappy Bird - Pasul 3: Gravitatie");

    // Datele pasarii
    Vector2 pozitiePasare = { 100, ecranInaltime / 2 };
    float vitezaPasare = 0;
    float gravitatie = 0.5f;
    float fortaSarituta = -8.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // 1. LOGICA (Update)
        
        // Pasarea cade constant din cauza gravitatiei
        vitezaPasare += gravitatie;
        pozitiePasare.y += vitezaPasare;

        // Daca apasam SPACE, pasarea sare
        if (IsKeyPressed(KEY_SPACE)) {
            vitezaPasare = fortaSarituta;
        }

        // 2. DESENARE (Draw)
        BeginDrawing();
            ClearBackground(SKYBLUE);

            // Desenam pasarea (un cerc galben momentan)
            DrawCircleV(pozitiePasare, 20, YELLOW);

            DrawText("Apasa SPACE ca sa sari!", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}