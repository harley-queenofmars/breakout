/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "BallObject.h"
#include "GameObject.h"

class(BallObject);

/**
 * BallObject
 * 
 * @param Position initial placement of ball 
 * @param Radius size of ball
 * @param Velocity initial speed of ball
 * @param Sprite to display
 */
proc void* Ctor(
    BallObjectRef this,
    Vec2 Position,
    float Radius,
    Vec2 Velocity,
    CFXTexture2DRef Sprite)
{
    Radius = Radius != 0 ? Radius : 12.5f;

    Ctor((GameObjectRef)this, "ball", Position, (Vec2) { Radius * 2, Radius * 2 }, Sprite, (Vec3) { 1, 1, 1 });

    this->Velocity = Velocity;
    this->Radius = Radius;
    return this;
}

/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
proc void Draw(BallObjectRef this, CFXArrayRendererRef renderer)
{
    CFXRect bounds = { this->Position.x, this->Position.y,
        this->Size.x, this->Size.y };

    Draw(renderer, this->Sprite, &bounds, this->Rotation, this->Color);
}

/**
 * Move
 * 
 * @param dt delta time
 * @param window_width
 * @returns Vec2 new position
 */
proc void Move(BallObjectRef this, GLfloat dt, GLuint window_width)
{
    // If not stuck to player board
    if (!this->Stuck) {
        // Move the ball
        this->Position += this->Velocity * dt;
        // Then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->Position.x <= 0.0f) {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        } else if (this->Position.x + this->Size.x >= window_width) {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
        if (this->Position.y <= 0.0f) {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
    }
}

/**
 * Resets the ball to initial Stuck Position (if ball is outside window bounds)
 * 
 * @param position to reset to
 * @param velocity to reset to
 * 
 */
proc void Reset(BallObjectRef this, Vec2 position, Vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}

/**
 * ToString
 */
proc char* ToString(BallObjectRef this)
{
    return "BallObject";
}

