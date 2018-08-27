#pragma once
#include "engine.h"
#include <map>
#include <string>

class Scene;
class IState;
class Entity;

class ENGINE_API StateMachine
{
public:
	StateMachine(Scene * scene, Entity* owner = nullptr) : m_scene(scene), m_owner(owner){}
	~StateMachine(){}

	void Update();

	void AddState(const std::string& statename, IState* state);
	void SetState(const std::string& statename);

	Scene* GetScene() { return m_scene; }
	Entity* GetEntity() { return m_owner; }
	
	template<typename T>
	T* GetEntity()
	{
		return dynamic_cast<T*>(m_owner);
	}

protected:
	Scene * m_scene = nullptr;
	IState * m_state = nullptr;
	Entity* m_owner = nullptr;
	std::map<std::string, IState*> m_states;
};