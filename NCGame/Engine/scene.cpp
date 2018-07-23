#include "scene.h"
#include "entity.h"
#include <assert.h>
#include "id.h"

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
}

void Scene::Draw()
{
	for (Entity* entity : m_entities)
	{
		entity->Draw();
	}
}

void Scene::AddEntity(Entity* entity)
{
	assert(std::find(m_entities.begin(),m_entities.end(),entity) == m_entities.end());
	assert(entity != nullptr);

	m_entities.push_back(entity);
}

void Scene::RemoveEntity(Entity* entity)
{
	assert(std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end());
	assert(entity != nullptr);

	auto iter = std::find(m_entities.begin(), m_entities.end(), entity);
	if (iter != m_entities.end())
	{
		m_entities.erase(iter);
	}
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
