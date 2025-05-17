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

extern CFClassRef GameObject;

typedef struct __GameObject* GameObjectRef;

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
typedef struct __GameObject {
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
} __GameObject;

extern proc GameObjectRef Ctor(
    GameObjectRef this, 
    char* name, 
    Vec2 Position, 
    Vec2 Size, 
    CFXTexture2DRef Sprite, 
    Vec3 Color);

extern proc void Draw(
    GameObjectRef this, 
    CFXArrayRendererRef renderer);

extern proc char* ToString(
    GameObjectRef this);

static inline GameObjectRef NewGameObject(char* name, Vec2 Position, Vec2 Size, CFXTexture2DRef Sprite, Vec3 Color)
{
    return Ctor((GameObjectRef)CFCreate(GameObject), name, Position, Size, Sprite, Color);
}

