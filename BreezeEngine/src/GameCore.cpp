#include <memory>
#include <random>
#include "GameCore.h"

GameCore::GameCore(MySDLWindow& sdlWindow, int frame_rate)
{
    ecs = ECSManager();
    renderSystem = std::make_unique<RenderSystem>(sdlWindow.GetRenderer());
    m_frame_rate = frame_rate;
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
    transformSystem->Update(ecs, deltaTime);
    inputSystem->Update(ecs);
}

void GameCore::Run(MySDLWindow& sdlWindow)
{
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

