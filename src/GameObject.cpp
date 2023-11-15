#include "GameObject.h"


#include <utility>

GameObject::GameObject()
        : m_Position(0.0f, 0.0f), m_Size(1.0f, 1.0f), m_Velocity(0.0f), m_Color(1.0f), m_Rotation(0.0f),
          m_IsSolid(false), m_Destroyed(false), m_Sprite(nullptr)
{}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, std::shared_ptr<Texture> sprite, glm::vec3 color,
                       glm::vec2 velocity)
        : m_Position(pos), m_Size(size), m_Velocity(velocity), m_Color(color), m_Rotation(0.0f), m_IsSolid(false),
          m_Destroyed(false), m_Sprite(std::move(sprite))
{

}


void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(m_Sprite, m_Position, m_Size, m_Rotation, m_Color);
}
