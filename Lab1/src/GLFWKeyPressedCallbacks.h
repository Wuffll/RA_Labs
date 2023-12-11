#pragma once

#include <GLFW/glfw3.h>

#include "Camera.h"

static Camera* mainPlayerCamera = nullptr;
static glm::vec3 vector = { 0.0f, 0.0f, 0.0f };
static ParticleContainer* containerPtr = nullptr;
static ParticleContainer* containerPtr2 = nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        vector = { 0.0f, 0.0f, 0.03f };
        mainPlayerCamera->Move(vector);
    }
    else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        vector = { 0.03f, 0.0f, 0.0f };
        mainPlayerCamera->Move(vector);
    }
    else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        vector = { 0.0f, 0.0f, -0.03f };
        mainPlayerCamera->Move(vector);
    }
    else if (key == GLFW_KEY_D &&  (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        vector = { -0.03f, 0.0f, 0.0f };
        mainPlayerCamera->Move(vector);
    }
    else if (key == GLFW_KEY_LEFT &&  (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        vector = { 0.0f, -1.0f, 0.0f };
        mainPlayerCamera->Rotate(vector);
    }
    else if (key == GLFW_KEY_RIGHT &&  (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        vector = { 0.0f, 1.0f, 0.0f };
        mainPlayerCamera->Rotate(vector);

    }
    else if (key == GLFW_KEY_1 &&  (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        containerPtr->AddParticle();
    }
    else if (key == GLFW_KEY_2 &&  (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        containerPtr2->AddParticle();
    }
}