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
#include "Transform.h"

#include "Spline.h"
#include "Camera.h"
#include "Texture.h"
#include "Panel.h"
#include "ParticleContainer.h"

#include "FpsManager.h"
#include "OpenGLDebugMessageCallback.h"
#include "GLFWKeyPressedCallbacks.h"
#include "Parser.h"
#include "Debug.h"

// change directory to yours
#define SHADER_PATH "D:\\Programming\\repos\\RA_Labs\\Shaders\\"
#define MODELS_PATH "D:\\Programming\\repos\\RA_Labs\\Models\\"
#define SPLINE_PATH "D:\\Programming\\repos\\RA_Labs\\Debug\\"
#define TEXTURES_PATH "D:\\Programming\\repos\\RA_Labs\\Textures\\"
#define FIRE_TEXTURES "D:\\Programming\\repos\\RA_Labs\\Textures\\Fire\\"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GLFWwindow* InitWindow();

int main(void)
{
    GLFWwindow* window = InitWindow();

    Shader shader(std::string(SHADER_PATH).append("general.glsl"));

    // Objekt obj("FirstObject", std::string(MODELS_PATH).append("airplane_f16_1.obj"), shader);
    
    Renderer renderer(shader);

    // renderer.AddDrawableObject(obj);

    Camera camera;
    camera.SetShader("view", &shader);

    mainPlayerCamera = &camera;
    

    Transform projection(glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f));

    shader.Bind();
    shader.SetUniformMatrix4f("projection", projection.GetMatrix());

    FpsManager fpsManager(120);
    TimeControl timer;
    timer.Start();
    float deltaTime = 0.0f;

    // Loading image and setting texture
    
    std::vector<Texture> fireTextures;
    std::string textureName = "fire0.png";
    for (int i = 0; i < 5; i++)
    {
        textureName[4] = STRING(i).c_str()[0];
        fireTextures.push_back(Texture(std::string(FIRE_TEXTURES).append(textureName)));
    }

    ParticleContainer container(shader, fireTextures, camera, 5, {0.0f, 0.0f, -2.0f});
    ParticleContainer container2(shader, fireTextures, camera, 6, { 3.5f, 0.0f, -1.0f });

    containerPtr = &container;
    containerPtr2 = &container2;

    float timeBetweenPoints = 0.016f; // in seconds

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        fpsManager.Begin();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // obj.SetActive(toggleModel);

        shader.SetUniformMatrix4f("projection", projection.GetMatrix());

        container.Draw();
        container2.Draw();

        // Time passed
        deltaTime += (float)timer.End();

        // Camera

        // obj.GetTransform().Rotate({ 0.0f, 0.0f, 180.0f }); // upside down model when going towards screen
 
        // Debugging
        {
            //auto& transform = obj.GetTransform();
            //std::cout << "Position = " << Debug::GlmString(transform.GetPosition()).c_str() << "; Rotation = " << Debug::GlmString(transform.GetOrientation()) << std::endl;
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

        container.Update(timer.End());
        container2.Update(timer.End());

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.15f, 0.0f, 0.3f, 1.0f);

    return window;
}