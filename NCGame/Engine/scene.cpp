#include "scene.h"
#include "entity.h"
#include <assert.h>
#include "id.h"
#include "collision.h"
#include "eventManager.h"
#include "renderComponent.h"
#include <algorithm>

Scene::Scene()
{
}


Scene::~Scene()
{
}

bool Scene::Initialize()
{
	return false;
}

void Scene::Shutdown()
{
	for (Entity* entity : m_entities)
	{
		delete entity;
	}
	m_entities.clear();
}

void Scene::Update()
{
	for (Entity* entity : m_entities)
	{
		entity->Update();
	}

	//update collision 
	std::vector<ICollisionComponent*> collisionComponents;
	for (Entity* entity : m_entities)
	{
		ICollisionComponent* collisionComponent = entity->GetComponent<ICollisionComponent>();
		if (collisionComponent)
		{
			collisionComponents.push_back(collisionComponent);
		}
	}

	//compare  collision

	for (size_t i = 0; i < collisionComponents.size(); i++)
	{
		for (size_t j = i+1; j < collisionComponents.size(); j++)
		{
			if (collisionComponents[i]->GetOwner()->GetState() != Entity::DESTROY &&
				collisionComponents[j]->GetOwner()->GetState() != Entity::DESTROY)
			{
				if (collisionComponents[i]->Intersects(collisionComponents[j]))
				{
					Event event;
					event.eventID = "collision";
					event.receiver = collisionComponents[i]->GetOwner();
					event.sender = collisionComponents[j]->GetOwner();
					EventManager::Instance()->SentMessage(event);

					event.receiver = collisionComponents[j]->GetOwner();
					event.sender = collisionComponents[i]->GetOwner();
					EventManager::Instance()->SentMessage(event);
				}
			}
		}
	}

	std::list<Entity*>::iterator iter = m_entities.begin();
	while (iter != m_entities.end())
	{
		if ((*iter)->GetState() == Entity::DESTROY)
		{
			iter = RemoveEntity(*iter);
		}
		else
		{
			iter++;
		}
	}

}

void Scene::Draw()
{
	std::vector<IRenderComponent*> renderComponents;
	for (Entity* entity : m_entities)
	{
		IRenderComponent* renderComponent = entity->GetComponent<IRenderComponent>();
		if (renderComponent)
		{
			renderComponents.push_back(renderComponent);
		}
	}

	std::sort(renderComponents.begin(), renderComponents.end(),IRenderComponent::CompareDepth);

	for (IRenderComponent* _renderComponent : renderComponents)
	{
		if (_renderComponent->GetVisible())
		{
		_renderComponent->Draw();
		}
	}
}

void Scene::AddEntity(Entity* entity)
{
	assert(std::find(m_entities.begin(),m_entities.end(),entity) == m_entities.end());
	assert(entity != nullptr);

	m_entities.push_back(entity);
}

std::list<Entity*>::iterator Scene::RemoveEntity(Entity* entity, bool destroy)
{
	assert(std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end());
	assert(entity != nullptr);

	auto iter = std::find(m_entities.begin(), m_entities.end(), entity);
	if (iter != m_entities.end())
	{
		if (destroy)
		{
			(*iter)->Destroy();
			delete *iter;
		}
		iter = m_entities.erase(iter);
	}
	return iter;
}


Entity * Scene::FindEntity(const ID & id)
{
	Entity* entity = nullptr;

	for (Entity* _entity : m_entities)
	{
		if (*_entity == id)
		{
			entity = _entity;
			break;
		}
	}

	return entity;
}

std::vector<Entity*> Scene::GetEntitiesWithTag(const ID & tag)
{
	std::vector<Entity*> entities; 
	
	for (Entity* entity : m_entities)
	{
		if (entity->GetTag() == tag)
		{
			entities.push_back(entity);
		}
	}

	return entities;
}
