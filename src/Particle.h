/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <corefw.h>      // IWYU pragma: keep
#include <corefx.h>      // IWYU pragma: keep

extern CFClassRef Particle;

typedef struct __Particle* ParticleRef;

// Represents a single particle and its state
typedef struct __Particle {
    __CFObject obj;
    Vec2 Position;
    Vec2 Velocity;
    Vec4 Color;
    GLfloat Life;
} __Particle;

extern proc void* Ctor(
    ParticleRef this, 
    CFXShaderRef shader, 
    CFXTexture2DRef texture, 
    int amount);

extern proc char* ToString(
    ParticleRef this);
