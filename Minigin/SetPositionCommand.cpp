#include "SetPositionCommand.h"
#include "GameObject.h"
#include "SceneManager.h"


using namespace dae;

SetPositionCommand::SetPositionCommand(GameObject* pGameObject, const glm::vec3& direction)
    : Command{}, m_pGameObject(pGameObject), m_OldPosition(pGameObject->GetLocalPosition()), m_Direction(direction) {};

void SetPositionCommand::Execute()
{
    if (!m_pGameObject) return;

    m_OldPosition = m_pGameObject->GetLocalPosition();

    glm::vec3 newPosition = m_OldPosition + m_Direction;   //DELTA TIME IN HERE I believe  
    m_pGameObject->SetPosition(newPosition.x, newPosition.y);  //dirty flag 

    //function()

    //if (state != righh)
    //{
    
    //state is equal to right 
    //}
    

    //call function here  remmber not to call it evry frame otherwise bugssss


}

void SetPositionCommand::Undo()
{
    if (!m_pGameObject) return;

    m_pGameObject->SetPosition(m_OldPosition.x, m_OldPosition.y);
}


