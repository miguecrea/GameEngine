#include "ColliderComponent.h"
#include"GameObject.h"
#include"Renderer.h"
#include<iostream>
#include"staticHeader.h"

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




	//ghost are constantly moving so the position of them can be set in the constructor we need to get them real time or evey frame 

	//m_objectsVector.push_back(ghots in the constructor and then updstes well dunno yet but I will figure it out 



	for (size_t i = 0; i < m_objectsVector.size(); i++)
	{

		// if can colliison state == collision then check collision 
		if (m_objectsVector[i].m_collisionPreset == dae::Collision::CanCollide)
		{

			if (CheckCollision(m_Rect, m_objectsVector[i]))
			{

				/// Ownwe->OnCollision(// otro game object ); //poner logica aqui 



				switch (m_objectsVector[i].m_type)
				{
				case dae::TypeOfObject::pellet:


					std::cout << "Is Collidiing\n" << i << "\n";
					m_objectsVector[i].color.a = 0;
					m_objectsVector[i].m_collisionPreset = dae::Collision::NoCollision;

	

	

				//add to score 


					break;

				case dae::TypeOfObject::powerUp:

					m_objectsVector[i].m_collisionPreset = dae::Collision::NoCollision;
					m_objectsVector[i].color.a = 0;
					m_GhostState =int(dae::GhostState::Blue);   
					
                   //bug all objects are of same type 
					//set ghots blue //for 2 second 
					// put  a variable can eat ghost with timer etc 

					//ghots have to run away from me 

					std::cout << "collides\n";

					break;

				case::dae::TypeOfObject::Enemy:

					if (m_GhostState == int(dae::GhostState::Normal))
					{
						//DYE and if no more lives 
						// reset 
						// if has lives -- live 
						//play dead animation


					}

					else
					{
						//add to score 
						//play eat sounds 

					}


					break;

				case::dae::TypeOfObject::cherry:


					//spawn ramdonly at some point on the map ? 

	                //at any point of the match 

					break;




				default:
					break;

				}
			}

		}


	}


	//if (CheckCollision(m_Rect, m_objectsVector))
	//{

	//	//if check collision with any of them 
	//	//then I am setting all of them //set that individual index 
	//


	//	for (int i = 0; i < m_objectsVector.size(); i++)
	//	{
	//		switch (m_objectsVector[i].m_type)
	//		{
	//		case dae::TypeOfObject::pellet:

	//			m_objectsVector[i].Update();

	//			//set pellets blakc and the collision to false 

	//			//add to score 
	//			m_GhostState = 1;    //bug all objects are of same type 

	//			break;

	//		case dae::TypeOfObject::powerUp:

	//			//set ghots blue //for 2 second 
	//			// put  a variable can eat ghost with timer etc 

	//			std::cout << "collides\n";

	//			break;

	//		case::dae::TypeOfObject::Enemy:

	//			// if the m_gghots state allows it

	//			//ghost
	////  dye 
	//// play dead animation 
	////-- live 


	//			break;

	//		default:
	//			break;

	//		}
	//	



	//		//way to win the game where you have to eat all the pellets
	//		
	//	}




	// checkType() ;  //return type     



		//ghost
		//  dye 
		// play dead animation 
		//-- live 

		// power up

		//make ghots blue and etc 




		//




	



	// if rect collides vector of f recfts // get type 


	//type pellet 

	//power up 


	//cherry 


}



bool dae::ColliderComponent::CheckCollision(SDL_Rect& self, Object& objects)
{
	// If one rectangle is on left side of other
	if (self.x + self.w < objects.shape.x || objects.shape.x + objects.shape.w < self.x)
		return false;

	// If one rectangle is on right side of other
	if (self.x > objects.shape.x + objects.shape.w || objects.shape.x > self.x + self.w)
		return false;

	// If one rectangle is above other
	if (self.y + self.h < objects.shape.y || objects.shape.y + objects.shape.h < self.y)
		return false;

	// If one rectangle is below other
	if (self.y > objects.shape.y + objects.shape.h || objects.shape.y > self.y + self.h)
		return false;

	return true;
}
