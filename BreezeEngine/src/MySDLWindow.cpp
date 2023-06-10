#include <iostream>
#include "MySDLWindow.h"

MySDLWindow::MySDLWindow(const char* title, int window_width, int window_height)
:window(nullptr), renderer(nullptr)
{
	window = SDL_CreateWindow
	(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		window_width,
		window_height,
		SDL_WINDOW_SHOWN
	);
	if (window == nullptr) { std::cout << "Window creation failed: " << SDL_GetError() << std::endl; }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) { std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl; }
}

SDL_Texture* MySDLWindow::LoadTexture(const char* filePath)
{
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(renderer, filePath);

	if (texture == nullptr)
	{
		std::cout << "Texture loading failed" << SDL_GetError() << std::endl;
	}

	return texture;
}

void MySDLWindow::Clear()
{
	SDL_RenderClear(renderer);
}

void MySDLWindow::Render(const Entity& entity)
{
	SDL_Rect srcRect;
	srcRect.x = entity.GetRect().x;
	srcRect.y = entity.GetRect().y;
	srcRect.w = entity.GetRect().w;
	srcRect.h = entity.GetRect().h;

	SDL_FRect dstRect;
	dstRect.x = entity.GetPos().x;
	dstRect.y = entity.GetPos().y;
	dstRect.w = static_cast<float>(entity.GetRect().w);
	dstRect.h = static_cast<float>(entity.GetRect().h);

	SDL_RenderCopyF(renderer, entity.GetTexture(), &srcRect, &dstRect);
}

void MySDLWindow::Display()
{
	SDL_RenderPresent(renderer);
}

void MySDLWindow::Clean()
{
	SDL_DestroyWindow(window);
}

MySDLWindow::~MySDLWindow()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}