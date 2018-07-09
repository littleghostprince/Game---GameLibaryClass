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

	text = TextManager::Instance()->CreateText("Hello!", "..\\content\\Inconsolata-Bold.ttf", 24, Color::red);

	Timer::Instance()->Initalize(this);
	Renderer::Instance()->Initalize(this);
	TextureManager::Instance()->Initalize(this);
	InputManager::Instance()->Initalize(this);
	AudioSystem::Instance()->Initalize(this);


	return true;
}

void Engine::Shutdown()
{
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

	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	text->SetColor(colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);


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

	if (InputManager::Instance()->GetButtonAction(SDL_SCANCODE_A) == InputManager::eAction::PRESSED)
	{
		std::cout << "pressed" << std::endl;
	}

	if ((InputManager::Instance()->GetButtonAction(SDL_SCANCODE_A) == InputManager::eAction::PRESSED) || 
		(InputManager::Instance()->GetButtonAction(SDL_SCANCODE_A) == InputManager::eAction::HELD))
	{
		angle -= 90.0f * Timer::Instance()->DeltaTime();
	}

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	if (keystate[SDL_SCANCODE_LEFT]) angle -= 90.0f * Timer::Instance()->DeltaTime(); // How far you want to rotate in 1 second
	if (keystate[SDL_SCANCODE_RIGHT])angle += 90.0f * Timer::Instance()->DeltaTime();

	Vector2D force = Vector2D::zero;
	if (keystate[SDL_SCANCODE_DOWN]) force.y = 200.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_UP]) force.y = -200.0f * Timer::Instance()->DeltaTime();

	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force; 


	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::orange);
	//Draw
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");
	Renderer::Instance()->DrawTexture(texture, position, angle);

	//Scale Draw
	//const Vector2D scale(13.0f, 10.0f);
	//Renderer::Instance()->DrawTexture(texture, position, scale, 0.0f);

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

