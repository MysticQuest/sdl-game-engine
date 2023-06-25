#include "World.h"
#include <Windows.h>
#include <string>

World::World() : breezeAPI("engine.ini", "Sample Game 1")
{
	Init();
	breezeAPI.Run();
}

void World::Init()
{
	OutputDebugString(L"Initializing World...\n");
	Entity entity = breezeAPI.AddEntity();
	std::wstring message = L"Added Entity with id: " + std::to_wstring(entity) + L'\n';
	OutputDebugString(message.c_str());
	breezeAPI.AddRenderer(entity, "res/textures/pac1.png");
	breezeAPI.AddTranform(entity, Vector2f(300, 300), Vector2f(0, 0), Vector2(1, 1));
	breezeAPI.AddInput(entity);
}

void World::Update()
{

}