#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <string>
#include "game.hpp"
#include "tiefighter.hpp"

std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main() 
{
    Color grey = {33,33,33,255};
    Color red = {214, 59, 47, 255};
    int windowWidth = 750;
    int windowHeight = 700;
    int offset = 50;
    bool start = true;
    
    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Falcon's Flight");

    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    Texture2D rebelImage = LoadTexture("graphics/rebel.png");

    InitAudioDevice();
    SetTargetFPS(60);
    
    Game game;
    
    while(WindowShouldClose() == false) {
        if (start) {
            game.run = false;
            if(IsKeyDown(KEY_ENTER)) {
                game.run = true;
                start = false;
            }
        }
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, red);
        if (game.run) {
            DrawTextEx(font, "Level 01", {570, 740}, 34, 2, red);
        }
        else {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, red);
            DrawTextEx(font,"PRESS ENTER TO START", {(float)GetScreenWidth() / 5 + 30, (float)GetScreenHeight() / 2}, 42, 2, red);
        }
        
        float x = 50.0;
        for (int i = 0; i < game.lives; i++) {
            DrawTextureV(rebelImage, {x, 745}, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, red);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font,scoreText.c_str(), {50,40}, 34, 2, red);

        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, red);
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font,highscoreText.c_str(), {655, 40}, 34, 2, red);

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
}