#include "tiefighter.hpp"
#include <iostream>

Tiefighter::Tiefighter(Vector2 position)
{
    this -> position = position;
    image = LoadTexture("graphics/tie.png");
    alive = true;
    tieDirection = 1;
}

void Tiefighter::Draw() {
    if(alive){
        DrawTextureV(image, position, WHITE);
    }
}

Rectangle Tiefighter::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Tiefighter::Update(int direction) {
    position.y += direction;

    if(alive) {
        if(position.y > GetScreenHeight()) {
            alive = false;
        }
    }
}


