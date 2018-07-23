#pragma once

#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

#pragma warning(disable:4251)

#include "sdl.h"
#include <SDL_ttf.h>
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
