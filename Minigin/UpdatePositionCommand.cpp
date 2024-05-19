#include "UpdatePositionCommand.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Renderer.h"
#include <iostream>
#include"Map.h"
#include"staticHeader.h"

using namespace dae;

UpdatePositionCommand::UpdatePositionCommand(GameObject* pGameObject, const glm::vec3& direction,int WhoIsTurning)   //pasar 
	: Command{}, m_pGameObject(pGameObject),   // 
	m_OldPosition(pGameObject->GetLocalPosition()),
	m_Direction(direction),
	m_pSceneManager(&SceneManager::GetInstance()),    //pointer needs addresss 
	m_currentPlayer{WhoIsTurning}

{

}

Point2f dae::UpdatePositionCommand::GridToWorld(int row, int column)
{
	return Point2f(8 * row, 8 * column);
}

void UpdatePositionCommand::Execute()
{
	if (!m_pGameObject || s_PauseGame==1) return;
	
	m_OldPosition = m_pGameObject->GetLocalPosition();


	// Set the new position

	float gridCellWidth = 8.f; // Assuming each grid cell is 16 units wide
	float gridCellHeight = 8.f;

	
	int column = static_cast<int>((m_OldPosition.x + 3) / gridCellWidth);  //number columns   //(ancho textura /2) -1
	int row = static_cast<int>((m_OldPosition.y + 3) / gridCellHeight);   //number of rows     

	glm::vec3 newPosition = m_OldPosition + m_Direction * m_pSceneManager->GetDeltaTime();
	if (m_Direction.x > 0) column++;
	if (m_Direction.x < 0) column--;
	if (m_Direction.y > 0) row++;
	if (m_Direction.y < 0) row--;

	if (m_Direction.x != 0) 
	{
		newPosition.y = row * gridCellHeight;
	}
	
	if (m_Direction.y != 0) 
	{
		newPosition.x = column * gridCellWidth;
	}



	if (Map::GetInstance().MapArray[row][column] != 1)
	{
		m_pGameObject->SetPosition(newPosition.x, newPosition.y);
	}
	




	if (m_currentPlayer == 0)
	{
	m_pacmanState = int(m_Direction.z);

	}
	else
	{
		m_MrsPacmanState = int(m_Direction.z);
	}





}

void UpdatePositionCommand::Undo()
{
	if (!m_pGameObject) return;

	m_pGameObject->SetPosition(m_OldPosition.x, m_OldPosition.y);
}


