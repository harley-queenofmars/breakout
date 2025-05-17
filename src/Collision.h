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

extern CFClassRef Collision;

typedef struct __Collision* CollisionRef;

// Represents the four possible (collision) directions
typedef enum {
    UP,
    RIGHT,
    DOWN,
    LEFT
} Direction;

/** Defines a Collision Result Tuple */
typedef struct __Collision {
    __CFObject obj;
    bool IsTrue;
    Direction Dir;
    Vec2 Vec;
} __Collision;

extern proc void* Ctor(
    CollisionRef this, 
    bool first, 
    Direction second, 
    Vec2 third);

extern proc char* ToString(
    CollisionRef this);

static inline CollisionRef NewCollision(bool first, Direction second, Vec2 third)
{
    return Ctor((CollisionRef)CFCreate(Collision), first, second, third);
}
