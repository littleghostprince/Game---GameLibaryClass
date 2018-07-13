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

Vector2D position(400.0f, 300.0f);
float angle = 0.0f;
Text* text;

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);


	Timer::Instance()->Initalize(this);
	Renderer::Instance()->Initalize(this);
	TextureManager::Instance()->Initalize(this);
	InputManager::Instance()->Initalize(this);
	AudioSystem::Instance()->Initalize(this);
	TextManager::Instance()->Initalize(this);

	InputManager::Instance()->AddAction("fire", SDL_BUTTON_LEFT, InputManager::eDevice::MOUSE);
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("steer", InputManager::eAxis::X,InputManager::eDevice::MOUSE);
	InputManager::Instance()->AddAction("horn", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
	
	AudioSystem::Instance()->AddSound("horn", "..\\content\\horn.wav");
	
	text = TextManager::Instance()->CreateText("Hello There", "..\\content\\comicsans.ttf", 100, Color::red);

	return true;
}

void Engine::Shutdown()
{
	TextManager::Instance()->Initalize(this);
	AudioSystem::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	Timer::Instance()->Shutdown();
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Timer::Instance()->SetTimeScale(2.0f);
	InputManager::Instance()->Update();



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

	int x, y;
	SDL_GetMouseState(&x, &y);

	//input

	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		std::cout << "pressed" << std::endl;
	}
	if (InputManager::Instance()->GetActionButton("horn") == InputManager::eButtonState::PRESSED) 
	{ 
		AudioSystem::Instance()->Playsound("horn");
	}

	/*
	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD))
	{
		angle -= 90.0f * Timer::Instance()->DeltaTime();
	}

	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
		angle += 90.0f * Timer::Instance()->DeltaTime();
	}
	*/

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);

	float steer = InputManager::Instance()->GetActionAxisRelative("steer");
	angle += (steer * 50.0f) * Timer::Instance()->DeltaTime();

	//if (keystate[SDL_SCANCODE_LEFT]) angle -= 90.0f * Timer::Instance()->DeltaTime(); // How far you want to rotate in 1 second
	//if (keystate[SDL_SCANCODE_RIGHT])angle += 90.0f * Timer::Instance()->DeltaTime();

	Vector2D force = Vector2D::zero;
	if (keystate[SDL_SCANCODE_DOWN]) force.y = 200.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_UP]) force.y = -200.0f * Timer::Instance()->DeltaTime();


	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force; 
	

	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);
	//Draw
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");
	Renderer::Instance()->DrawTexture(texture, position, angle);

	//Scale Draw
	//const Vector2D scale(13.0f, 10.0f);
	//Renderer::Instance()->DrawTexture(texture, position, scale, 0.0f);

	float h = InputManager::Instance()->GetActionAxisAbsolute("steer");
	std::string str = std::to_string(h);

	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	text->SetText(str, colors[rand() % colors.size()]);
	//text->SetColor(colors[rand() % colors.size()]);
	text->Draw(Vector2D(200.0f, 300.0f), 0.0f);


	Renderer::Instance()->EndFrame();

	



	/*SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	//Draw
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = 64;
	rect.h = 64;

	SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\cat.bmp");
	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	//SDL_RenderFillRect(m_renderer, &rect);
	//SDL_RenderCopy(m_renderer, m_texture, nullptr, &rect);
	SDL_RenderCopyEx(m_renderer, 
		texture, nullptr, &rect, 45.0, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(m_renderer);
	*/
}

