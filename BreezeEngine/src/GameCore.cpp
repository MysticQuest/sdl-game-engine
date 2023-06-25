#include <memory>
#include <random>
#include "GameCore.h"

GameCore::GameCore(MySDLWindow& sdlWindow, int frame_rate)
{
    renderSystem = std::make_unique<RenderSystem>(sdlWindow.GetRenderer());
    m_frame_rate = frame_rate;
    Run(sdlWindow);
}

GameCore::~GameCore() { }

void GameCore::PollEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (keystates[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void GameCore::Render(MySDLWindow& sdlWindow, const std::vector<Entity>& entities)
{
    sdlWindow.Clear();
    sdlWindow.Render(ecs);
    sdlWindow.Display();
}

void GameCore::Update(int deltaTime)
{
    renderSystem->Update(ecs);
    transformSystem.Update(ecs, deltaTime);
    inputSystem.Update(ecs);
}

void GameCore::Run(MySDLWindow& sdlWindow)
{
    Entity testEntity = create_entity();
    ecs.AddComponent(testEntity, RenderComponent{
        SDL_Rect{ 0, 0, 300, 230 },
        SDL_Rect{ 10, 10, 100, 73 },
        sdlWindow.LoadTexture("res/textures/pac1.png")
        });
    ecs.AddComponent(testEntity, TransformComponent{Vector2f(10, 10), Vector2f(0, 0), Vector2f(90, 90), Vector2(100, 100)});
    ecs.AddComponent(testEntity, InputComponent{});


    Uint32 before, second = SDL_GetTicks(), after;
    int deltaTime = 0;
    int frames = 0;

    while (isRunning)
    {
        before = SDL_GetTicks();

        PollEvents();

        Update(deltaTime);

        Render(sdlWindow, entities);
        
        frames++;
        after = SDL_GetTicks();
        deltaTime = after - before;

        if (after - second >= 1000)
        {
            frames = 0;
            second = after;
        }

        if (m_frame_rate > deltaTime)
        {
            SDL_Delay(m_frame_rate - deltaTime);
        }
    }
}

