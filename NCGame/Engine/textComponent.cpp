#include "textComponent.h"
#include "text.h"
#include "transform.h"
#include "entity.h"

void TextComponent::Create(const std::string & text, const std::string & fontName, int fontsize, const Color & color, const Vector2D & orgin)
{
	m_text = new Text();
	m_text->Create(text, fontName, fontsize, color);
	m_orgin = orgin;
}

void TextComponent::Destroy()
{
}

void TextComponent::Update()
{
}

void TextComponent::Draw()
{
	if (m_visible)
	{
		Transform transform = m_owner->GetTransform();
		m_text->Draw(transform.position, m_orgin, transform.scale, transform.rotation);
	}
}

void TextComponent::SetText(const std::string & text)
{
	m_text->SetText(text);
}

void TextComponent::SetColor(const Color & color)
{
	m_text->SetColor(color);
}
