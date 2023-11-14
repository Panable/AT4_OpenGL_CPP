#include "ShaderProgram.h"
#include "Debug.h"

ShaderProgram::ShaderProgram(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
{
    // GET FILE CONTENTS
    const std::string vertexShaderString = GetFileContents(vertexShaderFilePath);
    const std::string fragmentShaderString = GetFileContents(fragmentShaderFilePath);

    const char* vertexShaderCode = vertexShaderString.c_str();
    const char* fragmentShaderCode = fragmentShaderString.c_str();

    std::cout << fragmentShaderCode << std::endl;

    // CREATE THE SHADERS
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // PUSH CODE INTO THE CREATED SHADERS
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);

    // COMPILE SHADERS
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // ERROR TESTING COMPILATION
    CompileErrors(vertexShader, "VERTEX");
    CompileErrors(fragmentShader, "FRAGMENT");

    // CREATE SHADER PROGRAM
    m_Id = glCreateProgram();

    // ATTACH SHADERS
    glAttachShader(m_Id, vertexShader);
    glAttachShader(m_Id, fragmentShader);

    // LINKING
    glLinkProgram(m_Id);

    // ERROR TESTING SHADER LINKING
    CompileErrors(m_Id, "LINKING");
    std::cout << "Compiling ShaderProgram" << std::endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

ShaderProgram::ShaderProgram(const char* vertexShaderFilePath, const char* fragmentShaderFilePath, const char* geometryShaderFilePath)
{
    // GET FILE CONTENTS
    const std::string vertexShaderString = GetFileContents(vertexShaderFilePath);
    const std::string fragmentShaderString = GetFileContents(fragmentShaderFilePath);
    const std::string geometryShaderString = GetFileContents(geometryShaderFilePath);

    const char* vertexShaderCode = vertexShaderString.c_str();
    const char* fragmentShaderCode = fragmentShaderString.c_str();
    const char* geometryShaderCode = geometryShaderString.c_str();

    // CREATE THE SHADERS
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

    // PUSH CODE INTO THE CREATED SHADERS
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glShaderSource(geometryShader, 1, &geometryShaderCode, NULL);

    // COMPILE SHADERS
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    glCompileShader(geometryShader);

    // ERROR TESTING COMPILATION
    CompileErrors(vertexShader, "VERTEX");
    CompileErrors(fragmentShader, "FRAGMENT");
    CompileErrors(geometryShader, "GEOMETRY");

    // CREATE SHADER PROGRAM
    m_Id = glCreateProgram();

    // ATTACH SHADERS
    glAttachShader(m_Id, vertexShader);
    glAttachShader(m_Id, fragmentShader);
    glAttachShader(m_Id, geometryShader);

    // LINKING
    glLinkProgram(m_Id);

    // ERROR TESTING SHADER LINKING
    CompileErrors(m_Id, "LINKING");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
}

void ShaderProgram::SetVector4f(const char* name, const glm::vec4& value) const
{
    const int location = glGetUniformLocation(m_Id, name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::SetVector3f(const char* name, const glm::vec3& value) const
{
    const int location = glGetUniformLocation(m_Id, name);
    glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::Set1i(const char* name, int value) const
{
    if (glGetUniformLocation(m_Id, name) == -1)
        std::cout << "ERROR NO UNIFORM WITH NAME " << name << std::endl;
    GLCall(glUniform1i(glGetUniformLocation(m_Id, name), value));
}

ShaderProgram::~ShaderProgram()
{
    std::cout << "Destroying ShaderProgram" << std::endl;
    this->Delete();
}

void ShaderProgram::CompileErrors(const unsigned int shader, const char* type) const
{
    // Stores status of compilation
    GLint hasCompiled;
    // Character array to store error message in
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    }
}

std::string ShaderProgram::GetFileContents(const char* path) const
{
    std::ifstream     shaderFile(path);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}

void ShaderProgram::Delete() const
{
    glDeleteProgram(m_Id);
}

void ShaderProgram::Activate() const
{
    glUseProgram(m_Id);
}

void ShaderProgram::SetMatrix4f(const char* name, const glm::mat4& value, const unsigned int& count, const bool& transpose) const
{
	const int location = glGetUniformLocation(m_Id, name);
    glUniformMatrix4fv(location, count, transpose, glm::value_ptr(value));
}
