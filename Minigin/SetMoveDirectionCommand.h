#pragma once
#include "GameObject.h"
#include "SceneManager.h"
#include"Command.h"


namespace dae
{

	class SetMoveDirectionCommand : public Command
	{
		//public:
		//    SetPositionCommand(GameObject* pGameObject, const glm::vec3& direction);
		//
		//    void Execute() override;
		//    void Undo() override;
		//
		//private:
		//    GameObject* m_pGameObject;
		//    glm::vec3 m_OldPosition;
		//    glm::vec3 m_Direction;
	};

}