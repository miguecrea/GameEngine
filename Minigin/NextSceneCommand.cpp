#include "NextSceneCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PacmanManager.h"
#include"staticHeader.h"
#include"SoundSystem.h"
#include"Audio.h"
#include"InputManager.h"


#include"GameObject.h"
#include"UpdatePositionCommand.h"
#include <memory>
#include"AddInput.h"




dae::NextSceneCommand::NextSceneCommand(const std::string & nameScene, GameMode gamemode):
	nameOfScene{nameScene},
	m_gameMode{gamemode}
{
}

void dae::NextSceneCommand::Execute()
{

	auto & input = InputManager::GetInstance();
	 SceneManager::GetInstance().SetCurrentScene(nameOfScene);
	const  auto scene = SceneManager::GetInstance().GetScene(nameOfScene);
	
	float  setSpeed = 30.f;
	glm::vec3 direction{};
	
	
	if (nameOfScene == "ScoresScene") return;
	std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::UpdatePositionCommand>(scene->m_player.get(), direction,int(CurrentPlayer::Pacman)) };

		AddKeyBoard(input, scene->m_player, pMoveCommand, setSpeed);
		AddController1(input, scene->m_player, pMoveCommand, setSpeed);
		if (nameOfScene == "CoOpScene")
		{
	   std::unique_ptr<dae::Command> pMoveCommandplayer2{ std::make_unique<dae::UpdatePositionCommand>(scene->m_player2.get(), direction,int(CurrentPlayer::MrsPacman)) };
		     
			AddKeyBoard2(input, scene->m_player2, pMoveCommandplayer2, setSpeed);
		    AddController2(input, scene->m_player2, pMoveCommandplayer2, setSpeed);
	
		}
		if (nameOfScene == "VersusMode")
		{
	   std::unique_ptr<dae::Command> pMoveCommandplayer2{ std::make_unique<dae::UpdatePositionCommand>(scene->m_enemy.get(), direction,int(CurrentPlayer::MrsPacman)) };
		     
			AddKeyBoard2(input, scene->m_enemy, pMoveCommandplayer2, setSpeed);
		    AddController2(input, scene->m_enemy, pMoveCommandplayer2, setSpeed);
		}

	 PacmanManager::GetInstance().SetGameMode(m_gameMode);
	 dae::SoundSystem& audio{ dae::Audio::Get() };
	 audio.Play(s_GameSoundId,0.5f,1);






	 


}

void dae::NextSceneCommand::Undo()
{
}
