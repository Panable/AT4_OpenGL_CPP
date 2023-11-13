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
    auto shader = ResourceManager::LoadShader("shaders/sprite/sprite.vs", "shaders/sprite/sprite.fs", nullptr,
                                              "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_Width), static_cast<float>(m_Height), 0.0f, -1.0f,
                                      1.0f);
    shader.Activate();
    shader.Set1i("image", 0);
    shader.SetMatrix4f("projection", projection);
    Renderer = new SpriteRenderer(shader);

    ResourceManager::LoadTexture("texture/pop_cat", true, "cat");
}

void Game::ProcessInput(float dt)
{

}

void Game::Update(float dt)
{

}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f),
                         45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
