#include "BallObject.h"

glm::vec2 BallObject::Move(float dt, unsigned int windowWidth)
{
    if (m_Stuck)
        return m_Position;

    MoveBall(dt);
    HandleWallCollisions(windowWidth);
    return m_Position;
}

void BallObject::MoveBall(float dt)
{
    m_Position += m_Velocity * dt;
}

void BallObject::HandleWallCollisions(unsigned int windowWidth)
{
    bool hitLeftEdge = m_Position.x <= 0.0f;
    bool hitRightEdge = m_Position.x + m_Size.x >= windowWidth;
    bool hitTopEdge = m_Position.y <= 0.0f;

    if (hitLeftEdge)
    {
        HandleLeftEdgeCollision();
    }
    else if (hitRightEdge)
    {
        HandleRightEdgeCollision(windowWidth);
    }
    else if (hitTopEdge)
    {
        HandleTopEdgeCollision();
    }
}

void BallObject::HandleTopEdgeCollision()
{
    m_Velocity.y = -m_Velocity.y;
    m_Position.y = 0.0f;
}

void BallObject::HandleRightEdgeCollision(unsigned int windowWidth)
{
    m_Velocity.x = -m_Velocity.x;
    m_Position.x = windowWidth - m_Size.x;
}

void BallObject::HandleLeftEdgeCollision()
{
    m_Velocity.x = -m_Velocity.x;
    m_Position.x = 0.0f;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    m_Position = position;
    m_Velocity = velocity;
}

BallObject::BallObject()
        : GameObject(), m_Radius(12.5), m_Stuck(true)
{

}

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, std::shared_ptr<Texture> sprite)
        : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity), m_Radius(radius),
          m_Stuck(true)
{

}
