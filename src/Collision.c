/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "Collision.h"
// #include "Demo.h"

class(Collision);

/**
 * Collision Result Tuple
 * 
 * @param isTrue collided?
 * @param dir direction from
 * @param Vec2 difference point
 */
proc void* Ctor(CollisionRef this, bool isTrue, Direction dir, Vec2 vec)
{
    this->IsTrue = isTrue;
    this->Dir = dir;
    this->Vec = vec;
    return this;
}
