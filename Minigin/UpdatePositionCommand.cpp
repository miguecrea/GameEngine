#include "UpdatePositionCommand.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Renderer.h"
#include <iostream>

using namespace dae;

UpdatePositionCommand::UpdatePositionCommand(GameObject* pGameObject, const glm::vec3& direction)
	: Command{}, m_pGameObject(pGameObject),
	m_OldPosition(pGameObject->GetLocalPosition()),
	m_Direction(direction),
	m_pSceneManager(&SceneManager::GetInstance())    //pointer needs addresss 

{

}

Point2f dae::UpdatePositionCommand::GridToWorld(int row, int column)
{
	return Point2f(8 * row, 8 * column);
}

void UpdatePositionCommand::Execute()
{
	if (!m_pGameObject) return;

	m_OldPosition = m_pGameObject->GetLocalPosition();


	// Set the new position

	float gridCellWidth = 8.f; // Assuming each grid cell is 16 units wide
	float gridCellHeight = 8.f;

	
	int column = static_cast<int>((m_OldPosition.x + 3) / gridCellWidth);  //number columns 
	int row = static_cast<int>((m_OldPosition.y + 3) / gridCellHeight);   //number of rows     

	glm::vec3 newPosition = m_OldPosition + m_Direction * m_pSceneManager->GetDeltaTime();
	if (m_Direction.x > 0) column++;
	if (m_Direction.x < 0) column--;
	if (m_Direction.y > 0) row++;
	if (m_Direction.y < 0) row--;



	std::cout << column << ", " << row << ": " << Renderer::Map[row][column] << "\n";

	if (Renderer::Map[row][column] != 1)
	{
		m_pGameObject->SetPosition(newPosition.x, newPosition.y);
	}
	Renderer::GetInstance().FillSquare((column)*gridCellWidth, (row)*gridCellHeight, gridCellWidth, { 255,0,255,255 });





}

void UpdatePositionCommand::Undo()
{
	if (!m_pGameObject) return;

	m_pGameObject->SetPosition(m_OldPosition.x, m_OldPosition.y);
}


