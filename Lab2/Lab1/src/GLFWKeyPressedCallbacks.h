#pragma once

#include <GLFW/glfw3.h>

#include "Camera.h"

static Camera* mainPlayerCamera = nullptr;
static glm::vec3 vector = { 0.0f, 0.0f, 0.0f };

static ParticleContainer* containerPtr = nullptr;
static glm::vec3 sourceVector = { 0.0f, 0.0f, -2.5f };

static ParticleContainer* containerPtr2 = nullptr;
static glm::vec3 sourceVector2 = { 3.5f, 0.0f, -1.0f };

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
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        mainPlayerCamera->ResetTransform();
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
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        sourceVector += glm::vec3(-0.25f, 0.0f, 0.0f);
        containerPtr->UpdateSourcePosition(sourceVector);
    }
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
    {
        sourceVector += glm::vec3(0.25f, 0.0f, 0.0f);
        containerPtr->UpdateSourcePosition(sourceVector);
    }
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS)
    {
        sourceVector2 += glm::vec3(0.0f, 0.0f, -0.25f);
        containerPtr2->UpdateSourcePosition(sourceVector2);
    }
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        sourceVector2 += glm::vec3(0.0f, 0.0f, 0.25f);
        containerPtr2->UpdateSourcePosition(sourceVector2);
    }
}