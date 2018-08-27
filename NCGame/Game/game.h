#pragma once

#include "eventReciver.h"

class StateMachine;
class Engine;
class Scene;

class Game: public EventReceiver
{
public:
	Game(Engine * engine) : m_engine(engine) {};
	~Game();

	bool Initalize();
	void Shutdown();
	void Update();

	bool Run() { return m_running; }

	void OnEvent(const Event& event);

protected:
	size_t m_score = 0;

	bool m_running = false;
	Engine* m_engine = nullptr;
	Scene* m_scene = nullptr;
	StateMachine* m_stateMachine = nullptr;
};

