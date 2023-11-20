#include <vector>
#include "Game.h"
#include "SpriteRenderer.h"
#include "GLFW/glfw3.h"
#include "BallObject.h"

//Constants
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);
const float BALL_RADIUS = 12.5f;
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);

GameObject* player;
BallObject* Ball;
//GameObject* player2;

Game::Game(unsigned int width, unsigned int height)
        : m_IsInitialized(false), m_State(GAME_ACTIVE), m_Keys(), m_Width(width), m_Height(height)
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
    ResourceManager::LoadTexture("res/texture/paddle.png", true, "paddle");
    ResourceManager::LoadTexture("res/texture/pop_cat.png", true, "cat");
    ResourceManager::LoadTexture("res/texture/background.jpg", true, "background");
    ResourceManager::LoadTexture("res/texture/block.png", true, "block");
    ResourceManager::LoadTexture("res/texture/block_solid.png", true, "block_solid");


    glm::vec2 playerPos = glm::vec2(
            m_Width / 2.0f - PLAYER_SIZE.x / 2.0f,
            m_Height - PLAYER_SIZE.y
            );
    player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"), glm::vec3(1.0f));
    //player2 = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"), glm::vec3(1.0f));

    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);

    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("cat"));


    //Load Level
    GameLevel one;
    one.Load("res/levels/one.level", m_Width, m_Height / 2);
    m_Levels.push_back(one);

    // Initialize renderer after setting up shader and loading texture
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    m_IsInitialized = true;
}

std::string Game::GetCoordinates()
{
    auto x = std::to_string(player->m_Position.x);
    auto y = std::to_string(player->m_Position.y);
    return x + "," + y;
}

void Game::ProcessInput(float dt)
{
    if (m_State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        if (m_Keys[GLFW_KEY_A])
        {
            if (player->m_Position.x >= 0.0f)
            {
                player->m_Position.x -= velocity;
                if (Ball->m_Stuck)
                    Ball->m_Position.x -= velocity;
            }
        }
        if (m_Keys[GLFW_KEY_D])
        {
            if (player->m_Position.x <= m_Width - player->m_Size.x)
            {
                player->m_Position.x += velocity;
                if (Ball->m_Stuck)
                    Ball->m_Position.x += velocity;
            }
        }

        if (m_Keys[GLFW_KEY_SPACE])
            Ball->m_Stuck = false;

    }
}

void Game::Update(float dt)
{
    Ball->Move(dt, m_Width);
}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(m_Width, m_Height), 0.0f);

    m_Levels[m_Level].Draw(*Renderer);
    player->Draw(*Renderer);
    //player2->Draw(*Renderer);

    Ball->Draw(*Renderer);
}

void Game::SetPlayer(const float& x, const float& y)
{
    //player2->m_Position.x = x;
   // player2->m_Position.y = y;
}
