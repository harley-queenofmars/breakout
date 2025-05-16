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

extern CFClassRef GameLevel;

typedef struct __GameLevel* GameLevelRef;

/// GameLevel holds all Tiles as part of a Breakout level and
/// hosts functionality to Load/render levels from the harddisk.
typedef struct __GameLevel {
    __CFObject obj;
    CFArrayRef Bricks;
} __GameLevel;

extern method GameLevelRef Ctor(
    GameLevelRef this, 
    GLchar *file, 
    int levelWidth, 
    int levelHeight);

extern method GameLevelRef Load(
    GameLevelRef this, 
    GLchar *file, 
    int levelWidth, 
    int levelHeight);

extern method void Draw(
    GameLevelRef this, 
    CFXArrayRendererRef renderer);

extern method bool IsCompleted(
    GameLevelRef this);

extern method void init(
    GameLevelRef this, 
    CFArrayRef tileData, 
    int levelWidth, 
    int levelHeight);

extern method char* ToString(
    GameLevelRef this);

static inline GameLevelRef NewGameLevel(GLchar *file, int levelWidth, int levelHeight)
{
    return Ctor((GameLevelRef)CFCreate(GameLevel), file, levelWidth, levelHeight);
}
