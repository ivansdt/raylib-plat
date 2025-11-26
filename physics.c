#include "raylib.h"
#include "structures.c"

static float delta;

// Set values when jump is activated
void Jump(Entity *instance)
{
    instance->velocity.y = instance->jumpImpulse;
    instance->isJumping = true;
    instance->isGrounded = false;
}

// Gravity calculation and Jump detection
void GravityCalc(Entity *instance)
{
    if (instance->isGrounded)
    {
        if (instance->isJumping)
        {
            instance->isJumping = false;
            instance->control->jump = false;    // Cancel input button
        }
        else if (!instance->isJumping && instance->control->jump)
        {
            Jump(instance);
        }
    }
    else
    {
        if (instance->isJumping)
        {
            if (!instance->control->jump)
            {
                instance->isJumping = false;
                
                if (instance->velocity.y < instance->jumpRelease)
                {
                    instance->velocity.y = instance->jumpRelease;
                }
            }
        }
    }
    
    // Add gravity
    instance->velocity.y += instance->gravity*delta;
    
    // Limit falling to negative jump value
    if (instance->velocity.y > -instance->jumpImpulse)
    {
        instance->velocity.y = -instance->jumpImpulse;
    }
}
