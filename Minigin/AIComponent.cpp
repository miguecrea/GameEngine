#include "AIComponent.h"
#include "GameObject.h"
#include"SceneManager.h"
#include "Renderer.h"


dae::AIComponent::AIComponent(std::shared_ptr<GameObject> SelfGameObject, std::shared_ptr<GameObject> pTargetGameObejct):
	m_Self{SelfGameObject}, 
	m_Target{pTargetGameObejct},
	m_OldPosition(SelfGameObject->GetLocalPosition()),
	m_pSceneManager(&SceneManager::GetInstance()),//pointer needs addresss 
	m_TargetPos{pTargetGameObejct->GetLocalPosition()}


{
}//puede tomar un game object 


void dae::AIComponent::Render()
{
}

void dae::AIComponent::Update()
{



	//m_OldPosition = m_Self->GetLocalPosition();
	//glm::vec3 newPosition = m_OldPosition + glm::vec3{10,0,0} * m_pSceneManager->GetDeltaTime();
	//m_Self->SetPosition(newPosition.x, newPosition.y);



    /////////////////////////////////////////////////////////////////////////////////////////////////


    //const float targetX = 20.0f;
    //const float targetY = 200.0f;

    //m_OldPosition = m_Self->GetLocalPosition();

    //// Calculate direction vector towards the target position (200, 200)
    //glm::vec3 targetPosition(targetX, targetY, 0.0f); // Assuming z-coordinate is 0
    //glm::vec3 direction = glm::normalize(targetPosition - m_OldPosition);

    //// Define movement speed
    //float moveSpeed = 10.f; // Adjust as needed

    //// Calculate movement for this frame
    //glm::vec3 movement = direction * moveSpeed * m_pSceneManager->GetDeltaTime();

    //// Calculate new position by adding movement to the old position
    //glm::vec3 newPosition = m_OldPosition + movement;

    //// Check if the character is close enough to the target position
    //float distanceToTarget = glm::distance(newPosition, targetPosition);
    //if (distanceToTarget <= moveSpeed * m_pSceneManager->GetDeltaTime()) {
    //    // If close enough, directly set the position to the target position
    //    m_Self->SetPosition(targetX, targetY);
    //}
    //else {
    //    // Otherwise, set the position to the new calculated position
    //    m_Self->SetPosition(newPosition.x, newPosition.y);
    //}
   
    //


    /////////////////////

    m_OldPosition = m_Self->GetLocalPosition();

    // Assuming playerPosition represents the position of the player object
    glm::vec3 playerPosition = m_Target->GetLocalPosition(); // Assuming m_Player is a pointer to the player object

    // Calculate direction vector towards the player's position
    glm::vec3 direction = glm::normalize(playerPosition - m_OldPosition);

    // Define movement speed
    float moveSpeed = 10.0f; // Adjust as needed

    // Calculate movement for this frame
    glm::vec3 movement = direction * moveSpeed * m_pSceneManager->GetDeltaTime();

    // Calculate new position by adding movement to the old position
    glm::vec3 newPosition = m_OldPosition + movement;

    // Set the position to the new calculated position
   m_Self->SetPosition(newPosition.x, newPosition.y);






























    


}
