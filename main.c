#define PLATFORM_DESKTOP
#include "raylib.h"
#define MAX_STALPI 3 // cati stalpi sa fie pe ecran in acelasi timp

typedef enum
{
    MENU,
    GAMEPLAY,
    GAMEOVER
} StareJoc;

int main(void)
{
    const int ecranLatime = 450;
    const int ecranInaltime = 700;

    InitWindow(ecranLatime, ecranInaltime, "Flappy Bird - Adelina J");
    StareJoc stareCurenta = MENU;
    Texture2D fundal = LoadTexture("background.png");
    // Texture2D fundal = LoadTexture("C:/Users/adeli/OneDrive/Desktop/ProiectTP/background.png");
    if (fundal.id == 0)
    {
        TraceLog(LOG_WARNING, "Nu a fost gasita imag de fundal");
    }
    // Pasarea
    Vector2 pozitiePasare = {100, ecranInaltime / 2};
    float vitezaPasare = 0;
    float gravitatie = 0.5f; // cat de repede sau incet cade(mai mare mai greu)
    float fortaSaritura = -8.0f;

    // setari stalpi
    float latimeStalp = 50;
    float spatiuIntreStalpi_V = 180; // spatiu prin care trece pasarea
    float vitezaStalp = 3.0f;
    float disIntreStalpi_O = 260; // cat de des apar
    float distanta0 = 260;
    float spatiuV = 180;

    Rectangle stalpiSus[MAX_STALPI];
    Rectangle stalpiJos[MAX_STALPI];

    // initalizam totii 3 stalpi la d egale cu o inaltime aleatorie pt cel de sus
    for (int i = 0; i < MAX_STALPI; i++)
    {
        float inaltimeInitiala = (float)GetRandomValue(50, 400);
        stalpiSus[i] = (Rectangle){ecranLatime + i * disIntreStalpi_O, 0, latimeStalp, inaltimeInitiala};
        stalpiJos[i] = (Rectangle){ecranLatime + i * disIntreStalpi_O, inaltimeInitiala + spatiuIntreStalpi_V, latimeStalp, ecranInaltime};
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // 1. LOGICA (Update)
        if (stareCurenta == MENU)
        {
            if (IsKeyPressed(KEY_SPACE))
                stareCurenta = GAMEPLAY;
            
        }
        else if (stareCurenta == GAMEPLAY)
        {             //Pasarea cade constant din cauza gravitatiei
            vitezaPasare += gravitatie;
            pozitiePasare.y += vitezaPasare;

            if (IsKeyPressed(KEY_SPACE))
                vitezaPasare = fortaSaritura;

            // miscam si resetam stalpii spre stanga
            for (int i = 0; i < MAX_STALPI; i++)
            {
                stalpiSus[i].x -= vitezaStalp;
                stalpiJos[i].x -= vitezaStalp;
                // verificare coliziune
                if (CheckCollisionCircleRec(pozitiePasare, 20, stalpiSus[i]) || CheckCollisionCircleRec(pozitiePasare, 20, stalpiJos[i]))
                {
                    stareCurenta = GAMEOVER;
                }
            
                // resetare stalp cand iese din ecran
                if (stalpiSus[i].x < -latimeStalp)
                {
                    // trimitem in spatele ultimului stalp existent
                    stalpiSus[i].x = ecranLatime + (disIntreStalpi_O * (MAX_STALPI - 1));
                    stalpiJos[i].x = stalpiSus[i].x;
                    float nouaInaltime = (float)GetRandomValue(50, 400);
                    stalpiSus[i].height = nouaInaltime;
                    stalpiJos[i].y = nouaInaltime + spatiuIntreStalpi_V;
                }
            }
            // daca cade din ecrn
            if (pozitiePasare.y > ecranInaltime || pozitiePasare.y < 0)
            {
                stareCurenta = GAMEOVER;
            }
        }
            else if (stareCurenta == GAMEOVER)
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    pozitiePasare = (Vector2){100, ecranInaltime / 2};
                    vitezaPasare = 0;
                    for (int i = 0; i < MAX_STALPI; i++)
                    {
                        float inaltime = (float)GetRandomValue(50, 400);
                        stalpiSus[i].x = ecranLatime + i * distanta0;
                        stalpiSus[i].height = inaltime;
                        stalpiJos[i].x = ecranLatime + i * distanta0;
                        stalpiJos[i].y = inaltime + spatiuV;
                    }
                    stareCurenta = GAMEPLAY;
                }
            }
        
            // Desenare stalp
            BeginDrawing();
            ClearBackground(BLACK);
            // stergem ecranul
            // desnam fundal
            DrawTexture(fundal, 0, 0, WHITE);

            if (stareCurenta == MENU)
            {
                DrawRectangle(0, 0, ecranLatime, ecranInaltime, Fade(BLACK, 0.6f));
                // DrawText("Textul", x, y, dimensiuneFont, culoare);
                DrawText("FLAPPY BIRD by Adelina Jardan ", 40, 200, 25, YELLOW); // 60, 200,40
                DrawText("Apasa [SPACE] pentru START", 70, 350, 20, WHITE);
            }
            else if (stareCurenta == GAMEPLAY)
            {
                for (int i = 0; i < MAX_STALPI; i++)
                {
                    DrawRectangleRec(stalpiSus[i], DARKGREEN);
                    DrawRectangleRec(stalpiJos[i], DARKGREEN);
                }
                DrawCircleV(pozitiePasare, 20, YELLOW);
                DrawText("Apasa SPACE ca sa sari", 10, 10, 20, DARKBLUE);
            }
            else if (stareCurenta == GAMEOVER)
            {
                DrawRectangle(0, 0, ecranLatime, ecranInaltime, Fade(RED, 0.5f));
                DrawText("GAME OVER", 130, 250, 40, WHITE);
                DrawText("Apasa [ENTER] sa reincerci", 80, 350, 20, YELLOW);
            }
        
        EndDrawing();
        }
        UnloadTexture(fundal);
        CloseWindow();
    
    return 0;
}
