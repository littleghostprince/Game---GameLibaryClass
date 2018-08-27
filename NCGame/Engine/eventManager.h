#pragma once
#include "singleton.h"
#include "engine.h"
#include "event.h"
#include "eventManager.h"
#include "eventReciver.h"

class ENGINE_API EventManager : public Singleton<EventManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void SentMessage(const Event& event);
	void SendGameMessage(const Event& event);

	void SetEventReceiver(EventReceiver* eventReciver) { m_gameEventReceiver = eventReciver; }

protected: 
	friend Singleton<EventManager>;

protected:
	Engine * m_engine;
	EventReceiver* m_gameEventReceiver = nullptr;
};

