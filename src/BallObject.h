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

extern CFClassRef BallObject;

typedef struct __BallObject* BallObjectRef;

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
typedef struct __BallObject { // extend GameObject
    __CFObject obj;
    Vec2 Position;
    Vec2 Size;
    Vec2 Velocity;
    Vec3 Color;
    GLfloat Rotation;
    GLboolean IsSolid;
    GLboolean Destroyed;
    CFXTexture2DRef Sprite;
    char* Name;

    /* new BallObject fields */
    float Radius;
    bool Stuck;
} __BallObject;

extern proc void* Ctor(
    BallObjectRef this, 
    Vec2 Position, 
    float Radius, 
    Vec2 Velocity, 
    CFXTexture2DRef Sprite);

extern proc void Draw(
    BallObjectRef this, 
    CFXArrayRendererRef renderer);

extern proc void Move(
    BallObjectRef this, 
    GLfloat dt, 
    GLuint window_width);

extern proc void Reset(
    BallObjectRef this, 
    Vec2 position, 
    Vec2 velocity);

extern proc char* ToString(
    BallObjectRef  this);

static inline BallObjectRef NewBallObject(Vec2 Position, float Radius, Vec2 Velocity, CFXTexture2DRef Sprite)
{
    return Ctor((BallObjectRef)CFCreate(BallObject), Position, Radius, Velocity, Sprite);
}
