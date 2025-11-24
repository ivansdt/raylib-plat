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

static void init_GlubeIdle(void)
{
    animations[0].name = "Glube";

    float offset = 44.0f;
    for (int i = 0; i < 6; i++)
    {
        animations[0].frames[i] = (Rectangle){offset, 0.0f, 44.0f, 31.0f};
        offset += 44.0f;
    }

    animations[0].fps = 6;
    animations[0].frameCount = 0;
    animations[0].current = 0;
}

static Rectangle animate_GlubeIdle(void)
{
    animations[0].frameCount++;

    if (animations[0].frameCount >= (60 / animations[0].fps))
    {
        animations[0].frameCount = 0;
        animations[0].current++;

        if (animations[0].current > 5)
        {
            animations[0].current = 0;
        }
    }
    return animations[0].frames[animations[0].current];
}