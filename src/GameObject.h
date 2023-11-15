#pragma once


#include <memory>
#include "glm/glm.hpp"
#include "OpenGL/Texture.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

/**
 * Container for holding minimum state of an object in the game
 */
class GameObject
{
public:
    glm::vec2 m_Position, m_Size, m_Velocity;
    glm::vec3 m_Color;
    float m_Rotation;
    float m_IsSolid;
    bool m_Destroyed;

    std::shared_ptr<Texture> m_Sprite;

    virtual void Draw(SpriteRenderer& renderer);

public:
    GameObject();

    GameObject(glm::vec2 pos, glm::vec2 size, std::shared_ptr<Texture> sprite, glm::vec3 color = glm::vec3(1.0f),
               glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
};
