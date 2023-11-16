#include "SpriteRenderer.h"

#include <utility>
#include "OpenGL/VertexArrayObject.h"

#define ARRAY_LEN(xs) sizeof(xs)/sizeof(xs[0])

SpriteRenderer::SpriteRenderer(std::shared_ptr<ShaderProgram> shader)
        : m_Shader(shader)
{
    this->InitRenderData();
}

SpriteRenderer::~SpriteRenderer()
{

}

void SpriteRenderer::DrawSprite(const std::shared_ptr<Texture>& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    m_Shader->Activate();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_Shader->SetMatrix4f("model", model);
    m_Shader->SetVector3f("spriteColor", color);

    texture->Bind(0);
    m_QuadVAO.Bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
    m_QuadVAO.Unbind();
}

void SpriteRenderer::InitRenderData()
{
    m_QuadVAO.Bind();

    float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };

    VertexBufferObject VBO(vertices, sizeof(vertices));
    m_QuadVAO.LinkAttrib(VBO, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*) 0);
    m_QuadVAO.Unbind();
    VBO.Unbind();
}


