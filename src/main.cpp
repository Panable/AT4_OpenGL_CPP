// STD LIBRARY
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

#define ARRAY_LEN(xs) sizeof(xs)/sizeof(xs[0])
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
int          addZ = 0;
int          addX = 0;
float        lastX = 400, lastY = 300;
float        yaw = 0.0f;
float        pitch = 0.0f;
bool         firstMouse = true;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float     deltaTime = 0.0f; // Time between current frame and last frame
float     lastFrame = 0.0f; // Time of last frame

int main()
{
    // Initialize GLFW and set opengl version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;

    float pyramid[] = {

        //front side
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
         0.0f,  0.5f,  0.0f, 0.5f, 1.0f,        

        //back side
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.0f,  0.5f,  0.0f, 0.5f, 1.0f,        

        //left side
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
         0.0f,  0.5f,  0.0f, 0.5f, 1.0f,

        //right side
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.0f,  0.5f,  0.0f, 0.5f, 1.0f,

        //bottom side
        -0.5f,  -0.5f,  -0.5f,  0.0f,  1.0f, 
         0.5f,  -0.5f,  -0.5f,  1.0f,  1.0f, 
         0.5f,  -0.5f,   0.5f,  1.0f,  0.0f,
         0.5f,  -0.5f,   0.5f,  1.0f,  0.0f, 
        -0.5f,  -0.5f,   0.5f,  0.0f,  0.0f, 
        -0.5f,  -0.5f,  -0.5f,  0.0f,  1.0f,
     };


    // DATA
    float vertices[] = {

    //         VERTEX           Texture Coord
    //    X       Y        Z ,   X      Y 
        -0.5f,  -0.5f,  -0.5f,  0.0f,  0.0f,  //1
         0.5f,  -0.5f,  -0.5f,  1.0f,  0.0f,  //2
         0.5f,   0.5f,  -0.5f,  1.0f,  1.0f,  //3
         0.5f,   0.5f,  -0.5f,  1.0f,  1.0f,  //4 
        -0.5f,   0.5f,  -0.5f,  0.0f,  1.0f,  //5 
        -0.5f,  -0.5f,  -0.5f,  0.0f,  0.0f,  //1 

        //BACK SIDE ^


        -0.5f,  -0.5f,   0.5f,  0.0f,  0.0f, 
         0.5f,  -0.5f,   0.5f,  1.0f,  0.0f, 
         0.5f,   0.5f,   0.5f,  1.0f,  1.0f,
         0.5f,   0.5f,   0.5f,  1.0f,  1.0f,
        -0.5f,   0.5f,   0.5f,  0.0f,  1.0f, 
        -0.5f,  -0.5f,   0.5f,  0.0f,  0.0f,

        // FRONT SIDE ^

        -0.5f,   0.5f,   0.5f,  1.0f,  0.0f, 
        -0.5f,   0.5f,  -0.5f,  1.0f,  1.0f, 
        -0.5f,  -0.5f,  -0.5f,  0.0f,  1.0f,
        -0.5f,  -0.5f,  -0.5f,  0.0f,  1.0f,
        -0.5f,  -0.5f,   0.5f,  0.0f,  0.0f,
        -0.5f,   0.5f,   0.5f,  1.0f,  0.0f,

        //LEFT SIDE ^

         0.5f,   0.5f,   0.5f,  1.0f,  0.0f,
         0.5f,   0.5f,  -0.5f,  1.0f,  1.0f, 
         0.5f,  -0.5f,  -0.5f,  0.0f,  1.0f,
         0.5f,  -0.5f,  -0.5f,  0.0f,  1.0f, 
         0.5f,  -0.5f,   0.5f,  0.0f,  0.0f, 
         0.5f,   0.5f,   0.5f,  1.0f,  0.0f,

        //RIGHT SIDE ^

        -0.5f,  -0.5f,  -0.5f,  0.0f,  1.0f, 
         0.5f,  -0.5f,  -0.5f,  1.0f,  1.0f, 
         0.5f,  -0.5f,   0.5f,  1.0f,  0.0f,
         0.5f,  -0.5f,   0.5f,  1.0f,  0.0f, 
        -0.5f,  -0.5f,   0.5f,  0.0f,  0.0f, 
        -0.5f,  -0.5f,  -0.5f,  0.0f,  1.0f,

        //BOTTOM SIDE ^

        -0.5f,   0.5f,  -0.5f,  0.0f,  1.0f, 
         0.5f,   0.5f,  -0.5f,  1.0f,  1.0f, 
         0.5f,   0.5f,   0.5f,  1.0f,  0.0f,
         0.5f,   0.5f,   0.5f,  1.0f,  0.0f, 
        -0.5f,   0.5f,   0.5f,  0.0f,  0.0f, 
        -0.5f,   0.5f,  -0.5f,  0.0f,  1.0f

        //TOP SIDE ^
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glm::vec3 cubePositions[] = {glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
                                 glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
                                 glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
                                 glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
                                 glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};
    // VAO GENERATION
    const VertexArrayObject VAO1;
    VAO1.Bind();

    const VertexBufferObject VBO1(pyramid, sizeof(vertices));
    const IndexBufferObject  IBO1(indices, sizeof(indices));

    // COORDS
    const int numCoords = 3;
    const int numTextCoords = 2;
    const int stride = (numCoords + numTextCoords) * sizeof(float);

    VAO1.LinkAttrib(VBO1, 0, numCoords, GL_FLOAT, stride, (void*)0);

    VAO1.LinkAttrib(VBO1, 1, numTextCoords, GL_FLOAT, stride, (void*)(numCoords * sizeof(float)));

    VBO1.Unbind();
    VAO1.Unbind();
    IBO1.Unbind();

    // TEXTURE GENERATION

    const char* filePath = "res/texture/obamna2.png";

    Texture texture1(filePath);

    // SHADER GENERATION
    const ShaderProgram shader1("res/shaders/basic/vertex.shader", "res/shaders/basic/fragment.shader");
    const ShaderProgram shader2("res/shaders/basic/vertex.shader", "res/shaders/basic/fragmentUniform.shader");

    shader2.Activate();

    texture1.Bind();

    // transformations

    shader2.Set1i("ourTexture", 0);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    shader2.SetMatrix4f("model", 1, false, model);
    shader2.SetMatrix4f("view", 1, false, view);
    shader2.SetMatrix4f("projection", 1, false, projection);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader2.Activate();

        // ORTHO PROJECTION
        // float aspect = (float)SCR_WIDTH/SCR_HEIGHT;
        // projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 0.1f, 100.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        glm::mat4 view;

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        shader2.SetMatrix4f("view", 1, false, view);
        shader2.SetMatrix4f("projection", 1, false, projection);
        VAO1.Bind();

        for (unsigned int i = 0; i < 10; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f) );
            float angle = 20.0f * i;
            if (i % 3 == 0)
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.3f, 0.5f));
            //else
                //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader2.SetMatrix4f("model", 1, false, model);
            GLCall(glDrawArrays(GL_TRIANGLES, 0, ARRAY_LEN(pyramid) / 5));
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        addZ = 0;
        addX = 0;
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 10.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.01f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "Framebuffer resized" << std::endl;
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}
