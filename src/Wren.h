#pragma once
#include <stdio.h>                      // IWYU pragma: keep
#include <unistd.h>
#include <assert.h>
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <corefx.h>      // IWYU pragma: keep
#include <corefw.h>      // IWYU pragma: keep
#include "wren.h"						// IWYU pragma: keep

extern CFClassRef Wren;

typedef struct __Wren* WrenRef;


typedef struct __Wren {
    __CFObject  obj;
    WrenVM*     vm;
    WrenHandle* name;
    WrenHandle* version;
    WrenHandle* playerVelocity;
    WrenHandle* ballVelocityX;
    WrenHandle* ballVelocityY;
    } __Wren;


extern proc void* Ctor(
    WrenRef this);

extern proc const char* GetName(WrenRef this);
extern proc double GetVersion(WrenRef this);
extern proc double GetPlayerVelocity(WrenRef this);
extern proc Vec2 GetBallVelocity(WrenRef this);

static inline WrenRef NewWren()
{
    return Ctor((WrenRef)CFCreate(Wren));
}

