
#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "ControllerComponent.h"

class Texture;

class EnemyControllerComponent : public IControllerComponent
{
public:
	EnemyControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed);
	void Destroy();
	void Update();

protected:
	float m_speed = 0.0f;
	float m_timer = 0.0f;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 3.0f;

};


