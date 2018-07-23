#pragma once
#pragma once

#include "component.h"

class ENGINE_API IControllerComponent : public Component
{
public:
	IControllerComponent(Entity* owner) : Component(owner) {}
	virtual void Update();
	virtual void Destroy();
};