#pragma once
#include "singleton.h"
#include "Engine.h"
class AudioSystem : public Singleton<AudioSystem>
{
public:
	bool Initalize(Engine* engine);
	void Shutdown();

	friend Singleton<AudioSystem>;

protected:
	AudioSystem();
	~AudioSystem();

private:
	Engine * m_engine;
};

