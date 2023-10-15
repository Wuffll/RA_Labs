#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Mesh.h"

#include "FpsManager.h"
#include "OpenGLDebugMessageCallback.h"

// change directory to yours
#define SHADER_PATH "D:\\Programming\\repos\\RA_Labs\\Lab1\\Shaders"
#define MODELS_PATH "D:\\Programming\\repos\\RA_Labs\\Lab1\\Models\\"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GLFWwindow* InitWindow();

int main(void)
{
    GLFWwindow* window = InitWindow();

    Mesh mesh(std::string(MODELS_PATH).append("airplane_f16.obj"));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);

    VertexArray vArray;
    vArray.AddBuffer(mesh.GetVB(), mesh.GetIB(), layout);

    Shader shader(std::string(SHADER_PATH).append("\\general.glsl"));
    shader.Bind();

    shader.Unbind();
    vArray.Unbind();

    Renderer renderer;

    FpsManager fpsManager(60);

    shader.Bind();
    shader.SetUniformMatrix4f("model", mesh.GetTransform());

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0, 0.0, -2.5));

    view = glm::rotate(view, glm::radians(20.0f), glm::vec3(1.0, 0.0, 0.0));

    glm::mat4 projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

    shader.SetUniformMatrix4f("projection", projection);

    TimeControl timer;
    timer.Start();
    float deltaTime = 0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        fpsManager.Begin();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // !!! Check if uniform are being set properly
        deltaTime += timer.End();
        shader.SetUniformMatrix4f("view", glm::rotate(view, glm::radians(90.0f) * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f)));

        if (deltaTime - 4.0f >= 0.000002f)
            deltaTime = 0.0f;

        // !!! Check if the object is being properly drawn
        renderer.Draw(vArray, mesh.GetIB().GetIndicesCount(), shader);
        // glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        timer.Start();

        do 
        {
            /* Poll for and process events */
            glfwPollEvents();
        } while (!fpsManager.TimeToGo()); // should eventually replace while loop with sleep

        std::cout << "FPS: " << fpsManager.GetCurrentFps() << std::endl;
    }

    glfwTerminate();
    return 0;
}

GLFWwindow* InitWindow()
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        exit(-1);

    /* Window creation hints */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        printf("ERROR: Unable to create window!\n");
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

    // glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR: GLEW unable to be initialized!" << std::endl;
        exit(-1);
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, NULL);

    glEnable(GL_DEPTH_TEST);

    return window;
}