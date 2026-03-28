#include <iostream>
#include <math.h>

#include "raylib.h"

// Idle animation of character
typedef struct Animation {
    int first;
    int last;
    int current;
    float speed;
    float durationLeft;
} Animation;

void animationUpdate(Animation* self) {
    float dt = GetFrameTime();
    self->durationLeft -= dt;

    if (self->durationLeft <= 0.0f) {
        self->durationLeft = self->speed;
        self->current++;

        if (self->current > self->last) {
            self->current = self->first;
        }
    }
}

Rectangle animationFrame(Animation* self, int numFramesPerRow) {
    float x = (self->current % numFramesPerRow) * 32.0f;
    float y = (self->current / numFramesPerRow) * 32.0f;

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
    anim.first = 0;
    anim.last = 3;
    anim.current = 0;
    anim.speed = 0.1f;
    anim.durationLeft = 0.1f;

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