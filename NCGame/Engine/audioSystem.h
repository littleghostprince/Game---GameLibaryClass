#pragma once
#include "singleton.h"
#include "Engine.h"
#include <string>
#include <fmod.hpp>
#include <map>

class ENGINE_API AudioSystem : public Singleton<AudioSystem>
{
public:
	bool Initalize(Engine* engine);
	void Shutdown();
	void update();

	void AddSound(const std::string & id, const std::string& audioname);
	void Playsound(const std::string& id);
	void RemoveSound(const std::string& id);
	
	friend Singleton<AudioSystem>;


protected:
	AudioSystem();
	~AudioSystem();

private:
	Engine * m_engine;

	FMOD::System* m_fmodSystem;
	std::map<std::string, FMOD::Sound*> m_sounds;
	FMOD::Channel *channel = 0;
};

