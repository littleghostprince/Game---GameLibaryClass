#pragma once
#include "Engine.h"
#include <map>
#include "singleton.h"

class TextureManager : public Singleton<TextureManager>
{
public:

	bool Initalize(Engine* engine);
	void Shutdown();

	SDL_Texture* GetTexture(const std::string& textureName);

	friend Singleton<TextureManager>;

protected:
	TextureManager(){}
	~TextureManager(){}

private:
	Engine * m_engine;
	std::map<std::string, SDL_Texture*> m_textures;
};

