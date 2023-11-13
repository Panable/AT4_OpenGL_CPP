#pragma once

#include "Debug.h"
#include <string>
#include "glad/glad.h"
#include "stb_image.h"

/**
 * Stores and configures a texture in OpenGL
 * Additionally, provides utility functions
 */
class Texture {
public:

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const {
        return m_Width;
    }

    inline int GetHeight() const {
        return m_Height;
    }

    unsigned int m_Id;
    unsigned int m_WrapS; // wrapping mode on S axis
    unsigned int m_WrapT; // wrapping mode on T axis
    unsigned int m_FilterMin; // filtering mode if texture pixels < screen pixels
    unsigned int m_FilterMax; // filtering mode if texture pixels > screen pixels
    unsigned int m_InternalFormat;
    unsigned int m_ImageFormat;

public:
    Texture(const std::string &path, const bool& alpha = false);
    virtual ~Texture();

private:
    std::string m_FilePath;
    int m_ColorChannel;
    int m_Width, m_Height;
};

