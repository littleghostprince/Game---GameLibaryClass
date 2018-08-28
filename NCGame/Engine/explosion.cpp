#include "explosion.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "audioSystem.h"

Explosion::~Explosion()
{
}

void Explosion::Create(const Vector2D & position,eType type)
{
	if (type == Explosion::ENEMY)
	{
		m_transform.position = position;
		m_transform.scale = Vector2D(2.0f, 2.0f);
		SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
		spriteComponent->Create("", Vector2D(0.5f, 0.5f));
		AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
		std::vector<std::string> textureNames = { "enemy-explosion01.png","enemy-explosion02.png","enemy-explosion03.png","enemy-explosion04.png","enemy-explosion05.png" };
		animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME_DESTROY);

		AudioSystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
		AudioSystem::Instance()->Playsound("explosion");
	}
	if (type == Explosion::PLAYER)
	{
		m_transform.position = position;
		m_transform.scale = Vector2D(2.0f, 2.0f);
		SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
		spriteComponent->Create("", Vector2D(0.5f, 0.5f));
		AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
		std::vector<std::string> textureNames = { "ship-explosion01.png","ship-explosion02.png","ship-explosion03.png","ship-explosion04.png"};
		animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME_DESTROY);

		AudioSystem::Instance()->AddSound("Ship-explosion", "ship-explosion.wav");
		AudioSystem::Instance()->Playsound("Ship-explosion");
	}

}

void Explosion::Update()
{
	Entity::Update();
}
