#pragma once

#include <iostream>
struct GLFWwindow;

class Application
{
public:
    Application(uint32_t width, uint32_t height, GLFWwindow* window);

    uint32_t width_ = 0, height_ = 0;
    GLFWwindow* window_ = nullptr;
};

Application* application_init(int argc, char** argv);
bool application_run(Application* app);
bool application_shutdown(Application* app);
