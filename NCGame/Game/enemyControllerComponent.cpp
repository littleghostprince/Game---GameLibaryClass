#include "enemyControllerComponent.h"
#include "kinematicComponent.h"
#include "enemy.h"
#include "vector2D.h"
#include "timer.h"
#include "missile.h"
#include "_math.h"

void EnemyControllerComponent::Create(float speed)
{
	m_speed = speed;
	m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);

}

void EnemyControllerComponent::Destroy()
{
}

void EnemyControllerComponent::Update()
{
	Vector2D force = Vector2D::up;
		
	Entity* player = m_owner->GetScene()->FindEntity("player");
	if (player)
	{
		float dx = player->GetTransform().position.x - m_owner->GetTransform().position.x;
		if (dx < -32.0f) force.x = -1.0f;
		if (dx > 32.0f) force.x = 1.0f;
	}

	force.y = 1.0;
	KinematicComponent * kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}
	
	float dt = Timer::Instance()->DeltaTime();
	m_timer = m_timer - dt;

	if (m_timer <= 0.0f)
	{
		m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);
		Missile* missile = new Missile(m_owner->GetScene());
		missile->Create(m_owner->GetTransform().position, Vector2D::up, 800.0f, "enemymissile", "missile02.png");
		m_owner->GetScene()->AddEntity(missile);
	}
}
