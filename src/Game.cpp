#include <vector>
#include "Game.h"
#include "SpriteRenderer.h"

Game::Game(unsigned int width, unsigned int height)
        : m_State(GAME_ACTIVE), m_Keys(), m_Width(width), m_Height(height)
{

}

Game::~Game()
{

}

SpriteRenderer *Renderer;

void Game::Init()
{

    // Load shader
    ResourceManager::LoadShader("res/shaders/sprite/sprite.vs", "res/shaders/sprite/sprite.fs", nullptr, "sprite");

    // Set up shader parameters
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_Width), static_cast<float>(m_Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite")->Activate();
    ResourceManager::GetShader("sprite")->Set1i("image", 0);
    ResourceManager::GetShader("sprite")->SetMatrix4f("projection", projection);


    // load textures
    ResourceManager::LoadTexture("res/texture/pop_cat.png", true, "cat");

    ResourceManager::LoadTexture("res/texture/background.jpg", true, "background");
    ResourceManager::LoadTexture("res/texture/block.png", true, "block");
    ResourceManager::LoadTexture("res/texture/block_solid.png", true, "block_solid");

    GameLevel one;
    one.Load("res/levels/one.level", m_Width, m_Height / 2);

    m_Levels.push_back(one);

    // Initialize renderer after setting up shader and loading texture
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
}

void Game::ProcessInput(float dt)
{

}

void Game::Update(float dt)
{

}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(m_Width, m_Height), 0.0f);

    m_Levels[m_Level].Draw(*Renderer);
}
