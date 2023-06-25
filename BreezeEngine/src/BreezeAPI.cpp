#include "SettingsResolver.h"
#include "MySDLWindow.h"
#include "GameCore.h"
#include "ECS/ECSManager.h"
#include "BreezeAPI.h"

BreezeAPI::BreezeAPI(const std::string& settingsFile, const char* title)
{
    settings = std::make_unique<SettingsResolver>();
    Config config = settings->ReadSettings(settingsFile);
    sdl = std::make_unique<MySDLWindow>(title, config.width, config.height);
    game = std::make_unique<GameCore>(*sdl, config.frame_rate);
    ecs = &(game->ecs);
}

BreezeAPI::~BreezeAPI() = default;

void BreezeAPI::Init()
{
   
}

void BreezeAPI::Run()
{
    game->Run(*sdl);
}

Entity BreezeAPI::AddEntity()
{
    Entity entity = create_entity();
    std::cout << "Created Entity with ID: " << entity << std::endl;
    return entity;
}

void BreezeAPI::AddTranform(Entity entity, Vector2f pos, Vector2f vel, Vector2 scale)
{
    ecs->AddComponent(entity, TransformComponent{
        pos,
        vel,
        Vector2f (0,0),
        scale,
        });
}

void BreezeAPI::AddRenderer(Entity entity, const char* texturePath)
{
    SDL_Texture* texture = sdl->LoadTexture(texturePath);
    ecs->AddComponent(entity, RenderComponent{
        SDL_Rect{ 0, 0, 64, 64 },
        SDL_Rect{ 100, 100, 64, 64 },
        texture,
        });
}

void BreezeAPI::AddInput(Entity entity)
{
    ecs->AddComponent(entity, InputComponent{});
}