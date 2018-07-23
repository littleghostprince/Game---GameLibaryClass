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

	/*Entity* entity = new Entity(ID("player"));
	TransformComponent* transformComponent = new TransformComponent(entity);
	transformComponent->Create(Vector2D(400.0f, 500.0f));
	entity->AddComponent(transformComponent);

	SpriteComponent* spriteComponent = new SpriteComponent(entity);
	spriteComponent->Create("..\\content\\ship.bmp");
	entity->AddComponent(spriteComponent);

	*/

//	Entity* fentity = m_scene->FindEntity(ID("player"));

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
	//float h = InputManager::Instance()->GetActionAxisAbsolute("steer");
	//std::string str = std::to_string(h);

	//std::vector<Color> colors = { Color::red, Color::green, Color::white };
	//text->SetText(str, colors[rand() % colors.size()]);
	//text->Draw(Vector2D(200.0f, 300.0f), 0.0f);


}
