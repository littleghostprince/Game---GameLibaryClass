#include "audioSystem.h"



bool AudioSystem::Initalize(Engine * engine)
{
	m_engine = engine;
	return true;
}

void AudioSystem::Shutdown()
{
}

AudioSystem::AudioSystem()
{
}


AudioSystem::~AudioSystem()
{
}
