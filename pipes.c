#include "pipes.h"
#include <stdlib.h>

int score=0;

void InitPipes(Pipe pipes[])
{
    float gapHeight = 300.0f;
    for (int i=0; i<MAX_PIPES; i++)
    {
        pipes[i].xPos=SCREEN_WIDTH+(i*gapHeight);
        pipes[i].active=true;
        //random gap heights
        float gapY=GetRandomValue(150,550);
        float gapHeight=160.0f;
        float pipeWidth=60.0f;

        pipes[i].top=(Rectangle){pipes[i].xPos,0,pipeWidth, gapY};
        pipes[i].bottom=(Rectangle){pipes[i].xPos,gapY + gapHeight,pipeWidth, SCREEN_HEIGHT-(gapY +gapHeight)};
        pipes[i].active=true;

    }
}

void UpdatePipes(Pipe pipes[],Rectangle birdRect)
{
    float gapHeight = 300.0f;

    for (int i=0; i<MAX_PIPES; i++)
    {
        pipes[i].xPos-=PIPE_SPEED;
      //pipes[i].top.x=pipes[i].xPos;
      //pipes[i].bottom.x=pipes[i].xPos;
      if (pipes[i].active && (birdRect.x>pipes[i].xPos+pipes[i].top.width/2))
      {
        score++;
        pipes[i].active=false;
      }
    
       if (pipes[i].xPos <-60)
       {
            float furthestX=0;
            for (int j=0; j<MAX_PIPES; j++)
            {
                if(pipes[j].xPos>furthestX)
                {
                    furthestX=pipes[j].xPos;
                }
            }

            pipes[i].xPos=furthestX+gapHeight;

            float gapY=GetRandomValue(150,550);
            float gapHeight=180.0f;
            float pipeWidth=60.0f;

            pipes[i].top=(Rectangle){pipes[i].xPos,0,pipeWidth, gapY};
            pipes[i].bottom=(Rectangle){pipes[i].xPos,gapY + gapHeight,pipeWidth, SCREEN_HEIGHT-(gapY +gapHeight)};
            pipes[i].active=true;
       }
       else
       {
        pipes[i].top.x=pipes[i].xPos;
        pipes[i].bottom.x=pipes[i].xPos;
       }

        
    }

}


void DrawPipes(Pipe pipes[])
{
    for (int i=0; i<MAX_PIPES; i++)
    {   
        Color pipe = (Color){75,180,70,255};
        DrawRectangleRec(pipes[i].top,pipe);
        DrawRectangleRec(pipes[i].bottom,pipe);
        //umbra    
        Color darkGreen=(Color){40,100,35,255};
        DrawRectangle(pipes[i].top.x+pipes[i].top.width-15,pipes[i].top.y,15,pipes[i].top.height,darkGreen);
        DrawRectangle(pipes[i].bottom.x+pipes[i].bottom.width-15,pipes[i].bottom.y,15,pipes[i].bottom.height,darkGreen);
        //lumina
        Color lightGreen=(Color){140,220,130,255};
        DrawRectangle(pipes[i].top.x,pipes[i].top.y,15,pipes[i].top.height,lightGreen);
        DrawRectangle(pipes[i].bottom.x,pipes[i].bottom.y,15,pipes[i].bottom.height,lightGreen);
        //contur
        DrawRectangleLinesEx(pipes[i].top,2,BLACK);
        DrawRectangleLinesEx(pipes[i].bottom,2,BLACK);
        //capac
        float capWidth=pipes[i].top.width+14;
        float capHeight=25;
        float capX = pipes[i].top.x-5;

        Rectangle topCap ={capX, pipes[i].top.y+pipes[i].top.height-capHeight,capWidth,capHeight};
        Rectangle bottomCap={capX,pipes[i].bottom.y,capWidth,capHeight};
        DrawRectangleRec(topCap,pipe);
        DrawRectangleRec(bottomCap,pipe);
        //capac sus
        DrawRectangle(topCap.x,topCap.y,15+7,topCap.height,lightGreen);
        DrawRectangle(topCap.x+topCap.width-(15+7),topCap.y,15+7,topCap.height,darkGreen);
        //capac jos
        DrawRectangle(bottomCap.x,bottomCap.y,15+7,bottomCap.height,lightGreen);
        DrawRectangle(bottomCap.x+bottomCap.width-(15+7),bottomCap.y,15+7,bottomCap.height,darkGreen);

        DrawRectangleLinesEx(topCap,2,BLACK);
        DrawRectangleLinesEx(bottomCap,2,BLACK);

    }
}
