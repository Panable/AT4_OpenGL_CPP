#pragma once
#include "ResourceManager.h"
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    GameState m_State;
    bool m_Keys[1024];
    unsigned int m_Width, m_Height;

    Game(unsigned int width, unsigned int height);

    ~Game();

    void Init();

    void ProcessInput(float dt);

    void Update(float dt);

    void Render();
};
