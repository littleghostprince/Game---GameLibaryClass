#include "text.h"
#include "renderer.h"


Text::Text(const std::string & text, const std::string & fontName, int size, const Color & color)
{
	this->Create();

	TTF_Font * m_font = TTF_OpenFont(fontName.c_str(), 25);
	m_text = text;
	m_color = color;
}

Text::~Text()
{
	SDL_DestroyTexture(m_texture);
	TTF_CloseFont(m_font);
}

void Text::Draw(const Vector2D & position, float angle)
{
	if (m_texture)
	{
		Renderer::Instance()->DrawTexture(m_texture, position, angle);
	}

}

void Text::SetText(const std::string & text)
{
	if (m_text != text)
	{
		m_text = text;
		Create();
	}

}

void Text::SetText(const std::string & text, const Color & color)
{
	if (m_text != text || m_color != color)
	{
		m_text = text;
		m_color = color;
		Create();
	}

}

void Text::SetColor(const Color & color)
{
	if (m_color != color)
	{
		m_color = color;
	}
}

void Text::Create()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
	else {
		SDL_Surface* surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);
		m_texture = SDL_CreateTextureFromSurface(Renderer::Instance()->GetRenderer(), surface);
	}

}
