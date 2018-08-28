#pragma once
#include "controllerComponent.h"
#include "waypoints.h"
#include <vector>
#include "vector2D.h"
#include "Engine.h"

class ENGINE_API WaypointControllerComponent : public IControllerComponent
{
public:
	WaypointControllerComponent(Entity* owner) : IControllerComponent(owner) {};

	void Create(const std::vector<Vector2D>& points, float speed, float turnRate, bool setPositionAtStart = false);
	void Destroy();
	void Update();

	void SetNextWayPoint();

	bool IsComplete() { return m_isComplete; }

protected:
	bool m_isComplete = false;
	float m_speed = 0.0f;
	float m_turnRate = 0.0f;

	float m_timer = 0.0f;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 3.0f;

	Waypoint * m_waypoint = nullptr;
	size_t m_waypointIndex = 0;
	std::vector<Waypoint*> m_waypoints;
};


