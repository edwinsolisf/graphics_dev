#include "OpenGLError.h"

#include "OpenGLCore.h"

void openGLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool openGLCheckError()
{
    bool err = false;

    GLenum error = GL_NO_ERROR;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        err = true;
        std::cerr << "[OPENGL ERROR]: ";
        switch (error)
        {
        case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE";
            break;
        case GL_STACK_OVERFLOW:
            std::cerr << "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            std::cerr << "GL_STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "GL_OUT_OF_MEMORY";
            break;
        default:
            std::cerr << "GL_DEFAULT_ERROR";
        }
        std::cerr << std::endl;
    }

    return err;
}
