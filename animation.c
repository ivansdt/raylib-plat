#include <stdio.h>
#include "raylib.h"

typedef struct
{
    char *name;
    Rectangle frames[32];
    int fps;
    int frameCount;
    int current;
} AnimationClip;

AnimationClip animations[3];

static void initAnim(int arrId, char* animName, float sizeX, float sizeY)
{
    animations[arrId].name = animName;

    float offset = sizeX;
    for (int i = 0; i < 6; i++)
    {
        animations[arrId].frames[i] = (Rectangle){offset, 0.0f, sizeX, sizeY};
        offset += sizeX;
    }

    animations[arrId].fps = 6;
    animations[arrId].frameCount = 0;
    animations[arrId].current = 0;
}

static Rectangle animate(int arrId, int max)
{
    animations[arrId].frameCount++;

    if (animations[arrId].frameCount >= (60 / animations[arrId].fps))
    {
        animations[arrId].frameCount = 0;
        animations[arrId].current++;

        if (animations[arrId].current > max)
        {
            animations[arrId].current = 0;
        }
    }
    return animations[arrId].frames[animations[arrId].current];
}