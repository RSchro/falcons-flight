#include "laser.hpp"
#include <iostream>

Laser::Laser(Vector2 position, int speed, bool faction)
{   
    
    this -> position = position;
    this -> speed = speed;
    this -> faction = faction;
    active = true;
}

void Laser::Draw() {
    Color bolt;
    if (faction == 1) {
        bolt = {242, 41, 41,255};
    }
    else if (faction == 0) {
        bolt = {52, 237, 43, 255};
    }

    if(active){
        DrawEllipse(position.x, position.y, 2.0f, 7.0f, bolt);
    }
}

Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}

void Laser::Update() {
    position.y += speed;
    if(active){
        if(position.y > GetScreenHeight() || position.y < 0) {
            active = false;
            std::cout << "Laser Inactive" << std::endl;
        }
    }
}