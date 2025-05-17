#include "Demo.h"
#include "GameObject.h"
#include "BallObject.h"
#include "GameLevel.h"
#include "Collision.h"
#include "Wren.h"
#include <math.h>


class(Demo);

typedef void (*DemoProc)(DemoRef this);

static const Vec2 PLAYER_SIZE = { 100, 20 };                        // Initial size of the player paddle
static const GLfloat BALL_RADIUS = 12.5f;                           // Radius of the ball object
static const Vec2 ZERO = { 0, 0 };
static const Vec3 WHITE = { 1, 1, 1 };

// Game-related State data
CFXResourceManagerRef ResourceManager;
static CFXArrayRendererRef Renderer;
static GameObjectRef Player;
static BallObjectRef Ball;


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///// methods
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void* Ctor(DemoRef this, char* title, int width, int height)
{
    static __CFXGameVtbl vtable = {
        .Initialize =   (CFXGameProc)((DemoProc)Initialize),
        .LoadContent =  (CFXGameProc)((DemoProc)LoadContent),
        .Update =       (CFXGameProc)((DemoProc)Update),
        .Draw =         (CFXGameProc)((DemoProc)Draw),
    };

    Ctor((CFXGameRef)this, title, width, height, this, &vtable);

    this->Levels = CFNew(CFArray, nullptr);
    this->Level = 0;
    this->State = GAME_ACTIVE;
    this->width = width;
    this->height = height;
    this->script = NewWren();
    ResourceManager = NewCFXResourceManager();

    return (void*)this;
}

proc void Initialize(DemoRef this)
{
}


proc void LoadContent(DemoRef this)
{

    // Load shaders
    LoadShader(ResourceManager, "Resources/shaders/es/sprite.vs", "Resources/shaders/es/sprite.fs", "sprite");

    // Configure shaders
    Mat projection = glm_ortho(0, (GLfloat)this->width, (GLfloat)this->height, 0, -1, 1);
    CFXShaderRef shader = GetShader(ResourceManager, "sprite");
    Use(shader);
    SetInteger(shader, "sprite", 0);
    SetMatrix(shader, "projection", &projection);

    // Load textures
    LoadTexture(ResourceManager, "Resources/textures/block.png", false, "block");
    LoadTexture(ResourceManager, "Resources/textures/paddle.png", false, "paddle");
    LoadTexture(ResourceManager, "Resources/textures/block.png", false, "block");
    LoadTexture(ResourceManager, "Resources/textures/block_solid.png", false, "block_solid");
    LoadTexture(ResourceManager, "Resources/textures/awesomeface.png", true, "face");
    LoadTexture(ResourceManager, "Resources/textures/background.jpg", false, "background");
    // Set render-specific controls
    Renderer = NewCFXArrayRenderer(GetShader(ResourceManager, "sprite"));

    // Load levels
    Add(this->Levels, NewGameLevel("Resources/levels/one.lvl", this->width, this->height * 0.5));
    Add(this->Levels, NewGameLevel("Resources/levels/two.lvl", this->width, this->height * 0.5));
    Add(this->Levels, NewGameLevel("Resources/levels/three.lvl", this->width, this->height * 0.5));
    Add(this->Levels, NewGameLevel("Resources/levels/four.lvl", this->width, this->height * 0.5));

    // Configure game objects
    Vec2 playerPos = (Vec2) { (int)(this->width / 2) - PLAYER_SIZE.x / 2, this->height - PLAYER_SIZE.y };
    Player = NewGameObject("player", playerPos, PLAYER_SIZE, GetTexture(ResourceManager, "paddle"), WHITE);
    Vec2 ballPos = playerPos + (Vec2) { PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2 };
    Ball = NewBallObject(ballPos, BALL_RADIUS, GetBallVelocity(this->script), GetTexture(ResourceManager, "face"));
}

proc void Update(DemoRef this)
{
    // Update objects
    Move(Ball, this->delta, this->width);
    // Check for collisions

    DoCollisions(this);
    // // Check loss condition
    // if (Ball->Position.x > this->height) // Did ball reach bottom edge?
    // {
    //     --this->Lives;
    //     if (this->Lives <= 0) {
    //         ResetLevel(this);
    //     }   
    //     ResetPlayer(this);
    // }

    if (this->State == GAME_ACTIVE) {
        // GLfloat velocity = PLAYER_VELOCITY * this->delta;
        GLfloat velocity = GetPlayerVelocity(this->script) * this->delta;
        // Move playerboard
        if (this->keys[GLFW_KEY_A] || this->keys[GLFW_KEY_LEFT]) {
            if (Player->Position.x >= 0) {
                Player->Position.x -= velocity;
                if (Ball->Stuck)
                    Ball->Position.x -= velocity;
            }
        }
        if (this->keys[GLFW_KEY_D] || this->keys[GLFW_KEY_RIGHT]) {
            if (Player->Position.x <= this->width - Player->Size.x) {
                Player->Position.x += velocity;
                if (Ball->Stuck)
                    Ball->Position.x += velocity;
            }
        }
        if (this->keys[GLFW_KEY_SPACE])
            Ball->Stuck = false;
    }

}

proc void Draw(DemoRef this)
{
    float r = 0.392156f;
    float g = 0.584313f;
    float b = 0.929411f;

    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (this->State == GAME_ACTIVE) {
        // Draw background
        CFXRect bounds = { 0, 0, this->width, this->height };
        Draw(Renderer, GetTexture(ResourceManager, "background"), &bounds, 0.0f, WHITE);
        GameLevelRef level = Get(this->Levels, this->Level);
        Draw(level, Renderer);
        Draw(Player, Renderer);
        Draw(Ball, Renderer);
    }


    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

proc void Run(DemoRef this)
{
    Run((CFXGameRef)this);
}

/**
 * ResetLevel
 * Ctor
 */
proc void ResetLevel(DemoRef this)
{
    if (this->Level == 0) {
        GameLevelRef level = Get(this->Levels, 0);
        Load(level, "Resources/levels/one.lvl", this->width, this->height * 0.5f);
    } else if (this->Level == 1) {
        GameLevelRef level = Get(this->Levels, 1);
        Load(level, "Resources/levels/two.lvl", this->width, this->height * 0.5f);
    } else if (this->Level == 2) {
        GameLevelRef level = Get(this->Levels, 2);
        Load(level, "Resources/levels/three.lvl", this->width, this->height * 0.5f);
    } else if (this->Level == 3) {
        GameLevelRef level = Get(this->Levels, 3);
        Load(level, "Resources/levels/four.lvl", this->width, this->height * 0.5f);
    }
    this->Lives = 3;
}

/**
 * ResetPlayer
 * 
 */
proc void ResetPlayer(DemoRef this)
{
    Player->Size = PLAYER_SIZE;
    Player->Position = (Vec2) { (int)(this->width / 2) - PLAYER_SIZE.x / 2, this->height - PLAYER_SIZE.y };
    Reset(Ball, Player->Position + (Vec2) { PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2) }, GetBallVelocity(this->script));
}

//===============================================================//
// -------------------- C O L L I S I O N S -------------------- //
//===============================================================//

/**
 * Calculates which direction a vector is facing (N,E,S or W)
 * 
 */
static inline Direction ArrayDirection(Vec2 target)
{
    Vec2 compass[4] = {
        { 0.0f, 1.0f }, // up
        { 1.0f, 0.0f }, // right
        { 0.0f, -1.0f }, // down
        { -1.0f, 0.0f } // left
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    target = glm_normalize(target);
    for (GLuint i = 0; i < 4; i++) {
        GLfloat dot_product = glm_dot(target, compass[i]);
        if (dot_product > max) {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}

/**
 * CheckCollision2
 * 
 * @param one first game object to check
 * @param two second game object to check
 * 
 */
static GLboolean CheckCollision2(DemoRef this, GameObjectRef one, GameObjectRef two) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = one->Position.x + one->Size.x >= two->Position.x && two->Position.x + two->Size.x >= one->Position.x;
    // Collision y-axis?
    bool collisionY = one->Position.y + one->Size.y >= two->Position.y && two->Position.y + two->Size.y >= one->Position.y;
    // Collision only if on both axes
    return collisionX && collisionY;
}

/**
 * CheckCollision2
 * 
 * @param one first ball object to check
 * @param two second game object to check
 * 
 */
static CollisionRef CheckCollision(
    DemoRef this,
    BallObjectRef one,
    GameObjectRef two) // AABB - Circle collision
{
    // Get center point circle first
    Vec2 center = { one->Position + one->Radius };
    // Calculate AABB info (center, half-extents)
    Vec2 aabb_half_extents = { two->Size.x / 2, two->Size.y / 2 };
    Vec2 aabb_center = { two->Position.x + aabb_half_extents.x, two->Position.y + aabb_half_extents.y };
    // Get difference vector between both centers
    Vec2 difference = center - aabb_center;

    Vec2 clamped = glm_clamp(difference, -aabb_half_extents, aabb_half_extents);

    // Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
    Vec2 closest = aabb_center + clamped;
    // Now retrieve vector between center circle and closest point AABB and check if length < radius
    difference = closest - center;

    if (glm_length(difference) < one->Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
        return NewCollision(true, ArrayDirection(difference), difference);
    else
        return NewCollision(false, UP, (Vec2) { 0, 0 });
}

/**
 * DoCollisions
 * 
 */
proc void DoCollisions(DemoRef this)
{
    GameLevelRef level = Get(this->Levels, this->Level);
    CFArrayRef bricks = level->Bricks;

    for (int i = 0; i < Length(bricks); i++) {
        GameObjectRef box = Get(bricks, i);

        if (!box->Destroyed) {
            CollisionRef collision = CheckCollision(this, Ball, box);
            if (collision->IsTrue) // If collision is true
            {
                // Destroy block if not solid
                if (!box->IsSolid)
                    box->Destroyed = GL_TRUE;
                // Collision resolution
                Direction dir = collision->Dir;
                Vec2 diff_vector = collision->Vec;
                if (dir == LEFT || dir == RIGHT) // Horizontal collision
                {
                    Ball->Velocity.x = -Ball->Velocity.x; // Reverse horizontal velocity
                    // Relocatej
                    GLfloat penetration = Ball->Radius - fabsf(diff_vector.x);
                    if (dir == LEFT)
                        Ball->Position.x += penetration; // Move ball to right
                    else
                        Ball->Position.x -= penetration; // Move ball to left;
                } else // Vertical collision
                {
                    Ball->Velocity.y = -Ball->Velocity.y; // Reverse vertical velocity
                    // Relocate
                    GLfloat penetration = Ball->Radius - fabsf(diff_vector.y);
                    if (dir == UP)
                        Ball->Position.y -= penetration; // Move ball bback up
                    else
                        Ball->Position.y += penetration; // Move ball back down
                }
            }
        }
    }
    // Also check collisions for player pad (unless stuck)
    CollisionRef result = CheckCollision(this, Ball, Player);
    if (!Ball->Stuck && result->Dir) {
        // Check where it hit the board, and change velocity based on where it hit the board
        GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
        GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
        GLfloat percentage = distance / (Player->Size.x / 2);
        // Then move accordingly
        GLfloat strength = 2.0f;
        Vec2 oldVelocity = { Ball->Velocity.x, Ball->Velocity.y };
        Ball->Velocity.x = GetBallVelocity(this->script).x * percentage * strength;
        //Ball->Velocity.y = -Ball->Velocity.y;
        Ball->Velocity = glm_normalize(Ball->Velocity) * glm_length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        // Fix sticky paddle
        Ball->Velocity.y = -1 * fabsf(Ball->Velocity.y);
    }
}
