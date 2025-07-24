# How to make a game

BrewEngine is a entity component system based framework written in c++ and can be used for any small 2D game. 

## Dependencies

- **GLFW**: Window management and input
- **GLAD**: OpenGL loading
- **GLM**: Mathematics library for graphics
- **SoLoud**: Audio engine
- **leif**: UI framework
- **stb_image**: Image loading

## Get Started

First you create a directory for your game where you first include a CMake file:
The CMake file of your game should look something like this:

```cmake
cmake_minimum_required(VERSION 3.18)

project(CreationTermination)

# set variables for source files
    set(SOURCE_FILES
        # all your header and cpp files will be listed here
    )

    # set executable name
    set(EXE_FILE CreationTermination)

    # add the executable target
    add_executable(${EXE_FILE} ${SOURCE_FILES})

    # require C++ 17 compiler
    target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

    #### link with the BrewEngine library! ####
    target_link_libraries(${EXE_FILE} PRIVATE BrewEngine)

    target_compile_definitions(${EXE_FILE} PRIVATE ASSET_ROOT=./assets/)

    add_custom_target(copy_dir_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/CreationTermination/assets)
    add_dependencies(${EXE_FILE} copy_dir_assets)
```

The subdirectories `Components` and `Systems` should be added as well.

Further you would need a main.cpp that will eventually call the run function of your game and a Game class which inherits form the Game file of the Engine. 
This Game file is essentially the root of your game where you use the `start()` function to load and initilize everything you need right at the start of the game. Your game file also has access to the `update()` function which runs every frame and can be use for universal game logic, but alot of the game logic can be handled inside the systems. Create a game object and call with it run inside the `main()` function to run the game. 

```cpp
#include "brewEngine/Game.h"
 
class MyGame : public gl3::brewEngine::Game {
public:
    MyGame(int width, int height, const std::string &title) 
        : Game(width, height, title) {}
 
private:
    void start() override;
 
    void update(GLFWwindow *window) override;
 
    void draw() override;
};
 
```
```cpp
#include "MyGame.h"

int main() {
    MyGame game(1280, 720, "My Game");
    game.run();
    return 0;
}
```

## Game States

BrewEngine supports four built-in game states:
 
```cpp
enum GameState {
    GAME_INTRO,    // Introduction/menu state
    GAME_ACTIVE,   // Main gameplay state
    GAME_OVER,     // Game over state
    GAME_WIN       // Victory state
};
```
 
Access and modify game state using:
```cpp
GameState currentState = getGameState();
setGameState(GAME_ACTIVE);
```
 
## Entities

Entites are just unique identifiers in this case of the type `guid_t`, the represent the game objects.

- `guid()` returns the ID of the entity: 
- `isDeleted()` returns a bool, if the entity has been deleted or not

### Entity Manager

The methods of the Enity Manger can be accessed through your game file. 

```cpp
// Create an entity
Entity* Player = &entityManager.createEntity();
 
// get an entity with their ID
guid_t guid = 1;
Entity* Enemy = &entityManager.getEntity(guid);

// delete an entity
entityManager.deleteEntity(*Player);
```

## Components

Components are the ones who describe what an entity is and what its role is inside the game, but most importantly it stores the entity's data. They usually only consist of a header file and are obviously stored inside the Components directory. 

A class becomes a component if it inherits form `gl3::brewEngine::ecs::Component`

```cpp
class HealthComponent : public Component {
    // both of these friend classes always have to be included in a Component class
    friend ComponentManager; 
    friend Entity;
 
public:
    int maxHealth = 100;
    int currentHealth = 100;
 
private:
    // the owner parameter has to always be given to the constructor, but if a component is 
    // given to an entity it should not be given a value, that is what the engine already does.
    explicit HealthComponent(guid_t owner, int maxHp = 100) 
        : Component(owner), maxHealth(maxHp){}
};
```

The naming convention of entities is that they are writtten with a capital letter while all its components start with a lower case letter. The components name looks like this:
`HealthComponent* playerHealth = &Player->addComponent<HealthComponent>(5)`

### Component Manager and component managing

```cpp
// Add component to entity
HealthComponent* health = &Player->addComponent<HealthComponent>(100);
 
// Get component from entity
HealthComponent* health = &Player->getComponent<HealthComponent>();
 
// Remove component
Player->removeComponent<HealthComponent>();

// Check if entity has a certain Componant
bool hasHealth = componentManager.hasComponent<HealthComponent>(Player->guid());
 
// Get component from ComponentManager
HealthComponent* health = componentManager.getComponent<HealthComponent>(entityId);

// Go through every Component of the same type
componentManager.forEachComponent<HealthComponent>([&](HealthComponent& component){
    // Do something with those components inside the lambda function
});
```

### Build-in Components

#### Transform

Handles position, rotation, scale, and radius for collision purposes:
 
```cpp
Player = &entityManager.createEntity();
witchTransform = &Witch->addComponent<TransformComponent>(origin, glm::vec2(100, 100), 0, glm::vec2(120*1.6, 120), 60);
```

#### Collision
Giving an entity the ColliderComponent gives it the ability to collide with other entities which have a ColliderComponent as well.
if two entites collide that have the same type a collision won't trigger.
Example: A entity representing the player will have a ColliderComponent with the type @enum PLAYER,
this player can create missiles which are also entities with a ColliderComponent. In order to prevent the player colliding with its own missiles
the ColliderComponent of the missiles is also of the type PLAYER.

An overload of the ColliderComponent constructor that includes the member @param timeBetweenDamage
which can be used to prevent certain effects to take place on collision for a given amount of time, like health reduction.
```cpp
explicit ColliderComponent(guid_t owner, CollisionCategory type, float timeBetweenDamage,
                std::function <void()> handleCollision)
                : Component(owner), timeBetweenDamage(timeBetweenDamage) ,type(type), handleCollision(std::move(handleCollision)) {}
```

`handleCollision()` is a lambda function that is a parameter of the ColliderComponent constructor.
If the user adds a ColliderComponent to an entity, handleCollision's definition is the input.
This function will only get called on collision.

```cpp
playerCollider = &Player->addComponent<ColliderComponent>(PLAYER, 1.0f, [this] {
        //This method will only be called on collision
            // this implementation reduces the health of the Player/Witch

        // getting a new collider pointer to prevent having to stash it inside the lambda function
        ColliderComponent* collider = &Witch->getComponent<ColliderComponent>();

        // the invulnerable state serves the prevention of immediate death
        if (collider->isInvulnerable || collider->isShielded) return;

        --playerHealth->health;
        collider->invulnerabilityTimer = collider->timeBetweenDamage;
        collider->isInvulnerable = true;

        if(witchHealth->health == 0) {
            entityManager.deleteEntity(*Player);
        }
    });
```

#### Sprites

By giving an entity a SpriteComponent it will automatically be rendered and or animated. 

```cpp
// Static sprite
SpriteComponent* sprite = &entity->addComponent<SpriteComponent>(
    LoadedSprite, 
    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) //color
);
 
// Animated sprite sheet
SpriteComponent* animSprite = &Entity->addComponent<SpriteComponent>(
        LoadedSpriteSheet,
        glm::vec2(LoadedSpriteSheet.getImageWidth()/4, LoadedSpriteSheet.getImageHeight()),
        4, //Sprite sheet consists of 4 frames in this case
        10,//Frams per second
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) //Color
        );
```

#### BackgroundComponent

An entity with a BackgroundComponent is like the name implies the Background of the games scene.
Background entities have the possibility to scroll.
To make the scrolling seamless a copy of the backgrounds sprite will be rendered which ideally will be positioned at the end of the original sprite
even though the user can freely choose what value copyPosition should have. While the background moves the original image and the copy
will switch places, this results in an endless loop.
The User has also the possibility to change the speed of the scrolling, if the background should not scroll the speed should be set to 0.
If  isScrollingSideways and goesLeftOrUp is true then the background will scroll to the left.
If isScrollingSideways is true but goesLeftOrUp is false then the background will scroll to the right.
If isScrollingSideways is false but goesLeftOrUp is true the background will move up along the y axis.
If isScrollingSideways and goesLeftOrUp is false, the background will go down
Depending on if the background should left, right, up or down the copy should be positioned accrodingly.

```cpp
BackgroundComponent* backgroundComponents_Layer1 = 
&Background_Layer1->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 800.0f, true, true);
```

## Systems

Systems contain game logic and operate on entities with specific components. They make the most use of the events. All systems inherit from `gl3::brewEngine::ecs::System`:
 
```cpp
class PlayerSystem : public System {
public:
    explicit PlayerSystem(Game &game) : System(game) {
        // Subscribe to game events
        engine.onUpdate.addListener([&, Player](Game& game, float deltaTime) {
            TransformComponent* playerTransform = &Player->getComponent<TransformComponent>();
            playerMovement(game, playerTransform, deltaTime);
        });
    }
 
private:
    void playerMovement(Game& game, TransformComponent* pt, float deltaTime) {
        if (playerComponent && transform) {
            // Handle player movement, input, etc.
        }
    }
};
```
Initialize all the Systems you created inside your game file in the start method:

```cpp
// Inside the header file
//Systems
    std::unique_ptr<IntroSystem> introSystem;
    std::unique_ptr<GameOverSystem> gameOverSystem;
    std::unique_ptr<RenderingSystem> renderSystem;
    std::unique_ptr<PlayerSystem> playerSystem;
    std::unique_ptr<MissileSystem> missileSystem;
    std::unique_ptr<ShieldSystem> shieldSystem;
    std::unique_ptr<EnemySystem> enemySystem;
    std::unique_ptr<CollisionSystem> collisionSystem;

```

```cpp
// Inside the cpp file and the start() method

    introSystem = std::make_unique<IntroSystem>(*this, CutScene);
    enemySystem = std::make_unique<EnemySystem>(*this, Creature);
    playerSystem = std::make_unique<PlayerSystem>(*this, Witch, shieldCooldownUiNumber);
    collisionSystem = std::make_unique<CollisionSystem>(*this);
    missileSystem = std::make_unique<MissileSystem>(*this);
    shieldSystem = std::make_unique<ShieldSystem>(*this);

```

Idealy after you created all the necessary entities and such. 

## Event System

The engine uses a robust event system for decoupled communication:
 
```cpp
// Available events in Game class:
game.onStartup.addListener([](Game& game) {});
 
game.onAfterStartup.addListener([](Game& game) {});
 
game.onBeforeUpdate.addListener([](Game& game) {});
 
game.onUpdate.addListener([](Game& game, float deltaTime) {});
 
game.onAfterUpdate.addListener([](Game& game) {});
 
game.onBeforeShutdown.addListener([](Game& game) {});
 
game.onShutdown.addListener([](Game& game) {});
```

## Input

The input system provides keyboard input handling:
 
```cpp
#include "brewEngine/input/Input.h"
 
// Check if key is currently pressed
if (Input::IsKeyPressed(Input::KEY_SPACE)) {
    // Space key is pressed this frame
}
 
// Check if key is held down
if (Input::IsKeyDown(Input::KEY_W)) {
    // W key is being held down
}
 
// Check if key was released
if (Input::IsKeyReleased(Input::KEY_ESCAPE)) {
    // Escape key was released this frame
}
 
// Check if key is not pressed
if (Input::IsKeyUp(Input::KEY_ENTER)) {
    // Enter key is not pressed
}
```
To access a Key this engine uses custom names, but are just openGL macros in disguise

## Load Textures

Load and manage textures using the `Texture2D` class:
 
```cpp
#include "brewEngine/rendering/Texture2D.h"
 
// Load texture from file
Texture2D texture = Texture2D::FromFile("path/to/image.png");
 
// Texture properties
unsigned int width = texture.Width;
unsigned int height = texture.Height;
unsigned int internalFormat = texture.Internal_Format;
```
 
### MVP Matrix Calculation
 
The engine provides utility functions for matrix calculations:
 
```cpp
glm::mat4 mvpMatrix = game.calculateMvpMatrix(
    glm::vec3(position.x, position.y, 0.0f),
    rotationInDegrees,
    glm::vec3(scale.x, scale.y, 1.0f)
);
```

## Audio System
 
BrewEngine uses SoLoud for audio. Access the audio engine through the Game class:
 
```cpp
// In your game's start() method
SoLoud::Wav audioClip;
audioClip.load("assets/audio/sound.wav");
 
// Play audio
audio.play(audioClip);
```

### Key Engine Capabilities
 
- **Sprite Animation**: Full sprite sheet animation support with configurable frame rates
- **Collision Detection**: Spatial grid-based collision system for performance
- **Audio Integration**: Built-in SoLoud audio engine for sound effects and music
- **Input Handling**: Comprehensive keyboard input system
- **UI Support**: Integration with leif UI framework
- **Asset Management**: Streamlined asset loading and path resolution
- **Game State Management**: Built-in state system for menus, gameplay, and game over screens
- **Event-Driven Architecture**: Decoupled system communication

## Best Practices
 
### 1. System Organization
- Create systems in the `start()` method of your game
- Subscribe to appropriate events in system constructors
- Keep system logic focused and single-purpose
 
### 2. Component Design
- Keep components as data containers only
- Put logic in systems, not components
- Use friend classes for ComponentManager and Entity access
 
### 3. Memory Management
- Use smart pointers for systems (`std::unique_ptr`)
- Let the engine manage entity and component lifetimes
- Be careful with raw pointers to components (they may become invalid)
 
### 5. Asset Loading
- Load assets in the `start()` method
- Use the asset path resolution utilities