#include "Application.h"

#include <iostream>
#include <cmath>

#include "../OpenGL/OpenGLCore.h"
#include "../OpenGL/Renderer.h"

#include "stm/math.h"
#include "stm/matrix.h"
#include "stm/vector.h"
#include "stm/matrix_transform.h"

Application::Application(uint32_t width, uint32_t height, GLFWwindow* window)
    :width_(width), height_(height), window_(window)
{
}

Application* application_init(int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
    {
        std::cout << argv[i] << std::endl;
    }
    system("pwd");

    if (glfwInit() != GLFW_TRUE)
    {
        std::cerr << "Could not initialize GLFW\n";
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    uint32_t width = 800, height = 600;

    GLFWwindow* window = glfwCreateWindow(width, height, "Hello window", nullptr, nullptr);

    if(!window)
    {
        std::cerr << "Could not create window\n";
        return nullptr;
    }

    Application* application = new Application(width, height, window);

    glfwMakeContextCurrent(window);

    return application;
}

bool application_run(Application* app)
{
    if (!app)
        return false;

    GLFWwindow* window = app->window_;

    Shader shader;
    shader.attachSource(std::make_unique<ShaderSource>("../../assets/shaders/vertex.shader"));
    shader.attachSource(std::make_unique<ShaderSource>("../../assets/shaders/fragment.shader"));
    shader.linkProgram();

    VertexArrayLayout layout;
    layout.addElement<GLfloat>(3);

    VertexArray vao = VertexArray(layout);

    float data[] = {
        -0.5f, -0.5f, 1.0f,
        -0.5f,  0.5f, 1.0f,
         0.5f,  0.5f, 1.0f,
         0.5f, -0.5f, 1.0f
    };

    uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    VertexBuffer vbo = VertexBuffer(data, sizeof(data));
    IndexBuffer ibo = IndexBuffer(indices, sizeof(indices) / sizeof(uint32_t));

    float cubeData[] = {
        -0.5f, -0.5f,  0.5f,//0
        -0.5f,  0.5f,  0.5f,//1
         0.5f,  0.5f,  0.5f,//2
         0.5f, -0.5f,  0.5f,//3

        -0.5f, -0.5f, -0.5f,//4
        -0.5f,  0.5f, -0.5f,//5
         0.5f,  0.5f, -0.5f,//6
         0.5f, -0.5f, -0.5f,//7
    };

    uint32_t cubeIndices[] = {
        //Front
        0, 1, 2,
        0, 2, 3,
        //Back
        7, 6, 5,
        7, 5, 4,
        //Right
        3, 2, 6,
        3, 6, 7,
        //Left
        4, 5, 1,
        4, 1, 0,
        //Top
        1, 5, 6,
        1, 6, 2,
        //Bottom
        4, 0, 3,
        4, 3, 7
    };

    VertexBuffer vboCube(cubeData, sizeof(cubeData));
    IndexBuffer iboCube(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t));

    Renderer::bindObject(shader);

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){

    });

    while(glfwWindowShouldClose(window) != GLFW_TRUE)
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        //glfwWaitEvents();

        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        float time = glfwGetTime();

        shader.setUniformVec3f("u_color", {sinf(time * 0.2f), cosf(time), sinf(time * 0.5f) + cosf(time * 0.5f)});

        stm::mat4f mvp = stm::multiply(stm::perspective(stm::radians(45.f), 800.f/600.f, 0.1f, 20.f), stm::lookAt(stm::vec3f{2.0f, 0.0f, 2.0f} * stm::vec3f{2.0f, 0.f, cosf(time)}, stm::posY, stm::negZ));
        shader.setUniformMat4f("u_mvp", mvp);

        //Renderer::drawElements(vbo, ibo, vao, shader);
        Renderer::drawElements(vboCube, iboCube, vao, shader);
    }

    return true;
}

bool application_shutdown(Application* app)
{
    if (!app)
        return false;

    GLFWwindow* window = app->window_;

    glfwSetWindowShouldClose(window, GLFW_TRUE);
    glfwDestroyWindow(window);
    glfwTerminate();

    delete app;

    return true;
}
