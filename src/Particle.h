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

/**
 * @brief External reference to the Particle class type.
 *
 * This variable provides access to the Core Foundation class reference for Particle.
 * It is typically used for runtime type identification and class-related operations.
 */
extern CFClassRef Particle;

typedef struct __Particle* ParticleRef;

// Represents a single particle and its state
/**
 * @struct __Particle
 * @brief Represents a single particle in a 2D particle system.
 *
 * This structure encapsulates all the properties required to simulate a particle,
 * including its position, velocity, color, and remaining life. It is designed to be
 * used in particle systems for effects such as explosions, smoke, or fire.
 *
 * @var __CFObject obj
 *      Base object for compatibility or inheritance with other framework objects.
 * @var Vec2 Position
 *      The position of the particle in 2D space (X and Y coordinates).
 * @var Vec2 Velocity
 *      The velocity vector of the particle, representing its speed and direction.
 * @var Vec4 Color
 *      The color of the particle, typically represented as RGBA components.
 * @var GLfloat Life
 *      The remaining life of the particle in seconds. When this value reaches zero,
 *      the particle is considered dead and can be respawned or removed.
 */
typedef struct __Particle {
    __CFObject obj;
    Vec2 Position;
    Vec2 Velocity;
    Vec4 Color;
    GLfloat Life;
} __Particle;

/**
 * @brief Constructs and initializes a Particle object.
 *
 * @param this Pointer to the Particle instance to initialize.
 * @param shader Reference to the shader to be used by the particle.
 * @param texture Reference to the 2D texture to be applied to the particle.
 * @param amount The number of particles to initialize.
 * @return A pointer to the constructed Particle object.
 */
extern proc void* Ctor(
    ParticleRef this, 
    CFXShaderRef shader, 
    CFXTexture2DRef texture, 
    int amount);

/**
 * @brief Converts the given ParticleRef object to its string representation.
 *
 * @param this Reference to the Particle object to be converted.
 * @return A pointer to a character array containing the string representation of the Particle.
 */
extern proc char* ToString(
    ParticleRef this);
