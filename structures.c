#include "raylib.h"

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
    bool isMoving;
    // Flags for detecting collision
    bool hitOnFloor;
    bool hitOnCeiling;
    bool hitOnWall;

} Entity;

static Entity Player = { 0 };
