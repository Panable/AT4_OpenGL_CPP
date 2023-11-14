#include "ResourceManager.h"

std::map<std::string, ShaderProgram> ResourceManager::Shaders;
std::map<std::string, Texture> ResourceManager::Textures;

ShaderProgram& ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile,
                                            const std::string &name)
{
    ShaderProgram program = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    auto result = Shaders.emplace(name, program);
    return Shaders.find(name)->second;
}

Texture& ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
    Texture texture = LoadTextureFromFile(file, alpha);
    Textures.emplace(name, texture);
    return Textures.find(name)->second;
}


ShaderProgram& ResourceManager::GetShader(std::string name)
{
    auto it = Shaders.find(name);

    if (it != Shaders.end()) {
        // Texture found, return a reference to it
        return it->second;
    } else {
        // Handle the case when the texture is not found
        // For simplicity, you can throw an exception, or return a default texture, etc.
        throw std::runtime_error("Shader not found: " + name);
    }
}

Texture& ResourceManager::GetTexture(std::string name)
{
    auto it = Textures.find(name);

    if (it != Textures.end()) {
        // Texture found, return a reference to it
        return it->second;
    } else {
        // Handle the case when the texture is not found
        // For simplicity, you can throw an exception, or return a default texture, etc.
        throw std::runtime_error("Texture not found: " + name);
    }
}

void ResourceManager::Clear()
{
// (properly) delete all shaders
    for (auto iter: Shaders)
        glDeleteProgram(iter.second.m_Id);
    // (properly) delete all textures
    for (auto iter: Textures)
        glDeleteTextures(1, &iter.second.m_Id);
}

ShaderProgram
ResourceManager::LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    if (gShaderFile)
        return {vShaderFile, fShaderFile, gShaderFile};
    else
        return {vShaderFile, fShaderFile};
}


Texture ResourceManager::LoadTextureFromFile(const char *file, bool alpha)
{
    return {file, alpha};
}
