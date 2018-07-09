#pragma once
#include "singleton.h"
#include "Engine.h"
#include "text.h"
#include <vector>

class TextManager : public Singleton<TextManager>
{
public:
	TextManager();
	~TextManager();

	bool Initalize(Engine* engine);
	void Shutdown();
	Text* CreateText(const std::string& text, const std::string& fontName, int size, const Color& color);
	void DestroyText(Text* text);

protected:
	std::vector<Text*> m_texts;
	Engine * m_engine;

};

