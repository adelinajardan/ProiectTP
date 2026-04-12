#define PLATFORM_DESKTOP
#include "raylib.h"
#define MAX_STALPI 4 // cati stalpi sa fie pe ecran in acelasi timp

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
    Texture2D texturaPasare=LoadTexture("bird.png");
    // Texture2D fundal = LoadTexture("C:/Users/adeli/OneDrive/Desktop/ProiectTP/background.png");
    if (fundal.id == 0)
    {
        TraceLog(LOG_WARNING, "Nu a fost gasita imag de fundal");
    }
    if (texturaPasare.id == 0)
    {
        TraceLog(LOG_WARNING, "Nu a fost gasita imag cu bird");
    }
    // Pasarea
    Vector2 pozitiePasare = {100, ecranInaltime / 2};
    float vitezaPasare = 0;
    float gravitatie = 0.5f; // cat de repede sau incet cade(mai mare mai greu)
    float fortaSaritura = -8.0f;
    float scalaPasare=0.14f;

    // setari stalpi
    float latimeStalp = 50;
    float spatiuIntreStalpi_V = 180; // spatiu prin care trece pasarea
    float vitezaStalp = 3.0f;
    float disIntreStalpi_O = 260; // cat de des apar
    float distanta0 = 260;
    float spatiuV = 180;
    Color DARKER_GREEN_CUSTOM = (Color){ 0, 68, 0, 255 };

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
            {
                stareCurenta = GAMEPLAY;
            }
            
        }
        else if (stareCurenta == GAMEPLAY)
        {             //Pasarea cade constant din cauza gravitatiei
            vitezaPasare += gravitatie;
            pozitiePasare.y += vitezaPasare;

            if(IsKeyPressed(KEY_SPACE))
            {
                vitezaPasare=fortaSaritura;
            }
            for (int i=0; i<MAX_STALPI;i++)
            {
                stalpiSus[i].x-=vitezaStalp;
                stalpiJos[i].x-=vitezaStalp;
            
                // --- LOGICA DE COLIZIUNE ACTUALIZATĂ PENTRU SCAALARE ---
                // Calculăm dimensiunile reale ale păsării micșorate
                float latimeRealaPasare = texturaPasare.width * scalaPasare;   // 377 * 0.1 = 37.7
                float inaltimeRealaPasare = texturaPasare.height * scalaPasare; // 376 * 0.1 = 37.6
                Rectangle corpPasare = { pozitiePasare.x, pozitiePasare.y, latimeRealaPasare, inaltimeRealaPasare };

             // Verificăm coliziunea cu stâlpii folosind dreptunghiul micșorat
                 if (CheckCollisionRecs(corpPasare, stalpiSus[i]) || CheckCollisionRecs(corpPasare, stalpiJos[i])) 
                {
                     stareCurenta = GAMEOVER;
                 }
                // resetare stalp cand iese din ecran
                if (stalpiSus[i].x < -latimeStalp)
                {
                    // trimitem in spatele ultimului stalp existent
                    stalpiSus[i].x = stalpiSus[i].x + (disIntreStalpi_O * MAX_STALPI);
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
            DrawTexture(fundal, 0, 0, WHITE);

            if (stareCurenta == MENU)
            {
                DrawRectangle(0, 0, ecranLatime, ecranInaltime, Fade(BLACK, 0.6f));
                // DrawText("Textul", x, y, dimensiuneFont, culoare);
                DrawText("FLAPPY BIRD by Adelina Jardan ", 40, 200, 25, YELLOW); // 60, 200,40
                DrawText("Apasa [SPACE] pentru START.", 70, 350, 20, WHITE);
                DrawText("Apasa SPACE ca sa sari.", 90, 380, 20, WHITE);
            }

            else if (stareCurenta == GAMEPLAY)
            {
                /*for (int i = 0; i < MAX_STALPI; i++)
                {
                    DrawRectangleRec(stalpiSus[i], DARKGREEN);
                    DrawRectangleRec(stalpiJos[i], DARKGREEN);
                }*/
                 for (int i = 0; i < MAX_STALPI; i++)
                 {
                    // corpul principal al stâlpilor (Verde)
                    DrawRectangleRec(stalpiSus[i], DARKGREEN);
                    DrawRectangleRec(stalpiJos[i], DARKGREEN);
                    //lumina (o bandă subțire de 5 pixeli în stânga)
                    // Folosim LIME pentru un efect de verde strălucitor
                    DrawRectangle(stalpiSus[i].x, stalpiSus[i].y, 5, stalpiSus[i].height, LIME);
                    DrawRectangle(stalpiJos[i].x, stalpiJos[i].y, 5, stalpiJos[i].height, LIME);

                    // umbra(o bandă subțire de 5 pixeli în dreapta)
                    // stalpiSus[i].x + latimeStalp - 5 calculează marginea dreaptă
                    DrawRectangle(stalpiSus[i].x + latimeStalp - 5, stalpiSus[i].y, 5, stalpiSus[i].height, DARKER_GREEN_CUSTOM);
                    DrawRectangle(stalpiJos[i].x + latimeStalp - 5, stalpiJos[i].y, 5, stalpiJos[i].height, DARKER_GREEN_CUSTOM);

                    float latimeCapac = latimeStalp + 6; // Capacul va fi cu 20 pixeli mai lat
                    float xCapac = stalpiSus[i].x - 3;   // Il centram scazand 10 pixeli din X
                    int inaltimeCapac= 18.0f;
                    //capacul pentru stalpul de SUS (se deseneaza la baza lui)
                    DrawRectangle(xCapac, stalpiSus[i].height - inaltimeCapac, latimeCapac, inaltimeCapac, DARKGREEN);
                    // capacul pentru stalpul de JOS (se deseneaza la inceputul lui)
                    DrawRectangle(xCapac, stalpiJos[i].y, latimeCapac, inaltimeCapac, DARKGREEN);
                    DrawRectangle(xCapac,stalpiSus[i].height-inaltimeCapac,3,inaltimeCapac,LIME);
                    DrawRectangle(xCapac,stalpiJos[i].y,3,inaltimeCapac,LIME);
                    DrawRectangle(xCapac+latimeCapac-3,stalpiSus[i].height-inaltimeCapac,3,inaltimeCapac,(Color){0,40,0,255});
                    DrawRectangle(xCapac+latimeCapac-3,stalpiJos[i].y,3,inaltimeCapac,(Color){0,40,0,255});
                    //DrawRectangleLines-contur

                    Color culoareUmbra=Fade(BLACK,0.3f);
                    int grosimeUmbra=4;
                    DrawRectangle(stalpiSus[i].x,stalpiSus[i].height-inaltimeCapac-grosimeUmbra,latimeStalp,grosimeUmbra,culoareUmbra);
                    DrawRectangle(stalpiJos[i].x,stalpiJos[i].y+inaltimeCapac,latimeStalp,grosimeUmbra,culoareUmbra);


                 }
                
                //DrawCircleV(pozitiePasare, 20, YELLOW);
                DrawTextureEx(texturaPasare, pozitiePasare,0.0f,scalaPasare,WHITE);
                
            }

            else if (stareCurenta == GAMEOVER)
            {
                DrawRectangle(0, 0, ecranLatime, ecranInaltime, Fade(RED, 0.5f));
                DrawText("GAME OVER", 130, 250, 40, RED);
                DrawText("Apasa [ENTER] sa reincerci", 80, 350, 20, YELLOW);
            } 
        
        EndDrawing();
    }
        UnloadTexture(fundal);
        UnloadTexture(texturaPasare);
        CloseWindow();
    
    return 0;
}
