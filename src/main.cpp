#include <iostream>
#include "raylib.h"
#include <math.h>

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

    // Loading default pose of main character.
    const int mainCharacterWidth = fullPackWidth / amountOfColumns;
    const int mainCharacterHeight = fullPackHeigth / amountOfRows;

    Rectangle sourceMainCharacterDefaultPose = Rectangle {
        0,
        0,
        (float)mainCharacterWidth,
        (float)mainCharacterHeight
    };

    // Place Character in the center of Window
    Rectangle defaultMainCharacterPosition = Rectangle {
        (float)screenWidth / 2.0f - mainCharacterWidth / 2.0f,
        (float)screenHeight / 2.0f - mainCharacterHeight / 2.0f, 
        (float)mainCharacterWidth / 1.0f, 
        (float)mainCharacterHeight
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(mainCharacter, 
            sourceMainCharacterDefaultPose, 
            defaultMainCharacterPosition, 
            Vector2{ defaultMainCharacterPosition.width, defaultMainCharacterPosition.height }, 
            0.0f, 
            WHITE);

        EndDrawing();
    }

    // Free memory by unloading character image.
    UnloadTexture(mainCharacter);

    CloseWindow();
    return 0;
}