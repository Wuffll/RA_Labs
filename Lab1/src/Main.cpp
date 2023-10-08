#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "FpsManager.h"
#include "OpenGLDebugMessageCallback.h"

// change directory to yours
#define SHADER_PATH "D:\\Programming\\repos\\RA_Labs\\Lab1\\Shaders"

int main(void)
{
    GLFWwindow* window;;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW unable to be initialized!" << std::endl;
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, NULL);

    float points[] = {
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 1.0f, 0.3f, 0.1f, 0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexBuffer vBuffer((void*)&points[0], sizeof(points), GL_STATIC_DRAW);
    IndexBuffer iBuffer((void*)&indices[0], sizeof(indices) / sizeof(unsigned int), GL_STATIC_DRAW);

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);

    VertexArray vArray;
    vArray.AddBuffer(vBuffer, iBuffer, layout);

    Shader shader(std::string(SHADER_PATH).append("\\general.glsl"));
    glUseProgram(shader.GetShaderId());

    FpsManager fpsManager(61);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        fpsManager.Begin();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        vArray.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        while (!fpsManager.TimeToGo()) // should eventually replace with sleep
        {
            // Update state until fps limiter allows to draw next frame

            /* Poll for and process events */
            glfwPollEvents();
        }

        // std::cout << "FPS: " << fpsManager.GetCurrentFps() << std::endl;

    }

    glfwTerminate();
    return 0;
}