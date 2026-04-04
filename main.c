#define PLATFORM_DESKTOP
#include "raylib.h"

int main(void) {
    const int ecranLatime = 450;
    const int ecranInaltime = 700;

    InitWindow(ecranLatime, ecranInaltime, "Flappy Bird - Pasul 5: Obstacole Inaltimi diferite");

    // Datele pasarii
    Vector2 pozitiePasare = { 100, ecranInaltime / 2 };
    float vitezaPasare = 0;
    float gravitatie = 0.5f; //cat de repede sau incet cade(mai mare mai greu)
    float fortaSarituta = -8.0f;

    //setari stalpi
    float latimeStalp=50;
    float spatiuIntreStalpi=180; //spatiu prin care trece pasarea
    float vitezaStalp=3.0f;

    //initalizam 1 stalp cu o inaltime aleatorie pt cel de sus
    float inaltimeInitiala=(float)GetRandomValue(50,400);

    //Stalpi
    Rectangle stalpSus={450,0,latimeStalp,inaltimeInitiala};
    Rectangle stalpJos={4500,inaltimeInitiala +spatiuIntreStalpi,latimeStalp,ecranInaltime};
    

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // 1. LOGICA (Update)
        vitezaPasare +=gravitatie;
        pozitiePasare.y+= vitezaPasare;

        if (IsKeyPressed(KEY_SPACE)) vitezaPasare= -7.0f;

        //miscam stalpii spre stanga
        stalpSus.x -=vitezaStalp;
        stalpJos.x -=vitezaStalp;

        //regenerare stalp cand iese din ecran
        //daca stalp a iesit din ecran il ppunem iara in dreapta
        if (stalpSus.x <-latimeStalp)
        {
            stalpSus.x=ecranLatime;
            stalpJos.x=ecranLatime;

            //generare o noua inaltime aleatoare stalp sus
            float nouaInaltimeSus = (float)GetRandomValue(50,400);
            stalpSus.height=nouaInaltimeSus;
            //stalpul de jos incepe dupa cel de sus +spatiu liber
            stalpJos.y=nouaInaltimeSus+spatiuIntreStalpi;
        }
       //Desenare stalp
       BeginDrawing();
            ClearBackground(SKYBLUE);
            //Desenam stalpi
            DrawRectangleRec(stalpSus, GREEN);
            DrawRectangleRec(stalpJos, GREEN);

            // Desenam pasarea (un cerc galben momentan)
            DrawCircleV(pozitiePasare, 20, YELLOW);
        
        // Pasarea cade constant din cauza gravitatiei
        vitezaPasare += gravitatie;
        pozitiePasare.y += vitezaPasare;

        // Daca apasam SPACE, pasarea sare
        if (IsKeyPressed(KEY_SPACE)) {
            vitezaPasare = fortaSarituta;
        }

        

            DrawText("Apasa SPACE ca sa sari!", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;

}