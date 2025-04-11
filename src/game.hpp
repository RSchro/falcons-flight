#pragma once
#include "xwing.hpp"
#include "tiefighter.hpp"

class Game {
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int lives;
        int score;
        int highscore;
        Music music;
        
        private:
        void DeleteInactiveLasers();
        void DeleteTies();
        void CheckForCollisions();
        void MoveTies();
        void TieShootLaser();
        void SpawnTie();
        void GameOver();
        void Reset();
        void InitGame();
        void CheckForHighScore();
        void SaveHighscoreToFile(int highscore);
        int LoadHighscoreFromFile();
        int tieDirection;
        std::vector<Tiefighter> CreateTies();
        Xwing xwing;
        std::vector<Tiefighter> ties;
        std::vector<Laser> tieLasers;
        constexpr static float tieLaserInterval = 0.5;
        float timeLastTieFired;
        float lastTieSpawned;
        Sound explosionSound;
        Sound hitSound;
};