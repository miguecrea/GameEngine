#include "NextSceneCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PacmanManager.h"
#include"staticHeader.h"
#include"SoundSystem.h"
#include"Audio.h"





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


	 dae::SoundSystem& audio{ dae::Audio::Get() };
	 audio.Play(s_GameSoundId,0.5f,1);
	
	 



}

void dae::NextSceneCommand::Undo()
{
}
