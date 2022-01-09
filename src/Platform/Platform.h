#pragma once

#if defined _WIN32
    #define PLATFORM_WINDOWS
    #define ARCHITECTURE_X86
#elif defined _WIN64
    #define PLATFORM_WINDOWS
    #define ARCHITECTURE_X64
#elif defined __APPLE__
    #define PLATFORM_MACOS
    #define ARCHITECTURE_X64
#else
    #error No supported platform found
#endif
