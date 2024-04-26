#include "NextSceneCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PacmanManager.h"





dae::NextSceneCommand::NextSceneCommand(const std::string & nameScene, GameMode gamemode):
	nameOfScene{nameScene},
	m_gameMode{gamemode}
{
}

void dae::NextSceneCommand::Execute()
{

	// make sure I use a boolean to restrict use of this 
	 SceneManager::GetInstance().SetCurrentScene(nameOfScene);

	 PacmanManager::GetInstance().SetGameMode(m_gameMode);

}

void dae::NextSceneCommand::Undo()
{
}
