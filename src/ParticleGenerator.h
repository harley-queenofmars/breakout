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
#include "../libs/corefw/corefw.h"      // IWYU pragma: keep
#include "../libs/corefx/corefx.h"      // IWYU pragma: keep
#include "GameObject.h"
#include "Particle.h"

extern CFClassRef ParticleGenerator;

typedef struct __ParticleGenerator* ParticleGeneratorRef;
// ParticleGenerator acts as a container for rendering a large number of
// particles by repeatedly spawning and updating particles and killing
// them after a given amount of time.
typedef struct __ParticleGenerator {
    __CFObject obj;
    ParticleRef particles;
    GLuint amount;
    CFXShaderRef shader;
    CFXTexture2DRef texture;
    GLuint VAO;
} __ParticleGenerator;

extern method void* Ctor(
    ParticleGeneratorRef this, 
    CFXShaderRef shader, 
    CFXTexture2DRef texture, 
    int amount);

extern method void Update(
    ParticleGeneratorRef this, 
    GLfloat dt, 
    GameObjectRef object, 
    GLuint newParticles, 
    Vec2 offset);

extern method void Draw(
    ParticleGeneratorRef this);

extern method void init(
    ParticleGeneratorRef this);

extern method GLuint firstUnused(
    ParticleGeneratorRef this);

extern method void respawn(
    ParticleGeneratorRef this, 
    ParticleRef particle, 
    GameObjectRef object, 
    Vec2 offset);

extern method char* ToString(
    ParticleGeneratorRef this);

static inline ParticleGeneratorRef NewParticleGenerator(CFXShaderRef shader, CFXTexture2DRef texture, int amount)
{
    return Ctor((ParticleGeneratorRef)CFCreate(ParticleGenerator), shader, texture, amount);
}
