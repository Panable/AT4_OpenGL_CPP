#pragma once
#include "ResourceManager.h"
#include "GameLevel.h"
#include "BallObject.h"

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    bool m_IsInitialized;
    GameState m_State;
    bool m_Keys[1024];
    unsigned int m_Width, m_Height;

    std::vector<GameLevel> m_Levels;
    unsigned int m_Level;

    void SetPlayer(const float& x, const float& y);

    void Init();

    void ProcessInput(float dt);

    void Update(float dt);

    void Render();

public:

    Game(unsigned int width, unsigned int height);

    ~Game();

    std::string GetCoordinates();

private:
    void DoCollisions();

    static bool CheckCollision(BallObject& one, GameObject& two);

    static float Clamp(float value, float min, float max);
};
