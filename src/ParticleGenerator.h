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
#include "GameObject.h"
#include "Particle.h"

/**
 * @brief An external reference to a Core Foundation class object for particle generation.
 *
 * This variable provides access to the ParticleGenerator class reference,
 * which can be used for creating and managing particle generator instances.
 * 
 * @note The actual definition and initialization of this reference should be provided elsewhere.
 */
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

extern proc void* Ctor(
    ParticleGeneratorRef this, 
    CFXShaderRef shader, 
    CFXTexture2DRef texture, 
    int amount);

extern proc void Update(
    ParticleGeneratorRef this, 
    GLfloat dt, 
    GameObjectRef object, 
    GLuint newParticles, 
    Vec2 offset);

extern proc void Draw(
    ParticleGeneratorRef this);

extern proc void init(
    ParticleGeneratorRef this);

extern proc GLuint firstUnused(
    ParticleGeneratorRef this);

extern proc void respawn(
    ParticleGeneratorRef this, 
    ParticleRef particle, 
    GameObjectRef object, 
    Vec2 offset);

extern proc char* ToString(
    ParticleGeneratorRef this);

static inline ParticleGeneratorRef NewParticleGenerator(CFXShaderRef shader, CFXTexture2DRef texture, int amount)
{
    return Ctor((ParticleGeneratorRef)CFCreate(ParticleGenerator), shader, texture, amount);
}
