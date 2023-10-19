#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

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
#include "Objekt.h"
#include "Spline.h"

#include "Transform.h"

#include "FpsManager.h"
#include "OpenGLDebugMessageCallback.h"
#include "Debug.h"

// change directory to yours
#define SHADER_PATH "D:\\Programming\\repos\\RA_Labs\\Lab1\\Shaders"
#define MODELS_PATH "D:\\Programming\\repos\\RA_Labs\\Lab1\\Models\\"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

GLFWwindow* InitWindow();

int main(void)
{
    GLFWwindow* window = InitWindow();

    Shader shader(std::string(SHADER_PATH).append("\\general.glsl"));

    std::vector<glm::vec3> controlPoints{ {-5.0f, -5.0f, 1.0f}, {5.0f, -5.0f, 0.0f}, {5.0f, 5.0f, -1.0f}, {-5.0f, 5.0f, 0.0f} };
    CubicBSpline spline(controlPoints, 500);

    VertexBuffer splineBuffer(spline.GetSplinePoints().data(), spline.GetSplinePoints().size() * sizeof(Vertex), GL_STATIC_DRAW);

    Mesh mesh(std::string(MODELS_PATH).append("airplane_f16.obj"));

    Objekt obj("FirstObject", std::string(MODELS_PATH).append("airplane_f16.obj"), shader);
    
    /*
    VertexArray vArray2;
    vArray2.Bind();
    splineBuffer.Bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
    */
    
    Renderer renderer(shader);

    renderer.AddDrawableObject(obj);
    renderer.AddDrawableObject(spline);

    Transform view;
    view.Translation(glm::vec3(0.0f, 0.0f, -13.0f));

    // view.Rotate({ 0.0f, 50.0f, 0.0f });

    Transform projection(glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f));

    shader.Bind();
    shader.SetUniformMatrix4f("projection", projection.GetMatrix());
    shader.SetUniformMatrix4f("view", view.GetMatrix());

    FpsManager fpsManager(60);
    TimeControl timer;
    timer.Start();
    float deltaTime = 0.0f;

    int i = 0;

    auto& rotations = spline.GetRotationMatrices();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        fpsManager.Begin();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // !!! Check if uniform are being set properly
        deltaTime += timer.End();
        // view.Rotate((float)timer.End() * glm::vec3(0.0f, 90.0f, 0.0f));
        shader.SetUniformMatrix4f("view", view.GetMatrix());

        if (deltaTime - 4.0f >= 0.000002f)
        {
            deltaTime = 0.0f;
        }

        i += 1;

        if (i >= spline.GetSplinePoints().size())
            i = 0;

        obj.GetTransform().SetPosition(spline.GetSplinePoints()[i].pos);
        obj.GetTransform().SetOrientation(rotations[i]);
        // obj.GetTransform().Rotate({ 0.0f, 180.0f, 0.0f });

        auto& transform = obj.GetTransform();
        std::cout << "Position = " << Debug::GlmString(transform.GetPosition()).c_str() << "; Rotation = " << Debug::GlmString(transform.GetOrientation()) << std::endl;

        renderer.Draw();

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