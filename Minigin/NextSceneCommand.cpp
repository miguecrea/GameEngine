#include "NextSceneCommand.h"

#include "NextSceneCommand.h"
#include "SceneManager.h"
#include "Scene.h"
//#include "PacmanManager.h"

dae::NextSceneCommand::NextSceneCommand()
{
}

void dae::NextSceneCommand::Execute()
{
	//auto pCurrent{ SceneManager::GetInstance().GetCurrentScene() };

	//if (pCurrent->GetName() == "GameScene")
	//{
	//	PacmanManager::GetInstance().NextLevel();
	//}
	//else if (pCurrent->GetName() == "ScoreScene")
	//{
	//	SceneManager::GetInstance().GetScene("MenuScene")->Load();
	//}
}
