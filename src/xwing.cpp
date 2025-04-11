#include "xwing.hpp"

Xwing::Xwing()
{
    image = LoadTexture("graphics/falcon.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 70;
    lastFireTime = 0.0;
    laserSound = LoadSound("audio/laser.mp3");
}

Xwing::~Xwing() {
    UnloadTexture(image);
    UnloadSound(laserSound);
}

void Xwing::Draw() {
    DrawTextureV(image, position, WHITE);
}

void Xwing::MoveLeft() {
    position.x -= 7;
    if(position.x < 15) {
        position.x = 15;
    }
}

void Xwing::MoveRight() {
    position.x += 7;
    if(position.x > GetScreenWidth() - image.width - 15) {
        position.x = GetScreenWidth() - image.width - 15;
    }
}

void Xwing::FireLaser()
{
    if(GetTime() - lastFireTime >= 0.35) {
        PlaySound(laserSound);
        lasers.push_back(Laser({position.x + image.width/2 - 2, position.y}, -6, 1));
        lastFireTime = GetTime();
    }
}

void Xwing::Reset() {
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height - 70;
    lasers.clear();
}

Rectangle Xwing::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}
