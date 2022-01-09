#pragma once

#include <assert.h>
#include <iostream>

#define GLCALL(x) openGLClearError();\
                  x;\
                  assert(!openGLCheckError())

void openGLClearError();

bool openGLCheckError();
