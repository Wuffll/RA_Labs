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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

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
    Transform entityModel;
    entityModel.Translation({ 4.0f, 0.0f, -5.0f });

    shader.Bind();
    shader.SetUniformMatrix4f("projection", projection.GetMatrix());
    shader.SetUniformMatrix4f("model", entityModel.GetMatrix());

    FpsManager fpsManager(120);
    TimeControl timer;
    timer.Start();
    float deltaTime = 0.0f;

    // Loading image and setting texture
    
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    std::string texturePath(TEXTURES_PATH);
    texturePath.append("Fire\\fire0.png");

    stbi_set_flip_vertically_on_load(1);

    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        Debug::ThrowException("Unable to load image data!");
    }

    stbi_image_free(data);

    float vertices[] = {
        // positions          // colors           // texture coords // normals
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,       0.0f, 0.0f, 1.0f,   // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,       0.0f, 0.0f, 1.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,       0.0f, 0.0f, 1.0f,   // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,       0.0f, 0.0f, 1.0f    // top left 
    };
    glm::vec3 entityNormal = { 0.0f, 0.0f, 1.0f };
    
    glm::vec3 fromEntityToCamera = glm::normalize(camera.GetView().GetPosition() - entityModel.GetPosition());
    glm::vec3 axis = glm::normalize(glm::cross(fromEntityToCamera, entityNormal));
    float angle = acos(glm::dot(fromEntityToCamera, entityNormal));

    glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray mVAO;
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
    mVAO.SetLayout(layout, false);
    mVAO.SetDrawingMode(GL_TRIANGLES);
    mVAO.SetUsage(GL_STATIC_DRAW);

    VertexBuffer mVBO;
    mVBO.FillBuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);

    IndexBuffer mIBO;
    mIBO.FillBuffer(indices, sizeof(indices) / sizeof(unsigned int), GL_STATIC_DRAW);

    mVAO.AddBuffer(mVBO, mIBO);

    float timeBetweenPoints = 0.016f; // in seconds

    float sign = 1.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        fpsManager.Begin();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // obj.SetActive(toggleModel);

        shader.SetUniformMatrix4f("projection", projection.GetMatrix());
        shader.SetUniformMatrix4f("model", entityModel.GetMatrix() * rotMatrix);

        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        shader.Bind();
        mVAO.Bind();
        glDrawElements(GL_TRIANGLES, mIBO.GetIndicesCount(), GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_TRIANGLES, mIBO.GetIndicesCount(), GL_UNSIGNED_INT, 0);

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

        if (deltaTime < 10.0f)
        {
            entityModel.Translation({ 0.0f, 0.0f, sign * (float)timer.End() * 1.0f });
        }
        else
        {
            sign *= -1.0f;
            deltaTime = 0.0f;
        }


        // camera.Rotate((float)timer.End() * glm::vec3{ 0.0f, 15.0f, 0.0f });

        fromEntityToCamera = glm::normalize(camera.GetView().GetPosition() - entityModel.GetPosition());
        axis = glm::normalize(glm::cross(fromEntityToCamera, entityNormal));
        angle = acos(glm::dot(fromEntityToCamera, entityNormal));

        rotMatrix = glm::rotate(glm::mat4(1.0f), -angle, axis);

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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return window;
}