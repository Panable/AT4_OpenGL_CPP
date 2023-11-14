#pragma once

#include <memory>
#include "OpenGL/ShaderProgram.h"
#include "OpenGL/Texture.h"
#include "OpenGL/VertexArrayObject.h"

/**
 * Renders sprites!
 */
class SpriteRenderer
{
public:
    SpriteRenderer(std::shared_ptr<ShaderProgram> shader);
    ~SpriteRenderer();

    /**
     * Draw a sprite
     * @param texture the texture of the sprite
     * @param size the size of the sprite
     * @param rotate the rotation of the sprite
     * @param color the color of the sprite
     */
    void DrawSprite(const std::shared_ptr<Texture>& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));

private:
    std::shared_ptr<ShaderProgram> m_Shader;
    VertexArrayObject m_QuadVAO;

    void InitRenderData();

};
