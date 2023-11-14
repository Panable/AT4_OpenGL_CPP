#include "ResourceManager.h"

std::map<std::string, std::shared_ptr<ShaderProgram>> ResourceManager::Shaders;
std::map<std::string, std::shared_ptr<Texture>> ResourceManager::Textures;

std::shared_ptr<ShaderProgram> ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name)
{
    Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const char* file, bool alpha, const std::string& name)
{
    Textures[name] = LoadTextureFromFile(file, alpha);
    return Textures[name];
}

std::shared_ptr<ShaderProgram> ResourceManager::GetShader(const std::string& name)
{
    return Shaders[name];
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // Properly delete all shaders
    for (auto& iter : Shaders)
        glDeleteProgram(iter.second->m_Id);

    // Properly delete all textures
    for (auto& iter : Textures)
        glDeleteTextures(1, &iter.second->m_Id);
}

std::shared_ptr<ShaderProgram> ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    if (gShaderFile)
        return std::make_shared<ShaderProgram>(vShaderFile, fShaderFile, gShaderFile);
    else
        return std::make_shared<ShaderProgram>(vShaderFile, fShaderFile);
}

std::shared_ptr<Texture> ResourceManager::LoadTextureFromFile(const char* file, bool alpha)
{
    return std::make_shared<Texture>(file, alpha);
}
