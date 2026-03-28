#include <iostream>
#include <math.h>

#include "raylib.h"

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
    // Scale image x2
    const int mainCharacterWidth = (fullPackWidth / amountOfColumns) * 2;
    const int mainCharacterHeight = (fullPackHeigth / amountOfRows) * 2;

    // Select first frame of character from pack.
    Rectangle mainCharacterFrame = Rectangle {
        0,
        0,
        (float)mainCharacterWidth / 2.0f,
        (float)mainCharacterHeight / 2.0f
    };

    // Player position on the screen.
    // Starts from center.
    Rectangle mainCharacterPosition = Rectangle {
        (float)screenWidth / 2.0f - mainCharacterWidth / 2.0f,
        (float)screenHeight / 2.0f - mainCharacterHeight / 2.0f, 
        (float)mainCharacterWidth, 
        (float)mainCharacterHeight
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
       
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
            mainCharacterFrame, 
            mainCharacterPosition, 
            Vector2{ mainCharacterPosition.width, mainCharacterPosition.height },
            0.0f, 
            WHITE);

        EndDrawing();
    }

    // Free memory by unloading character image.
    UnloadTexture(mainCharacter);

    CloseWindow();
    return 0;
}