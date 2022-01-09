#pragma once

#include "../Platform/Platform.h"

#if defined PLATFORM_WINDOWS
    #include "GL/glad.h"
    #include "GLFW/glfw3.h"
#elif defined PLATFORM_MACOS
    #include "GLFW/glfw3.h"
    #include <OpenGL/gl.h>
    #include <OpenGL/gl3.h>
#else
    #error OPENGL not supported for the given platform
#endif

#include "OpenGLError.h"
