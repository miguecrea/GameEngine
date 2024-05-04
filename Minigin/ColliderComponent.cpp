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

					m_StartTimer = true;
					m_GhostState =int(dae::GhostState::Blue);  
					m_objectsVector[i].m_collisionPreset = dae::Collision::NoCollision;
					m_objectsVector[i].color.a = 0;


					//add to score //and display +2-00 srpite on screen 

					//ghots have to run away from me 


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


	if (m_StartTimer)
	{

		m_totalTimeElapsed += SceneManager::GetInstance().GetDeltaTime();



		if (m_totalTimeElapsed >= 3.f)
		{
			m_ToogleSpriteTimer += SceneManager::GetInstance().GetDeltaTime();
			if (m_ToogleSpriteTimer >= 0.45f)
			{
				m_ToogleSpriteTimer = 0;
				ToogleSprite();

			}

		}
		if (m_totalTimeElapsed >= 7.f)
		{
			m_StartTimer = false;
			m_ToogleSpriteTimer = 0;

			m_GhostState = int(dae::GhostState::Normal);
			m_totalTimeElapsed = 0;

			//set the bool variable to = false 

		}

	}



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

void dae::ColliderComponent::ToogleSprite()
{
	if (m_GhostState == int(dae::GhostState::Blue))
	{
		m_GhostState = int(dae::GhostState::White);
	}
	else
	{
		m_GhostState = int(dae::GhostState::Blue);
	}


}
