#include "game.hpp"
#include <iostream>
#include <fstream>

Game::Game()
{
    music = LoadMusicStream("audio/music.mp3");
    explosionSound = LoadSound("audio/explosion.mp3");
    hitSound = LoadSound("audio/hit.mp3");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game() {
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
    UnloadSound(hitSound);
}

void Game::Update() {
    if (run) {
        for(auto& laser: xwing.lasers) {
            laser.Update();
        }

        SpawnTie();
        MoveTies();
        TieShootLaser();

        for(auto& laser: tieLasers) {
            laser.Update();
        }

        CheckForCollisions();

        if (score < 0) {
            score = 0;
        }
    }   
    else {
        if(IsKeyDown(KEY_ENTER)) {
            Reset();
            InitGame();
        }
    }
}

void Game::Draw() {
    xwing.Draw();
    for(auto& laser: xwing.lasers) {
        laser.Draw();
    }

    for(auto& tie: ties) {
        tie.Draw();
    }

    for(auto& laser: tieLasers) {
        laser.Draw();
    }

    DeleteInactiveLasers();
    DeleteTies();
}

void Game::HandleInput() {
    if(run) {
        if(IsKeyDown(KEY_LEFT)) {
            xwing.MoveLeft();
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            xwing.MoveRight();
        }
        if(IsKeyDown(KEY_SPACE)) {
            xwing.FireLaser();
        }
    }
}

void Game::DeleteInactiveLasers()
{
    for(auto it = xwing.lasers.begin(); it != xwing.lasers.end();){
        if(!it -> active) {
            it = xwing.lasers.erase(it);
        }
        else {
            ++it;
        }
    }

    for(auto it = tieLasers.begin(); it != tieLasers.end();){
        if(!it -> active) {
            it = tieLasers.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Game::DeleteTies() {
    for(auto it = ties.begin(); it != ties.end();){
        if(!it -> alive) {
            it = ties.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Game::CheckForCollisions()
{
    //Falcon lasers
    for(auto& laser: xwing.lasers) {
        auto it = ties.begin();
        while(it != ties.end()) {
            if (CheckCollisionRecs(it -> getRect(), laser.getRect())) {
                PlaySound(explosionSound);
                it = ties.erase(it);
                laser.active = false;
                score += 100;
                CheckForHighScore();
            }
            else {++it;}
        }
    }

    //Tie lasers
    for(auto& laser: tieLasers) {
        if(CheckCollisionRecs(laser.getRect(), xwing.getRect())) {
            laser.active = false;
            lives--;
            PlaySound(hitSound);
            if (lives == 0) {
                GameOver();
            }
        }
    }
}

std::vector<Tiefighter> Game::CreateTies()
{   
    std::vector<Tiefighter> ties;

    float x = GetRandomValue(50,700);
    float y = GetRandomValue(-20, -5);
    ties.push_back(Tiefighter({x,y}));

    return ties;
}

void Game::SpawnTie() {
    double currentTime = GetTime();
    int spawnTimer = GetRandomValue(2, 6);

    if(currentTime - lastTieSpawned >= spawnTimer) {
        float x = GetRandomValue(100,700);
        float y = GetRandomValue(-20, -5);
        ties.push_back(Tiefighter({x,y}));
        lastTieSpawned = GetTime();
    }
}

void Game::MoveTies() {
    for(auto& tie:ties) {
        tie.Update(tieDirection);

        if (tie.position.y == GetScreenHeight() - 10) {
            std::cout << "A Tiefighter got passed!" << std::endl;
            score -= 500;
        }
    }
}

void Game::TieShootLaser(){   
    double currentTime = GetTime();
    if (currentTime - timeLastTieFired >= tieLaserInterval && !ties.empty()){
        int randomIndex = GetRandomValue(0, ties.size() - 1);
        Tiefighter& tie = ties[randomIndex];

        if (ties.size() == 1 && currentTime - timeLastTieFired >= tieLaserInterval * 3){
            tieLasers.push_back(Laser({tie.position.x + tie.image.width/2, 
                tie.position.y + tie.image.height}, 6, 0));
        }
        else{
            tieLasers.push_back(Laser({tie.position.x + tie.image.width/2, 
                                        tie.position.y + tie.image.height}, 6, 0));
        }

        timeLastTieFired = GetTime();
    }
}

void Game::GameOver() {
    run = false;
}

void Game::Reset() {
    xwing.Reset();
    ties.clear();
    tieLasers.clear();
}

void Game::InitGame() {
    ties = CreateTies();
    tieDirection = 1;
    timeLastTieFired = 0;
    lastTieSpawned = 0;
    lives = 3;
    run = true;
    score = 0;
    highscore = LoadHighscoreFromFile();
}

void Game::CheckForHighScore() {
    if (score > highscore) {
        highscore = score;
        SaveHighscoreToFile(highscore);
    }
}

void Game::SaveHighscoreToFile(int highscore) {
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    }
    else {
        std::cerr << "Failed to save highscore to file!" << std::endl;
    }
}

int Game::LoadHighscoreFromFile() {
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    }
    else {
        std:: cerr << "Failed to load highscore!" << std::endl;
    }
    return loadedHighscore;
}
