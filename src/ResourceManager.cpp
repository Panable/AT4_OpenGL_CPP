#include "ResourceManager.h"

std::map<std::string, std::unique_ptr<ShaderProgram>> ResourceManager::Shaders;
std::map<std::string, std::unique_ptr<Texture>> ResourceManager::Textures;


std::unique_ptr<ShaderProgram>&
ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile,
                            const std::string& name)
{
    std::unique_ptr<ShaderProgram> shader = std::make_unique<ShaderProgram>(
            LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile));
    Shaders[name] = std::move(shader);
    return Shaders[name];
}

std::unique_ptr<Texture>& ResourceManager::LoadTexture(const char* file, bool alpha, const std::string& name)
{
    std::unique_ptr<Texture> texture = std::make_unique<Texture>(LoadTextureFromFile(file, alpha));
    Textures[name] = std::move(texture);
    return Textures[name];
}


std::unique_ptr<ShaderProgram>& ResourceManager::GetShader(const std::string& name)
{
    return Shaders[name];
}

std::unique_ptr<Texture>& ResourceManager::GetTexture(const std::string& name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
// (properly) delete all shaders
    for (auto& iter: Shaders)
        glDeleteProgram(iter.second->m_Id);
    // (properly) delete all textures
    for (auto& iter: Textures)
        glDeleteTextures(1, &iter.second->m_Id);
}

ShaderProgram
ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    if (gShaderFile)
        return {vShaderFile, fShaderFile, gShaderFile};
    else
        return {vShaderFile, fShaderFile};
}


Texture ResourceManager::LoadTextureFromFile(const char* file, bool alpha)
{
    return {file, alpha};
}
