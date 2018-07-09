#pragma once
#include "singleton.h"
#include "Engine.h"
#include "text.h"
#include <vector>

class TextManager : public Singleton<TextManager>
{
public:

	bool Initalize(Engine* engine);
	void Shutdown();
	Text* CreateText(const std::string& text, const std::string& fontName, int size, const Color& color);
	void DestroyText(Text* text);

	friend Singleton<TextManager>;
protected:
	TextManager();
protected:
	std::vector<Text*> m_texts;
	Engine * m_engine;

};

