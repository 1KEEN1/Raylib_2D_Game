#include <iostream>
#include <math.h>

#include "raylib.h"

// Idle animation of character
typedef struct Animation {
    int firstFrame;
    int lastFrame;
    int currentFrame;
    float frameSpeed;
    float frameDurationLeft;
} Animation;

void animationUpdate(Animation* self) {
    float dt = GetFrameTime();
    self->frameDurationLeft -= dt;

    if (self->frameDurationLeft <= 0.0f) {
        self->frameDurationLeft = self->frameSpeed;
        self->currentFrame++;

        if (self->currentFrame > self->lastFrame) {
            self->currentFrame = self->firstFrame;
        }
    }
}

Rectangle animationFrame(Animation* self, int numFramesPerRow) {
    float x = (self->currentFrame % numFramesPerRow) * 32.0f;
    float y = (self->currentFrame / numFramesPerRow) * 32.0f;

    Rectangle rect;
    rect.x = x;
    rect.y = y;
    rect.width = 32.0f;
    rect.height = 32.0f;

    return rect;
}

int main() {
    // Initialization of window
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Game");

    SetTargetFPS(60);

    // Loading full pack of main character assets.
    Texture2D mainCharacter = LoadTexture("sprites/skeleton.png");
    
    const int fullPackWidth = 128;
    const int fullPackHeigth = 384;
    const int amountOfColumns = 4;
    const int amountOfRows = 12;
    const int movementSpeed = 3;

    // Loading default pose of main character.
    // Scale image x2 by multiplying
    const int mainCharacterWidth = (fullPackWidth / amountOfColumns) * 2;
    const int mainCharacterHeight = (fullPackHeigth / amountOfRows) * 2;

    // Select first frame of character from pack.
    Rectangle mainCharacterFrame = Rectangle {
        0,
        0,
        (float)mainCharacterWidth / 2.0f,
        (float)mainCharacterHeight / 2.0f
    };

    // Player position on the screen. Starts from center.
    Rectangle mainCharacterPosition = Rectangle {
        (float)screenWidth / 2.0f - mainCharacterWidth / 2.0f,
        (float)screenHeight / 2.0f - mainCharacterHeight / 2.0f, 
        (float)mainCharacterWidth, 
        (float)mainCharacterHeight
    };

    // Initialization of animation
    Animation anim;      
    anim.firstFrame = 0;
    anim.lastFrame = 3;
    anim.currentFrame = 0;
    anim.frameSpeed = 0.2f;
    anim.frameDurationLeft = 0.1f;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
       
        animationUpdate(&anim);
        // Getting current frame
        Rectangle sourceRect = animationFrame(&anim, amountOfColumns);

        // Rotation point (center)
        Vector2 origin = Vector2{ mainCharacterPosition.width / 2.0f, mainCharacterPosition.height / 2.0f };

        // Movement of character
        if (IsKeyDown(KEY_W)) {
            mainCharacterPosition.y -= movementSpeed;
        }
        if (IsKeyDown(KEY_S)) {
            mainCharacterPosition.y += movementSpeed;
        }
        if (IsKeyDown(KEY_D)) {
            mainCharacterPosition.x += movementSpeed;
        }
        if (IsKeyDown(KEY_A)) {
            mainCharacterPosition.x -= movementSpeed;
        }

        DrawTexturePro(mainCharacter,
            sourceRect,             
            mainCharacterPosition,
            origin,   
            0.0f,
            WHITE);

        EndDrawing();
    }

    // Free memory by unloading character image.
    UnloadTexture(mainCharacter);

    CloseWindow();
    return 0;
}