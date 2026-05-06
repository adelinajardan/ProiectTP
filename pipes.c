#include "pipes.h"
#include <stdlib.h>

void InitPipes(Pipe pipes[])
{
    float gapHeight = 300.0f;
    for (int i=0; i<MAX_PIPES; i++)
    {
        pipes[i].xPos=SCREEN_WIDTH+(i*gapHeight);
        pipes[i].active=true;
        //random gap heights
        float gapY=GetRandomValue(80,SCREEN_HEIGHT-200);
        float gapHeight=120.0f;
        float pipeWidth=60.0f;

        pipes[i].top=(Rectangle){pipes[i].xPos,0,pipeWidth, gapY};
        pipes[i].bottom=(Rectangle){pipes[i].xPos,gapY + gapHeight,pipeWidth, SCREEN_HEIGHT-(gapY +gapHeight)};

    }
}

void UpdatePipes(Pipe pipes[])
{
    for (int i=0; i<MAX_PIPES; i++)
    {
        pipes[i].xPos-=PIPE_SPEED;
        pipes[i].top.x=pipes[i].xPos;
        pipes[i].bottom.x=pipes[i].xPos;

        if (pipes[i].xPos< -pipes[i].top.width)
        {
            pipes[i].xPos=SCREEN_WIDTH;
            //random gap heights
            float gapY=GetRandomValue(80,SCREEN_HEIGHT-200);
            float gapHeight=120.0f;
    

            pipes[i].top.y=0;
            pipes[i].top.height=gapY;
            pipes[i].bottom.y=gapY + gapHeight;
            pipes[i].bottom.height=SCREEN_HEIGHT-(gapY +gapHeight);
        }
    }

}


void DrawPipes(Pipe pipes[])
{
    for (int i=0; i<MAX_PIPES; i++)
    {
        DrawRectangleRec(pipes[i].top,GREEN);
        DrawRectangleRec(pipes[i].bottom,GREEN);
    }
}
