#pragma once

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

#include "sdl.h"

class TextureManager;

class ENGINE_API Engine
{
public:
	Engine() {}
	~Engine() {}
	
	bool Initialize();
	void Update();
	void Shutdown();

	bool isQuit() { return m_isQuit; }
	SDL_Window * GetWindow() { return m_window; }

protected:
	bool m_isQuit = false;
	SDL_Window * m_window;
	

};
