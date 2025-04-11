#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Xwing{
    public:
        Xwing();
        ~Xwing();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
        void Reset();
        Rectangle getRect();
        std::vector<Laser> lasers;

    private:
        Texture2D image;
        Vector2 position;
        double lastFireTime;
        Sound laserSound;
};