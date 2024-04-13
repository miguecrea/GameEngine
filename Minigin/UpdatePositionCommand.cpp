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
	m_pSceneManager(&SceneManager::GetInstance())     //pointer needs addresss 
	//  function{function}

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

	// takes x and y posiiton and returns de row and columns 
	//int column = static_cast<int>(newPosition.x / gridCellWidth);  //number columns 
	//int  row = static_cast<int>(newPosition.y / gridCellHeight);   //number of rows     //numero de la grid en terminos de la grid [3][2]
	int column = static_cast<int>((m_OldPosition.x + 3) / gridCellWidth);  //number columns 
	int row = static_cast<int>((m_OldPosition.y + 3) / gridCellHeight);   //number of rows     //numero de la grid en terminos de la grid [3][2]

	glm::vec3 newPosition = m_OldPosition + m_Direction * m_pSceneManager->GetDeltaTime();
	if (m_Direction.x > 0) column++;
	if (m_Direction.x < 0) column--;
	if (m_Direction.y > 0) row++;
	if (m_Direction.y < 0) row--;

	/*auto tileRect = SDL_Rect{ row * 8, column * 8, 8, 8 };
	auto playerRect = SDL_Rect{ int(newPosition.x), int(newPosition.y), 7, 7 };*/

	std::cout << column << ", " << row << ": " << Renderer::Map[row][column] << "\n";
	/*if (!SDL_HasIntersection(&tileRect, &playerRect))
	{
		m_pGameObject->SetPosition(newPosition.x, newPosition.y);
	}*/
	if (Renderer::Map[row][column] != 1)
	{
		m_pGameObject->SetPosition(newPosition.x, newPosition.y);
	}
	Renderer::GetInstance().FillSquare((column)*gridCellWidth, (row)*gridCellHeight, gridCellWidth, { 255,0,255,255 });

	// row and grid 

   //Point2f ActualPosition = GridToWorld(row, column);

	//m_pGameObject->SetPosition(float(ActualPosition.x),float( ActualPosition.y));






   //if(Renderer::GetInstance().)
   // function();
}

void UpdatePositionCommand::Undo()
{
	if (!m_pGameObject) return;

	m_pGameObject->SetPosition(m_OldPosition.x, m_OldPosition.y);
}


