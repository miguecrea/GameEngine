#include "ColliderComponent.h"
#include"GameObject.h"

dae::ColliderComponent::ColliderComponent()    //make it take a render 
{

	auto  df = GetOwner();

	df->GetLocalPosition();



}

dae::ColliderComponent::~ColliderComponent()
{
}


void dae::ColliderComponent::Render()
{

	

}

void dae::ColliderComponent::Update()
{

	//
	//if (GetOwner()->GetWorldPosition().x >= 40)

	//{
	//	//GetOwner()->SetPosition(40, 0);

	//}









	// checks t with every psoition of the vector 
	//
	//


	



	//if (m_Rect.x >= 100)
	//{
	//	m_Rect.x = 100;
	//}


	/*if (m_Rect.x + m_Rect.w >= 66)
	{
		m_Rect.x + m_Rect.w = 60;
	}

*/





}
