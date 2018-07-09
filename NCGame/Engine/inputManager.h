#pragma once
#include "singleton.h"
#include "Engine.h"

class InputManager : public Singleton<InputManager>
{
public:
	enum eAction
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};
public:
	bool Initalize(Engine* engine);
	void Shutdown();
	void Update();

	eAction GetButtonAction(SDL_Scancode scancode);
	eAction GetMouseButtonAction(int button);
	//For Hw do get mouse button Action, GO TO SDL.WIKI and itll get the mouse button

	
	friend Singleton<InputManager>;

protected:
	InputManager();
	~InputManager();

private:
	Engine * m_engine;
	Uint8* m_prevKeystate;
	Uint8* m_keystate;
	int m_numKeys;

	Uint8* m_buttonstate[5];
	Uint8* m_prevbutton[5];
};

