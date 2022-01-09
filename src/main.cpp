#include <iostream>

#include "Application/Application.h"

int main(int argc, char** argv)
{
    std::cout << "Hello world!" << std::endl;

    Application* app = application_init(argc, argv);

    application_run(app);

    application_shutdown(app);

    return 0;
}
