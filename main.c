#define PLATFORM_DESKTOP
#include "raylib.h"
#define MAX_STALPI 3 //cati stalpi sa fie pe ecran in acelasi timp

int main(void) {
    const int ecranLatime = 450;
    const int ecranInaltime = 700;

    InitWindow(ecranLatime, ecranInaltime, "Flappy Bird - Pasul 6.2: Mai multi stalpi+Fundal");
    Texture2D fundal = LoadTexture("background.png");
    //Texture2D fundal = LoadTexture("C:/Users/adeli/OneDrive/Desktop/ProiectTP/background.png");
    if(fundal.id==0)
    {
        TraceLog(LOG_WARNING,"Nu a fost gasita imag de fundal");
    }
    // Pasarea
    Vector2 pozitiePasare = { 100, ecranInaltime / 2 };
    float vitezaPasare = 0;
    float gravitatie = 0.5f; //cat de repede sau incet cade(mai mare mai greu)
    float fortaSarituta = -8.0f;

    //setari stalpi
    float latimeStalp=50;
    float spatiuIntreStalpi_V=180; //spatiu prin care trece pasarea
    float vitezaStalp=3.0f;
    float disIntreStalpi_O =260;//cat de des apar

    Rectangle stalpiSus[MAX_STALPI];
    Rectangle stalpiJos[MAX_STALPI];


    //initalizam totii 3 stalpi la d egale cu o inaltime aleatorie pt cel de sus
    for(int i=0; i<MAX_STALPI;i++)
    {
    float inaltimeInitiala=(float)GetRandomValue(50,400);
    stalpiSus[i]=(Rectangle){ ecranLatime+i*disIntreStalpi_O,0, latimeStalp,inaltimeInitiala};
    stalpiJos[i]=(Rectangle){ ecranLatime+i*disIntreStalpi_O,inaltimeInitiala+spatiuIntreStalpi_V, latimeStalp,ecranInaltime};
    }



    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // 1. LOGICA (Update)
        vitezaPasare +=gravitatie;
        pozitiePasare.y+= vitezaPasare;

        if (IsKeyPressed(KEY_SPACE)) vitezaPasare= -7.0f;

        //miscam si resetam stalpii spre stanga
        for(int i=0; i<MAX_STALPI; i++)
        {
            stalpiSus[i].x -=vitezaStalp;
            stalpiJos[i].x -=vitezaStalp;
            // resetare stalp cand iese din ecran
            if (stalpiSus[i].x <-latimeStalp)
            {
                //trimitem in spatele ultimului stalp existent
                stalpiSus[i].x=ecranLatime + (disIntreStalpi_O*(MAX_STALPI-1));
                stalpiJos[i].x=stalpiSus[i].x;

                float nouaInaltime=(float)GetRandomValue(50,400);
                stalpiSus[i].height=nouaInaltime;
                stalpiJos[i].y=nouaInaltime+spatiuIntreStalpi_V;
            }
        }
        

        //regenerare stalp cand iese din ecran
        //daca stalp a iesit din ecran il ppunem iara in dreapta
        /*if (stalpSus.x <-latimeStalp)
        {
            stalpSus.x=ecranLatime;
            stalpJos.x=ecranLatime;

            //generare o noua inaltime aleatoare stalp sus
            float nouaInaltimeSus = (float)GetRandomValue(50,400);
            stalpSus.height=nouaInaltimeSus;
            //stalpul de jos incepe dupa cel de sus +spatiu liber
            stalpJos.y=nouaInaltimeSus+spatiuIntreStalpi;
        }*/
       //Desenare stalp
       BeginDrawing();
            ClearBackground(BLACK);
            //stergem ecranul
            //desnam fundal
            DrawTexture(fundal,0,0,WHITE);
            //Desenam stalpi
           for(int i=0; i<MAX_STALPI; i++)
           {
             DrawRectangleRec(stalpiSus[i], DARKGREEN);
            DrawRectangleRec(stalpiJos[i], DARKGREEN);
           }

            // Desenam pasarea (un cerc galben momentan)
            DrawCircleV(pozitiePasare, 20, YELLOW);
        
        /*// Pasarea cade constant din cauza gravitatiei
        vitezaPasare += gravitatie;
        pozitiePasare.y += vitezaPasare;

        // Daca apasam SPACE, pasarea sare
        if (IsKeyPressed(KEY_SPACE)) {
            vitezaPasare = fortaSarituta;
        }*/
            DrawText("Apasa SPACE ca sa sari!", 10, 10, 20, DARKBLUE);
        EndDrawing();
    }
    UnloadTexture(fundal);
    CloseWindow();
    return 0;

}