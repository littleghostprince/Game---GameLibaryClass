#pragma once
#include "controllerComponent.h"
#include "vector2D.h"
#include "Engine.h"

class ENGINE_API TransformControllerComponent : public IControllerComponent
{
public:
	TransformControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(const Vector2D& position, float rotation, float speed, float rotateRate);
	void Destroy();
	void Update();

protected:
	float m_speed = 0.0f;
	float m_rotation = 0.0f;
	float m_rotationRate= 0.0f;
	Vector2D m_position;
};