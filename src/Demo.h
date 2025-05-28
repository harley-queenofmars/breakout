#pragma once
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <corefx.h>      // IWYU pragma: keep
#include <corefw.h>      // IWYU pragma: keep
#include "Wren.h"

extern CFClassRef Demo;

typedef struct __Demo* DemoRef;
struct DemoVtbl;
typedef enum {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
} GameState;


typedef struct __Demo {
    /**
     * @brief Represents a Core Foundation object.
     *
     * This type is typically used as a generic handle or reference to a Core Foundation object,
     * allowing for manipulation and management of various CF types in a platform-agnostic way.
     * The actual definition and usage may depend on the platform and the specific Core Foundation
     * APIs being interfaced with.
     */
    __CFObject obj;
    void* subclass;
    CFXGameVtblRef  virtual;
    GLFWwindow* window;
    char* title;
    int len;
    bool* keys;
    double delta;
    double factor;
    uint64_t targetElapsedTime;
    uint64_t accumulatedElapsedTime;
    uint64_t maxElapsedTime;
    uint64_t totalGameTime;
    uint64_t elapsedGameTime;
    uint64_t currentTime;
    long previousTicks;
    int x;
    int y;
    int width;
    int height;
    uint32_t flags;
    int mouseX;
    int mouseY;
    bool mouseDown;
    int sdlVersion;
    int frameSkip;
    int gl_major_version;
    int gl_minor_version;
    bool isRunning;
    int ticks;
    int fps;
    bool isFixedTimeStep;
    bool isRunningSlowly;
    int updateFrameLag;
    bool shouldExit;
    bool suppressDraw;

    GameState State;
    CFArrayRef Levels;
    int Level;
    int Lives;
    WrenRef script;

} __Demo;


extern CFXResourceManagerRef ResourceManager;


extern void* Ctor(
    DemoRef this, 
    char* title, 
    int width, 
    int height);

extern proc void SetKey(
    DemoRef this, 
    int key, 
    bool value);

extern proc void SetState(
    DemoRef this, 
    GameState state);
    
extern proc void Initialize(DemoRef this);
extern proc void LoadContent(DemoRef this);
extern proc void Update(DemoRef this);
extern proc void Draw(DemoRef this);
extern proc void Run(DemoRef this);
extern proc void Start(DemoRef this);
extern proc void ResetLevel(DemoRef this);
extern proc void ResetPlayer(DemoRef this);
extern proc void Dispose(DemoRef this);
extern proc void DoCollisions(DemoRef this);

static inline DemoRef NewDemo(char* title, int width, int height)
{
    return Ctor((DemoRef)CFCreate(Demo), title, width, height);
}

