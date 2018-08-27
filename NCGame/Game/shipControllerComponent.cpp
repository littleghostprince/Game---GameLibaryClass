#include "shipControllerComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "transformComponent.h"
#include "timer.h"
#include "kinematicComponent.h"
#include "missile.h"
#include "audioSystem.h"

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;

	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);

	AudioSystem::Instance()->AddSound("fire", "laser.wav");
}

void ShipControllerComponent::Destroy()
{
}

void ShipControllerComponent::Update()
{
	Vector2D force = Vector2D::zero;

	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD))
	{
		force.x = -1.0;
		// force x <- -1.0
	}

	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
		force.x = 1.0;
		// force x -> 1.0
	}

	if ((InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED))
	{
		std::vector<Entity*> missiles = m_owner->GetScene()->GetEntitiesWithTag("playermissile");

		if (missiles.size() < 2) //makes only 2 at a time 
		{
			//fire missile / create missile 
			Missile* missile = new Missile(m_owner->GetScene());
			missile->Create(m_owner->GetTransform().position, Vector2D::down, 800.0f,"playermissile","missile01.png");
			m_owner->GetScene()->AddEntity(missile);

			AudioSystem::Instance()->Playsound("fire");
		}
	}

	// get transform component
	KinematicComponent * kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::FORCE);
	}
	// tranform position = transform position + force * speed * dt
}