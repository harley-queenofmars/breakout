#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <corefw.h>      // IWYU pragma: keep
#include "BallObject.h"                 // IWYU pragma: keep
#include "Collision.h"                  // IWYU pragma: keep
#include "Demo.h"                       // IWYU pragma: keep
#include "GameLevel.h"                  // IWYU pragma: keep
#include "GameObject.h"                 // IWYU pragma: keep
#include "Particle.h"                   // IWYU pragma: keep
#include "ParticleGenerator.h"          // IWYU pragma: keep
