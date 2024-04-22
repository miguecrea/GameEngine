#include "Scene.h"
#include "GameObject.h"
#include <algorithm>
#include"InputManager.h"


using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name)
	: m_name(name)

{



}

Scene::~Scene() = default;

class GameObjectAlreadyHasParentException {};

void Scene::Add(std::shared_ptr<GameObject> object)   //add any game obejct to a scene 
{
	if (object->GetParent())
	{
		throw GameObjectAlreadyHasParentException{};
	}

	if (std::find(m_pObjects.begin(), m_pObjects.end(), object) != m_pObjects.end())
	{
		throw GameObjectAlreadyHasParentException{};
	}

	m_pObjects.emplace_back(std::move(object));

	//Sort the components based on priority
	auto compareFunction = [&](const std::shared_ptr<GameObject>& pLhs, const std::shared_ptr<GameObject>& pRhs)
	{
		return pRhs->GetPriority() < pLhs->GetPriority();
	};

	std::sort(m_pObjects.begin(), m_pObjects.end(), compareFunction);
}

void dae::Scene::ForceRemoveAll()
{
	//m_pNewObjects.clear();
	m_pObjects.clear();         //removea ll game objects 
}

void dae::Scene::DestroyAll()
{

	for (const auto& pObject : m_pObjects)
	{
		pObject->Destroy();

	}



}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

void Scene::Update()
{
	for(auto& pObject : m_pObjects)
	{
		if (!pObject->IsDestroyed())
		{
			pObject->Update();
		}
	}

	//m_pObjects.erase(std::remove_if(m_pObjects.begin(), m_pObjects.end(), [&](std::shared_ptr<GameObject> pGameObject) {return pGameObject->IsDestroyed(); }), m_pObjects.end());
}

void dae::Scene::FixedUpdate()
{
	for (auto& pObject : m_pObjects)
	{
		pObject->FixedUpdate();
	}
}

std::string dae::Scene::GetName() const
{
	return m_name;
}

void dae::Scene::Load()
{

}

bool dae::Scene::NeedsCleanUp() const
{

	return false;
}

void Scene::Render() const
{
	for (const auto& pObject : m_pObjects)
	{
		pObject->Render();
	}
}

void dae::Scene::CleanUp()
{

	//m_NeedsCleanUp = false;

	//m_pObjects.erase(std::remove_if(m_pObjects.begin(), m_pObjects.end(),
	//	[&](std::shared_ptr<GameObject> pGameObject)
	//	{
	//		return pGameObject->IsDestroyed();
	//	}), m_pObjects.end());

	//if (m_ShouldLoad)
	//{
	//	SceneManager::GetInstance().SetCurrentScene(m_name);

	//	//m_pNewObjects.clear();
	//	m_pObjects.clear();
	//	//m_pGrid->Clear();

	//	m_LoadFunction();

	//	m_ShouldLoad = false;
	//}



}
