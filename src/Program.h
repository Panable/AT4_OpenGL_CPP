// Program.h
#pragma once
#include "OpenGL/Texture.h"
#include "detail/type_mat.hpp"
#include "detail/type_vec.hpp"
#include "stb_image.h"
#include "OpenGL/Debug.h"
#include <fstream>
#include <iostream>
#include <sstream>

// OPENGL STUFF
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// MY INCLUDES
#include "OpenGL/IndexBufferObject.h"
#include "OpenGL/ShaderProgram.h"
#include "OpenGL/VertexArrayObject.h"
#include "OpenGL/VertexBufferObject.h"
#include "Game.h"
#include "ResourceManager.h"

namespace Program {
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    int Run();
}
