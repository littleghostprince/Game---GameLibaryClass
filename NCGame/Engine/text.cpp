#include "text.h"
#include "renderer.h"
#include "texture.h"
#include "fileSystem.h"

Text::Text()
{

}

Text::~Text()
{
	m_texture->Destroy();
	TTF_CloseFont(m_font);
}

void Text::Create(const std::string & text, const std::string & fontName, int size, const Color & color)
{
	m_texture = new Texture();
	m_text = text;
	m_color = color;

	std::string filename = FileSystem::Instance()->GetPathname() + fontName;
	m_font = TTF_OpenFont(filename.c_str(), size);

	CreateTexture();

}


void Text::Draw(const Vector2D & position, const Vector2D & origin, const Vector2D & scale, float angle)
{
	m_texture->Draw(position, origin, scale, angle);
}

void Text::SetText(const std::string & text)
{
	if (m_text != text)
	{
		m_text = text;
		CreateTexture();
	}

}

void Text::SetText(const std::string & text, const Color & color)
{
	if (m_text != text || m_color != color)
	{
		m_text = text;
		m_color = color;
		CreateTexture();
	}

}

void Text::SetColor(const Color & color)
{
	if (m_color != color)
	{
		m_color = color;
	}
}

void Text::CreateTexture()
{
	assert(m_font);

	if (m_texture)
	{
		m_texture->Destroy();
	}

	SDL_Surface* surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);
	m_texture->CreateFromSurface(surface);
	SDL_FreeSurface(surface);

}
