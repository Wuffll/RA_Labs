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
#include "GLFWKeyPressedCallbacks.h"
#include "Parser.h"
#include "Debug.h"

// change directory to yours
#define SHADER_PATH "D:\\Programming\\repos\\RA_Labs\\Lab1\\Shaders\\"
#define MODELS_PATH "D:\\Programming\\repos\\RA_Labs\\Lab1\\Models\\"
#define SPLINE_PATH "D:\\Programming\\repos\\RA_Labs\\Debug\\"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GLFWwindow* InitWindow();

int main(void)
{
    GLFWwindow* window = InitWindow();

    Shader shader(std::string(SHADER_PATH).append("general.glsl"));

    std::vector<glm::vec3> controlPoints{};
    Parser::ReadFile(std::string(SPLINE_PATH).append("spiral.txt"), controlPoints);

    CubicBSpline spline(controlPoints, 2000);

    VertexBuffer splineBuffer(spline.GetSplinePoints().data(), spline.GetSplinePoints().size() * sizeof(Vertex), GL_STATIC_DRAW);

    Objekt obj("FirstObject", std::string(MODELS_PATH).append("airplane_f16_1.obj"), shader);
    // Objekt obj("FirstObject", std::string(MODELS_PATH).append("galleon1.obj"), shader);
    // Objekt obj("FirstObject", std::string(MODELS_PATH).append("tetrahedron_1.obj"), shader);
    
    Renderer renderer(shader);

    renderer.AddDrawableObject(obj);
    renderer.AddDrawableObject(spline);

    Transform view;

    // view.Rotate({ 0.0f, 50.0f, 0.0f });

    Transform projection(glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f));

    shader.Bind();
    shader.SetUniformMatrix4f("projection", projection.GetMatrix());
    shader.SetUniformMatrix4f("view", view.GetMatrix());

    FpsManager fpsManager(120);
    TimeControl timer;
    timer.Start();
    float deltaTime = 0.0f;

    int i = 0;

    auto& points = spline.GetSplinePoints();
    auto& tangents = spline.GetTangents();
    auto& rotations = spline.GetRotationMatrices();

    float angle;
    glm::vec3 axis;
    glm::vec3 zVec = { 0.0f, 0.0f, 1.0f };
    float mult;

    float timeBetweenPoints = 0.016f; // in seconds

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        fpsManager.Begin();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        obj.SetActive(toggleModel);

        // Time passed
        deltaTime += timer.End();

        // Camera
        view.SetPosition(glm::vec3(0.0f, 0.0f, -5.0f) - points[i].pos);
        shader.SetUniformMatrix4f("view", view.GetMatrix());

        i++;

        if (i >= spline.GetRotationMatrices().size())
            i = 0;

        obj.GetTransform().SetPosition(spline.GetSplinePoints()[i].pos);

        if (toggleRotation)
        {
            axis = glm::cross(zVec, tangents[i].pos);

            mult = zVec.x * tangents[i].pos.x + zVec.y * tangents[i].pos.y + zVec.z * tangents[i].pos.z; // component-wise vector multiplication
            angle = acos(mult / (glm::length(zVec) * glm::length(glm::normalize(tangents[i].pos))));

            obj.GetTransform().SetOrientation(axis, angle);
        }
        else
        {
            obj.GetTransform().SetOrientation(rotations[i]);
        }

        // obj.GetTransform().Rotate({ 0.0f, 0.0f, 180.0f }); // upside down model when going towards screen
 
        // Debugging
        {
            auto& transform = obj.GetTransform();
            std::cout << "Position = " << Debug::GlmString(transform.GetPosition()).c_str() << "; Rotation = " << Debug::GlmString(transform.GetOrientation()) << std::endl;
        }

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

    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_DEPTH_TEST);

    return window;
}