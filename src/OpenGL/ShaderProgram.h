﻿#pragma once
#include "detail/type_mat.hpp"
#include "glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ShaderProgram
{
public:
    ShaderProgram(const char *vertexShaderFilePath, const char *fragmentShaderFilePath, const char *gShaderFilePath);

    unsigned int m_Id;
public:
	ShaderProgram(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
	~ShaderProgram();
	void Activate() const;
	void SetVector4f(const char* name, const glm::vec4& value) const;
    void SetVector3f(const char* name, const glm::vec3& value) const;
    void Set1i(const char* name, int value) const;
    void SetMatrix4f(const char* name, const glm::mat4& value, const unsigned int& count = 1, const bool& transpose = false) const;
private:
	void CompileErrors(unsigned int shader, const char* type) const;
	std::string GetFileContents(const char* path) const;
	void Delete() const;

};
