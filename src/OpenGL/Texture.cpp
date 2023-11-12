#include "Texture.h"
#include "Debug.h"
#include <iostream>

Texture::Texture(const std::string& path) : m_FilePath(path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_colorChannel, 4);

    if (!data)
    {
        std::cout << "ERROR: Failed to load texture at " << path << std::endl;
        return;
    }

    GLCall(glGenTextures(1, &m_Id));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_Id));

    //Scaling up/down, what pixel to choose
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    //Setting outside coord range, repeat.
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data) );

    Unbind();

    stbi_image_free(data);
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_Id));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_Id));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
