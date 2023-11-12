#pragma once

#include "Debug.h"
#include <string>
#include "glad/glad.h"
#include "stb_image.h"

class Texture
{
public:
    Texture(const std::string& path);
    virtual ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const
    {
        return m_Width;
    }

    inline int GetHeight() const
    {
        return m_Height;
    }

protected:
private:
    unsigned int   m_Id;
    std::string    m_FilePath;
    int m_colorChannel;
    int            m_Width, m_Height;

};

