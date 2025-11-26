#include "raylib.h"

typedef struct {
    float right;
    float left;
    float up;
    float down;
    bool jump;
} Input;

typedef struct {
    Vector2 position;
    float direction;
    float maxSpd;
    float acc;
    float dcc;
    float gravity;
    float jumpImpulse;
    float jumpRelease;
    Vector2 velocity;
    // Carry stored subpixel values
    float hsp;
    float vsp;

    bool isGrounded;
    bool isJumping;
    // Flags for detecting collision
    bool hitOnFloor;
    bool hitOnCeiling;
    bool hitOnWall;

    Input *control;
} Entity;