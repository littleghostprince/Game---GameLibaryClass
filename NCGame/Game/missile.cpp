#include "missile.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "shipControllerComponent.h"
#include "timer.h"
#include "aabbComponent.h"

void Missile::Create(const Vector2D & position, const Vector2D& direction, float speed, const std::string Tag, const std::string filename)
{
	m_lifetime = 0.9f; //how long the missles are alive. 2 sec
	SetTag(Tag);

	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.9f);
	kinematic->ApplyForce(direction * speed, KinematicComponent::VELOCITY);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create(filename, Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();

}

void Missile::Update()
{
	Entity::Update();
	m_lifetime = m_lifetime - Timer::Instance()->DeltaTime();
	if (m_lifetime <= 0.0f)
	{
		SetState(Entity::DESTROY);
	}
}

void Missile::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemy" && m_tag == "playermissile")
		{
			SetState(Entity::DESTROY);
		}
	}
}
