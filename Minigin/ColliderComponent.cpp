#include "ColliderComponent.h"
#include"GameObject.h"
#include"Renderer.h"
#include<iostream>

dae::ColliderComponent::ColliderComponent(std::shared_ptr<GameObject> owner, std::vector<Object> & collideswidth):  //PUIT objects array in the constructor
	m_Owner{owner},// vector of f rects 
	m_objectsVector{collideswidth}

{
	m_Rect.w = 30;
	m_Rect.h = 30;


	////  iNITIALIZE objects array in here 

}

dae::ColliderComponent::~ColliderComponent()
{
}


void dae::ColliderComponent::Render()
{

	Renderer::GetInstance().FillSquare(float(m_Rect.x),float(m_Rect.y),float(m_Rect.w),float(m_Rect.h), Renderer::GetInstance().m_White);

}

void dae::ColliderComponent::Update()
{


	m_Rect.x = int(m_Owner->GetWorldPosition().x*2);
	m_Rect.y = int(m_Owner->GetWorldPosition().y*2);





	std::cout << m_objectsVector[0].shape.x << m_objectsVector[0].shape.y << "\n";
	


	// if (objects can collide )

	// cjeck the variable when colliding 

	if (CheckCollision(m_Rect, m_objectsVector))
	{
	


		for (size_t i = 0; i < m_objectsVector.size(); i++)
		{
			if (m_objectsVector[i].m_type == dae::TypeOfObject::pellet || m_objectsVector[i].m_type == dae::TypeOfObject::powerUp)

			{
				std::cout << "collides\n";
				m_objectsVector[0].m_SetColorBlack = true ;

				//std::c

			}
		}




	// checkType() ;  //return type     



		//ghost
		//  dye 
		// play dead animation 
		//-- live 

		// power up

		//make ghots blue and etc 




		//




	}

	else
	{
	//	std::cout << "no\n";

	}


	// if rect collides vector of f recfts // get type 


	//type pellet 

	//power up 


	//cherry 


}

bool dae::ColliderComponent::CheckCollision(SDL_Rect & self, std::vector<Object> & objects)

{


	for (int index = 0; index < objects.size(); index++)
	{
		// If one rectangle is on left side of other
		if (self.x + self.w < objects[index].shape.x || objects[index].shape.x + objects[index].shape.w < self.x)
			continue;

		// If one rectangle is on right side of other
		if (self.x > objects[index].shape.x + objects[index].shape.w || objects[index].shape.x > self.x + self.w)
			continue;

		// If one rectangle is above other
		if (self.y + self.h < objects[index].shape.y || objects[index].shape.y + objects[index].shape.h < self.y)
			continue;

		// If one rectangle is below other
		if (self.y > objects[index].shape.y + objects[index].shape.h || objects[index].shape.y > self.y + self.h)
			continue;

		// If none of the above conditions are met, rectangles overlap

		//objects[index].m_visibility = Visibility::Invisible;


		return true;

	}

	// No collision detected with any object
	return false;
	
	
}
