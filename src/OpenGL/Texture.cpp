#include "Texture.h"
#include "Debug.h"
#include <iostream>

Texture::Texture(const std::string &path, const bool &alpha) : m_FilePath(path), m_InternalFormat(GL_RGB),
                                                               m_ImageFormat(GL_RGB),
                                                               m_WrapS(GL_REPEAT), m_WrapT(GL_REPEAT),
                                                               m_FilterMin(GL_LINEAR),
                                                               m_FilterMax(GL_LINEAR)
{
    if (alpha)
    {
        m_InternalFormat = GL_RGBA;
        m_ImageFormat = GL_RGBA;
    }

    //STBI IMAGE LOADING
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_ColorChannel, 4);

    if (!data)
    {
        std::cout << "ERROR: Failed to load texture at " << path << std::endl;
        return;
    }

    //OpenGL Functions
    GLCall(glGenTextures(1, &m_Id));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_Id));

    //Scaling up/down, what pixel to choose
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_FilterMax));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_FilterMin));

    //Setting outside coord range, repeat.
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_WrapS));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_WrapT));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

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
