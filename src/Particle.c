/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "Particle.h"

class(Particle);

/**
 * Particle Result Tuple
 * 
 * @param isTrue collided?
 * @param dir direction from
 * @param Vec2 difference point
 */
proc void* Ctor(ParticleRef this, Vec2 position, Vec2 velocity, Vec4 color, GLfloat life)
{
    this->Color = color;
    this->Life = life;
    this->Position = position;
    this->Velocity = velocity;
    return this;
}
