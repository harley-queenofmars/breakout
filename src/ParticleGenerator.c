/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "ParticleGenerator.h"
#include "GameObject.h"

class(ParticleGenerator);

/**
 * ParticleGenerator
 * 
 * @param shader to use
 * @param texture to source from
 * @param amount number of particles to generate
 * 
 */
proc void* Ctor(
    ParticleGeneratorRef this,
    CFXShaderRef shader,
    CFXTexture2DRef texture,
    int amount)
{
    this->shader = shader;
    this->texture = texture;
    this->amount = amount;
    init(this);
    return this;
}
/**
 * Update
 * 
 * @param dt delta time
 * @param object GameObject
 * @param newParticles count
 * @param offset to display from
 * 
 */
proc void Update(
    ParticleGeneratorRef this,
    GLfloat dt,
    GameObjectRef object,
    GLuint newParticles,
    Vec2 offset)
{
    // Add new particles
    for (GLuint i = 0; i < newParticles; ++i) {
        int unusedParticle = firstUnused(this);
        respawn(this, &this->particles[unusedParticle], object, offset);
    }
    // Update all particles
    for (GLuint i = 0; i < this->amount; ++i) {
        this->particles[i].Life -= dt; // reduce life
        if (this->particles[i].Life > 0.0f) { // particle is alive, thus update

            this->particles[i].Position -= this->particles[i].Velocity * dt;
            this->particles[i].Color[3] -= dt * 2.5;
        }
    }
}

/**
 * Render all particles
 * 
 */
proc void Draw(ParticleGeneratorRef this)
{
    // Use additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    Use(this->shader);
    for (int i = 0; i < this->amount; i++) {
        ParticleRef particle = &this->particles[i];
        if (particle->Life > 0.0f) {
            SetVector2v(this->shader, "offset", &particle->Position);
            SetVector4v(this->shader, "color", &particle->Color);
            Bind(this->texture);
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    // Don't forget to reset to default blending mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/**
 * initialize generator
 */
proc void init(ParticleGeneratorRef this)
{
    // Set up mesh and attribute properties
    GLuint VBO;
    GLfloat particle_quad[24] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);
    // Fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // Set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    this->particles = (ParticleRef)malloc(sizeof(struct __Particle) * this->amount);
}

// Stores the index of the last particle used (for quick access to next dead particle)
static GLuint lastUsedParticle = 0;
proc GLuint firstUnused(ParticleGeneratorRef this)
{
    // First search from last used particle, this will usually return almost instantly
    for (GLuint i = lastUsedParticle; i < this->amount; ++i) {
        if (this->particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    // Otherwise, do a linear search
    for (GLuint i = 0; i < lastUsedParticle; ++i) {
        if (this->particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    // All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle = 0;
    return 0;
}

proc void respawn(
    ParticleGeneratorRef this,
    ParticleRef particle,
    GameObjectRef object,
    Vec2 offset)
{
    GLfloat random = ((rand() % 100) - 50) / 10.0f;
    GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
    particle->Position = object->Position + random + offset;
    particle->Color = (Vec4) { rColor, rColor, rColor, 1.0f };
    particle->Life = 1.0f;
    particle->Velocity = object->Velocity * 0.1f;
}

/**
 * ToString
 */
proc char* ToString(ParticleGeneratorRef this)
{
    return "ParticleGenerator";
}
