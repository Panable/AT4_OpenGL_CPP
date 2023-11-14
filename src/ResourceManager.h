#pragma once

#include <map>
#include <string>
#include "OpenGL/ShaderProgram.h"
#include "OpenGL/Texture.h"

/**
 * Singleton
 * Stores Texture/Shaders
 * Has functions to load Texture/Shaders
 */
class ResourceManager
{
public:

    //Resource storage
    static std::map<std::string, ShaderProgram> Shaders;
    static std::map<std::string, Texture> Textures;

    /**
     * Loads and generates a shader from a file.
     * @param vShaderFile vertex shader file path
     * @param fShaderFile fragment shader file path
     * @param gShaderFile geometry shader file path
     * @param name name of the shader
     * @return ShaderProgram object
     */
    static ShaderProgram &
    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, const std::string &name);

    /**
     * Gets a shader by name
     * @param name Name of the shader
     * @return ShaderProgram object
     */
    static ShaderProgram & GetShader(std::string name);

    /**
     * Loads and generates a texture from disk
     * @param file File path of the texture
     * @param alpha Does the texture have alpha values?
     * @param name The name of the image to store
     * @return
     */
    static Texture & LoadTexture(const char *file, bool alpha, std::string name);

    /**
     * Get a texture by name
     * @param name Name of the texture
     * @return Texture Object
     */
    static Texture & GetTexture(std::string name);

    /**
     * Properly de-allocates all loaded resources
     */
    static void Clear();

private:
    //All members/functions publicly avaliable -> private constructor
    ResourceManager()
    {}

    //loads and generates shader from file
    static ShaderProgram
    LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);

    //loads a single texture from file
    static Texture LoadTextureFromFile(const char *file, bool alpha);
};
