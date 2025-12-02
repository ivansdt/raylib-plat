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

AnimationClip animations[5];

static void initAnim(int arrId, char* animName, float sizeX, float sizeY, int max)
{
    animations[arrId].name = animName;

    float offset = 0;
    for (int i = 0; i < max; i++)
    {
        animations[arrId].frames[i] = (Rectangle){offset, 0.0f, sizeX, sizeY};
        offset += sizeX;
    }

    animations[arrId].fps = max;
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

        if (animations[arrId].current > max-1)
        {
            animations[arrId].current = 0;
        }
    }
    return animations[arrId].frames[animations[arrId].current];
}

static Rectangle animateJump(int arrId, int max)
{
    animations[arrId].frameCount++;

    if (animations[arrId].frameCount >= (60 / animations[arrId].fps))
    {
        animations[arrId].frameCount = 0;
        if(animations[arrId].current < max-1)
            animations[arrId].current++;
    }
    return animations[arrId].frames[animations[arrId].current];
}