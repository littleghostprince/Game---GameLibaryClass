#include "entity.h"
#include <algorithm>
#include <assert.h>
#include "renderComponent.h"
#include "collision.h"

void Entity::Destroy()
{
	for (Component * component : m_components)
	{
		component->Destroy();
		delete component;
	}

	m_components.clear();
}

void Entity::Update()
{
	for (Component * component : m_components)
	{
		component->Update();
	}
}

void Entity::Draw()
{
	IRenderComponent* renderComponent = GetComponent<IRenderComponent>();
	if (renderComponent) // if we put a render component then draw
	{
		renderComponent->Draw();
	}
}

void Entity::AddComponent(Component * component)
{
	assert(component);
	assert(std::find(m_components.begin(), m_components.end(), component) == m_components.end());

	m_components.push_back(component);
}

void Entity::RemoveComponent(Component * component)
{
	assert(std::find(m_components.begin(), m_components.end(), component) != m_components.end());

	auto iter = std::find(m_components.begin(), m_components.end(), component);
	(*iter)->Destroy();
	delete *iter;
	m_components.erase(iter);
}

void Entity::OnEvent(const Event & event)
{
}

bool Entity::Intersects(Entity * otherEntity)
{
	bool intersects = false;

	ICollisionComponent* collisionA = GetComponent<ICollisionComponent>();
	ICollisionComponent* collisionB = otherEntity->GetComponent<ICollisionComponent>();

	if (collisionA && collisionB)
	{
		intersects = collisionA->Intersects(collisionB);
	}
	return intersects;
}
