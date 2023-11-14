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

    // Load texture
    ResourceManager::LoadTexture("res/texture/pop_cat.png", true, "cat");

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
    Renderer->DrawSprite(ResourceManager::GetTexture("cat"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f),
                         45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
