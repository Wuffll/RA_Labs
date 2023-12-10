#pragma once

#include <GLFW/glfw3.h>

#include "Camera.h"

Camera* mainPlayerCamera = nullptr;
glm::vec3 vector = { 0.0f, 0.0f, 0.0f };

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        vector = { 0.0f, 0.0f, 0.03f };
        mainPlayerCamera->Move(vector);
    }
    else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        vector = { -0.03f, 0.0f, 0.0f };
        mainPlayerCamera->Move(vector);
    }
    else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        vector = { 0.0f, 0.0f, -0.03f };
        mainPlayerCamera->Move(vector);
    }
    else if (key == GLFW_KEY_D &&  (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        vector = { 0.03f, 0.0f, 0.0f };
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
    else if (key == GLFW_KEY_UP &&  (action == GLFW_PRESS || action == GLFW_REPEAT))
    {

    }
    else if (key == GLFW_KEY_DOWN &&  (action == GLFW_PRESS || action == GLFW_REPEAT))
    {

    }
}