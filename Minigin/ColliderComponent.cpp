#include "ColliderComponent.h"
#include"GameObject.h"
#include"Renderer.h"
#include<iostream>
#include"staticHeader.h"
#include"Audio.h"
#include"SoundSystem.h"
#include"AIComponent.h"
#include"Map.h"
dae::ColliderComponent::ColliderComponent(std::shared_ptr<GameObject> owner, std::vector<Object>& collideswidth, std::vector<std::shared_ptr<GameObject>>& ghosts) :  //PUIT objects array in the constructor
	m_Owner{ owner },// vector of f rects 
	m_Enemies{ ghosts },
	m_objectsVector{ collideswidth }

{
	m_Rect.w = 30;   //changed collider //was in 30
	m_Rect.h = 30;




}

dae::ColliderComponent::~ColliderComponent()
{
	
}

void dae::ColliderComponent::Render()
{

	Renderer::GetInstance().FillSquare(float(m_Rect.x),float(m_Rect.y),float(m_Rect.w),float(m_Rect.h), Renderer::GetInstance().m_White);


	Renderer::GetInstance().FillSquare(float(x),float(y), float(m_Rect.w), float(m_Rect.h), Renderer::GetInstance().m_White);

}

void dae::ColliderComponent::Update()
{

	float scale{ 2 };
	for (int index = 0; index < m_Enemies.size(); index++)
	{

		enemiesArrayX[index] = int(m_Enemies[index]->GetWorldPosition().x * scale);
		enemiesArrayY[index] = int(m_Enemies[index]->GetWorldPosition().y * scale);

	}

	x = int(m_Enemies[0]->GetWorldPosition().x * 2);
	y = int(m_Enemies[0]->GetWorldPosition().y * 2);


	m_Rect.x = int(m_Owner->GetWorldPosition().x * scale);
	m_Rect.y = int(m_Owner->GetWorldPosition().y * scale);


	

	Object ghosts1={ Object{SDL_Rect{enemiesArrayX[0],enemiesArrayY[0],30,30},dae::TypeOfObject::Enemy }};
	Object ghosts2={ Object{SDL_Rect{enemiesArrayX[1],enemiesArrayY[1],30,30},dae::TypeOfObject::Enemy }};
	Object ghosts3={ Object{SDL_Rect{enemiesArrayX[2],enemiesArrayY[2],30,30},dae::TypeOfObject::Enemy }};
//	Object ghosts4={ Object{SDL_Rect{enemiesArrayX[3],enemiesArrayY[3],30,30},dae::TypeOfObject::Enemy }};
	

		if (CheckCollision(m_Rect, ghosts1))
		{


			std::cout << "ghots\n";


			if (m_GhostState == int(dae::GhostState::Normal))
			{
				std::cout << "Ghost\n";

				m_pacmanState = 0;

				//ownder->Set that variable to 

				//play dead animation 
				// 
				// play dead sound 
				// 
				// 
				// 
				// 
				 //if
				// and if no more lives 
				// }
				// DYE ();
				// //cambiar scene a Scores 
				// 
				// 
				// }
				// else
				// 
				// {
				// 
				// 
				// 
				Map::GetInstance().ResetMap();   //reset points //uf no more lives ofcourse 
				// reset 
				// if has lives -- live 
				//play dead animation
				// 
				// // resetear el mapa 
				// //todos los puntos //poner collision otra ves 
				// 
				// // poner puntos visisbles otra vez
				// /
				// 
				// }
				// 
				// 


			}

			else
			{

				m_Enemies[0]->SetPosition(30, 30);
				//add to score 
				//play eat sounds 

			}







		}



















	//if ! all have been picked    //execute logic below 

	bool allPelletsNoCollision = true; // Assume all pellets have NoCollision preset initially

	for (size_t i = 0; i < m_objectsVector.size(); i++)
	{
		if (m_objectsVector[i].m_type == TypeOfObject::pellet)
		{
			if (m_objectsVector[i].m_collisionPreset == dae::Collision::CanCollide)
			{

			//if one pellet can collide   means all of the pellets are not set to no collsuom
				// If any pellet has collision preset as CanCollide, set flag to false and break the loop
				allPelletsNoCollision = false;
				break;
			}
		}
	}

	if (allPelletsNoCollision)
	{
		SceneManager::GetInstance().SetCurrentScene("ScoresScene");
	}




	if (!allPelletsNoCollision)
	{

	ExeceuteCollisionLogic();
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

void dae::ColliderComponent::ExeceuteCollisionLogic()
{



	for (size_t i = 0; i < m_objectsVector.size(); i++)
	{

		//check if all the vector has no collision means all dots were picked 

		// if can colliison state == collision then check collision 

		//check if all the ones that are type pellets have no collision how to do that

		////loopera sobre todo en vector if ver si ninguno tiene este tipo

		//ALSO NEED TO PLAY SOUND 


		if (m_objectsVector[i].m_collisionPreset == dae::Collision::CanCollide)
		{

			if (CheckCollision(m_Rect, m_objectsVector[i]))
			{

				/// Ownwe->OnCollision(// otro game object ); //poner logica aqui 

				switch (m_objectsVector[i].m_type)
				{
				case dae::TypeOfObject::pellet:

					Audio::Get().Play(s_PickUpPellet);

					//	std::cout << "Is Collidiing\n" << i << "\n";
					m_objectsVector[i].color.a = 0;
					m_objectsVector[i].m_collisionPreset = dae::Collision::NoCollision;

					//add to score
					s_Score+=10;

					
					break;

				case dae::TypeOfObject::powerUp:
					Audio::Get().Play(s_CanEatGhots);

					//Audio::Get().Play(0);


					m_StartTimer = true;
					m_GhostState = int(dae::GhostState::Blue);
					m_objectsVector[i].m_collisionPreset = dae::Collision::NoCollision;
					m_objectsVector[i].color.a = 0;


					//add to score //and display +2-00 srpite on screen 

					//ghots have to run away from me 


					break;

				case::dae::TypeOfObject::Enemy:

						std::cout << "Ghost\n";

					if (m_GhostState == int(dae::GhostState::Normal))
					{
						std::cout << "Ghost\n";

						//play dead animation 
						// 
						// play dead sound 
						// 
						// 
						// 
						// 
						// 
						// and if no more lives 
						// }
						// DYE ();
						// //cambiar scene a Scores 
						// 
						// 
						// }
						// else
						// 
						// {
						// reset 
						// if has lives -- live 
						//play dead animation
						// 
						// // resetear el mapa 
						// //todos los puntos //poner collision otra ves 
						// 
						// // poner puntos visisbles otra vez
						// /
						// 
						// }
						// 
						// 


					}

					else
					{
						//add to score 
						//play eat sounds 

					}
					break;
				default:
					break;

				}
			}

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

bool dae::ColliderComponent::HasAllBeenPicked()

{



	return true;
}
