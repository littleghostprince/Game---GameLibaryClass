#include "spriteComponent.h"
#include "entity.h"
#include "renderer.h"
#include "texture.h"


void SpriteComponent::Create(const std::string & textureName, const Vector2D & orgin)
{
	if (textureName != "")
	{
		m_texture = new Texture();
		m_texture->Create(textureName);
	}
		m_orgin = orgin;
}

void SpriteComponent::Destroy()
{
	//
}

void SpriteComponent::Update()
{
	//
}

void SpriteComponent::Draw()
{
	if (m_texture)
	{
		if (m_visible)
		{
			Transform transform = m_owner->GetTransform();
			m_texture->Draw(transform.position, m_orgin, transform.scale, transform.rotation);
		}
	}
}
