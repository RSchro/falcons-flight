#pragma once
#include <raylib.h>

class Tiefighter {
    public:
        Tiefighter(Vector2 position);
        void Update(int direction);
        void Draw();
        Rectangle getRect();
        bool alive;
        Texture2D image;
        Vector2 position;
    private:
        int tieDirection;
};