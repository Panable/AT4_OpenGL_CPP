#pragma once
#include "GameObject.h"

class BallObject : public GameObject
{
public:
    glm::vec2 Move(float dt, unsigned int windowWidth);
    void Reset(glm::vec2 position, glm::vec2 velocity);

    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, std::shared_ptr<Texture> sprite);
public:
    float m_Radius;
    bool m_Stuck;

private:
    void HandleWallCollisions(unsigned int windowWidth);

    void MoveBall(float dt);

    void HandleLeftEdgeCollision();

    void HandleRightEdgeCollision(unsigned int windowWidth);

    void HandleTopEdgeCollision();
};
