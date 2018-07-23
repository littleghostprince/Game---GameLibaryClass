#include "game.h"
#include "Engine.h"
#include "inputManager.h"
#include "audioSystem.h"
#include "textManager.h"
#include "TextureManager.h"
#include "text.h"
#include "timer.h"
#include "renderer.h"
#include <iostream>
#include "matrix22.h"
#include "entity.h"
#include "transformComponent.h"
#include "spriteComponent.h"
#include "scene.h"
#include "shipControllerComponent.h"

Vector2D position(400.0f, 300.0f);
float angle = 0.0f;
Text* text;


Game::~Game()
{
}

bool Game::Initalize()
{
	bool success = m_engine->Initialize();

	m_scene = new Scene();

	for (size_t i = 0; i < 1; i++)
	{

		Entity* entity = new Entity();
		TransformComponent* transformComponent = new TransformComponent(entity);
		float x = (float)(rand() % 800);
		float y = (float)(rand() % 600);

		transformComponent->Create(Vector2D(x, y));
		entity->AddComponent(transformComponent);

		SpriteComponent* spriteComponent = new SpriteComponent(entity);
		spriteComponent->Create("..\\content\\ship.png");
		entity->AddComponent(spriteComponent);

		ShipControllerComponent* shipControllerComponent = new ShipControllerComponent(entity);
		shipControllerComponent->Create(20.0);
		entity->AddComponent(shipControllerComponent);
	
		m_scene->AddEntity(entity);
	}


	m_running = success;



	return success;
}

void Game::Shutdown()
{
	m_engine->Shutdown();
}

void Game::Update()
{
	InputManager::Instance()->Update();
	Timer::Instance()->Update();

	m_running = !m_engine->isQuit();

	m_engine->Update();
	m_scene->Update();

	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);

	//draw
	m_scene->Draw();

	Renderer::Instance()->EndFrame();


}
