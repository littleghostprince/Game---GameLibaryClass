#include "Engine.h"
#include "renderer.h"
#include "TextureManager.h"
#include "inputManager.h"
#include "audioSystem.h"
#include <cassert>
#include "vector2D.h"
#include "matrix22.h"
#include "timer.h"
#include <iostream>
#include "text.h"
#include "textManager.h"
#include <SDL_image.h>
#include "physics.h"
#include "fileSystem.h"


bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	FileSystem::Instance()->Initalize(this);
	Timer::Instance()->Initalize(this);
	Renderer::Instance()->Initalize(this);
	TextureManager::Instance()->Initalize(this);
	InputManager::Instance()->Initalize(this);
	AudioSystem::Instance()->Initalize(this);
	TextManager::Instance()->Initalize(this);
	Physics::Instance()->Initialize(this);

	m_isDebug = false;

	return true;
}

void Engine::Shutdown()
{
	Physics::Instance()->Shutdown();
	TextManager::Instance()->Shutdown();
	AudioSystem::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	Timer::Instance()->Shutdown();
	FileSystem::Instance()->Shutdown();

	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Timer::Instance()->SetTimeScale(1.0f);
	InputManager::Instance()->Update();
	AudioSystem::Instance()->update();
	Physics::Instance()->Update();
	FileSystem::Instance()->Update();

	SDL_Event event;
	SDL_PollEvent(&event);


	switch (event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isQuit = true;
		}
		break;
	}

	SDL_PumpEvents();

	if (InputManager::Instance()->GetButtonState(SDL_SCANCODE_GRAVE) == InputManager::eButtonState::PRESSED)
	{
		m_isDebug = !m_isDebug;
	}

}

