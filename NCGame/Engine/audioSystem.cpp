#include "audioSystem.h"
#include <assert.h>
#include "fmod.hpp"


bool AudioSystem::Initalize(Engine * engine)
{
	FMOD_RESULT result= FMOD::System_Create(&m_fmodSystem);
	assert(result == FMOD_OK);

	void * extradriverdata = nullptr;
	result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	assert(result == FMOD_OK);

	m_engine = engine;
	return true;
}

void AudioSystem::Shutdown()
{
	for (auto audio : m_sounds)
	{
		audio.second->release();
	}
	m_sounds.clear();

	m_fmodSystem->close();
	m_fmodSystem->release();
}

void AudioSystem::update()
{
	FMOD_RESULT result = m_fmodSystem->update();
	assert(result == FMOD_OK);
}

void AudioSystem::AddSound(const std::string & id, const std::string & filename)
{
	auto iter = m_sounds.find(filename); // checks to see if its already there
	FMOD::Sound * music;

	if (iter == m_sounds.end())
	{
		m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &music);
		m_sounds[id] = music;
	}
}

void AudioSystem::Playsound(const std::string & id)
{
	auto iter = m_sounds.find(id); // checks to see if its already there

	if (iter != m_sounds.end())
	{
	 m_fmodSystem->playSound(m_sounds[id], 0, false, &channel);
	}
}

void AudioSystem::RemoveSound(const std::string & id)
{
	auto iter = m_sounds.find(id); // checks to see if its already there

	if (iter != m_sounds.end())
	{
		m_sounds[id]->release();
		m_sounds.erase(iter);
	}
}

AudioSystem::AudioSystem()
{
}


AudioSystem::~AudioSystem()
{
}
