#include "SceneManager.h"
#include "Scene.h"
#include"Renderer.h"
#include<cassert>
#include"Map.h"
#include"PacmanManager.h"
#include"iostream"

void dae::SceneManager::Update(float deltaTime)   //ALL THIS VALUES ARE FROM THE GAME LOOP
{
	m_DeltaTime = deltaTime;

	/*for(auto& scene : m_pScenes)
	{
		scene->Update();
	}*/

	m_CurrentScene->Update();

	if (m_CurrentScene->GetName() != "MenuScene" && m_CurrentScene->GetName() != "ScoresScene")
	{
		Map::GetInstance().UpdateMap();
	}

//	const  auto& member = dae::PacmanManager::GetInstance().GetMode();
	//std::cout << int(member) << "\n";


	
}

void dae::SceneManager::FixedUpdate(float fixedTimeStep) //ALL THIS VALUES ARE FROM THE GAME LOOP
{
	m_FixedTimeStep = fixedTimeStep;

	m_CurrentScene->FixedUpdate();
}

void dae::SceneManager::Render() const//ALL THIS VALUES ARE FROM THE GAME LOOP
{

	m_CurrentScene->Render();

	if (m_CurrentScene->GetName() != "MenuScene" && m_CurrentScene->GetName() != "ScoresScene")
	{
	Map::GetInstance().DrawMap();

	}

	


	//redner Map 
	
}

void dae::SceneManager::CleanUp()
{

	for (auto& pScene : m_pScenes)
	{
		if (pScene->NeedsCleanUp())
		{
			pScene->CleanUp();                             //Clean Up
		}
	}
}

float dae::SceneManager::GetDeltaTime() const
{
	return m_DeltaTime;
}

float dae::SceneManager::GetFixedTimeStep() const
{
	return m_FixedTimeStep;
}

float dae::SceneManager::GetFramePercentage() const
{
	return m_FramePercentage;
}

dae::Scene * dae::SceneManager::GetCurrentScene() const
{
	return m_CurrentScene;
}

dae::Scene* dae::SceneManager::GetScene(const std::string& name) const
{
	auto pScene{ std::find_if(m_pScenes.begin(), m_pScenes.end(), [&](std::shared_ptr<Scene> pScene) { return pScene->GetName() == name; }) };

	assert(pScene != m_pScenes.end());

	return (*pScene).get();
}

void dae::SceneManager::SetCurrentScene(const std::string& name)
{
	auto pScene{ std::find_if(m_pScenes.begin(), m_pScenes.end(), [&](std::shared_ptr<Scene> pScene) { return pScene->GetName() == name; }) };

	if (pScene != m_pScenes.end())
	{
		m_CurrentScene = (*pScene).get();
	}
}

void dae::SceneManager::ForceRemoveAllObjects()
{

	for (auto& pScene : m_pScenes)
	{
		pScene->ForceRemoveAll();   //REMOVE ALLL OBJECTS 
	}

}



dae::Scene & dae::SceneManager::CreateScene(const std::string& name)
{
	const auto & scene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(scene);

	m_CurrentScene = scene.get();  //returns a pointer 

	return * scene;
}
