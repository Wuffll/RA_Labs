#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"

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
    
    // !!! Check if window is being created properly
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        printf("ERROR: Unable to create window!\n");
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

    // glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR: GLEW unable to be initialized!" << std::endl;
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, NULL);

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("", 0);

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
    shader.Bind();

    shader.Unbind();
    vArray.Unbind();
    vBuffer.Unbind();
    iBuffer.Unbind();

    Renderer renderer;

    FpsManager fpsManager(61);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        fpsManager.Begin();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // !!! Check if uniform are being set properly
        shader.Bind();
        shader.SetUniform4f("uColor", 1.0f, 0.0f, 0.3f, 0.0f);

        // !!! Check if the object is being properly drawn
        renderer.Draw(vArray, iBuffer.GetIndicesCount(), shader);
        // glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);

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