/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <stdio.h>
#include "GameLevel.h"
#include "Demo.h"
#include "GameObject.h"

/**
 * BlockType tint color
 */
static const Vec3 COLOR0 = { 0.8f, 0.8f, 0.7f };
static const Vec3 COLOR1 = { 0.2f, 0.6f, 1.0f };
static const Vec3 COLOR2 = { 0.0f, 0.7f, 0.0f };
static const Vec3 COLOR3 = { 0.8f, 0.8f, 0.4f };
static const Vec3 COLOR4 = { 1.0f, 0.5f, 0.0f };
static const Vec3 COLOR5 = { 1.0f, 1.0f, 1.0f };

class(GameLevel);

/**
 * GameLevel
 */
proc GameLevelRef Ctor(
    GameLevelRef this,
    GLchar* file,
    int levelWidth,
    int levelHeight)
{
    this->Bricks = CFCreate(CFArray, nullptr);
    Load(this, file, levelWidth, levelHeight);
    return this;
}

/**
 * Load 
 * 
 * @oaram file  text file with level data
 * @param levelWidth of level in tiles
 * @param levelHeight of level in tiles
 * 
 */
proc GameLevelRef Load(
    GameLevelRef this,
    GLchar* file,
    int levelWidth,
    int levelHeight)
{
    // Clear old data
    Clear(this->Bricks);
    // Load from file
    GLuint tileCode;
    GameLevelRef level;

    FILE* fstream = fopen(file, "r");

    // CFFileRef  handle = CFNew(CFFile, file, "r");
    // if (!handle) {
    //     printf("Unable to open %s\n", file);
    //     return this;
    // }

    // printf("===============================================\n");
    // while (!CFStreamAtEnd(handle)) {
    //     CFRefPoolRef line = CFStreamReadLine(handle);
    //     printf("%s\n", CFStringC(line));
    // }
    // CFStreamClose(handle);
    // printf("===============================================\n");


    CFArrayRef tileData = CFCreate(CFArray, nullptr);
    CFArrayRef row = CFCreate(CFArray, nullptr);
    int i;
    char c;
    if (fstream) {
        while (fscanf(fstream, "%d%c", &i, &c) != EOF) {
            Add(row, CFCreate(CFInt, i));
            if (c == '\n') {
                Add(tileData, row);
                row = CFCreate(CFArray, nullptr);
            }
        }

        if (Length(tileData) > 0) {
            init(this, tileData, levelWidth, levelHeight);
        }
        fclose(fstream);
    }
    return this;
}

/**
 * Draw
 * 
 * @param renderer to use
 * 
 */
proc void Draw(
    GameLevelRef this,
    CFXArrayRendererRef renderer)
{
    for (int i = 0; i < Length(this->Bricks); i++) {
        GameObjectRef tile = CFArrayGet(this->Bricks, i);
        if (!tile->Destroyed)
            Draw(tile, renderer);
    }
}

/**
 * IsCompleted
 * 
 * @returns true when complete
 * 
 */
proc bool IsCompleted(GameLevelRef this)
{
    for (int i = 0; i < Length(this->Bricks); i++) {
        GameObjectRef tile = CFArrayGet(this->Bricks, i);
        if (tile->IsSolid && !tile->Destroyed)
            return false;
    }
    return true;
}

/**
 * init
 * 
 * @param tileData array of tiles
 * @param levelWidth of level in tiles
 * @param levelHeight of level in tiles
 *  
 */
proc void init(
    GameLevelRef this,
    CFArrayRef tileData,
    int levelWidth,
    int levelHeight)
{
    // Calculate dimensions
    int height = Length(tileData);
    CFArrayRef row = CFArrayGet(tileData, 0);
    int width = Length(row); // Note we can index vector at [0] since this static inline is only called if height > 0
    GLfloat unit_width = levelWidth / (GLfloat)width, unit_height = (int)(levelHeight / height);
    // Initialize level tiles based on tileData
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Check block type from level data (2D level array)
            CFArrayRef row = CFArrayGet(tileData, y);
            int blockType = CFIntValue((CFArrayGet(row, x)));

            Vec2 pos = { unit_width * x, unit_height * y };
            Vec2 size = { unit_width, unit_height };
            Vec3 color = {};
            switch (blockType) {
            case 1:
                color = COLOR1;
                break;
            case 2:
                color = COLOR2;
                break;
            case 3:
                color = COLOR3;
                break;
            case 4:
                color = COLOR4;
                break;
            case 5:
                color = COLOR5;
                break;
            default:
                color = COLOR0;
            }

            if (blockType == 1) // Solid
            {
                CFXTexture2DRef tex = GetTexture(ResourceManager, "block_solid");
                GameObjectRef obj = NewGameObject("tile", pos, size, tex, color);
                obj->IsSolid = true;
                Add(this->Bricks, obj);
            } else if (blockType > 1) // Non-solid; now determine its color based on level data
            {
                CFXTexture2DRef tex = GetTexture(ResourceManager, "block");
                GameObjectRef obj = NewGameObject("tile", pos, size, tex, color);
                Add(this->Bricks, obj);
            }
        }
    }
}

/**
 * ToString
 */
proc char* ToString(GameLevelRef this)
{
    return "GameLevel";
}
