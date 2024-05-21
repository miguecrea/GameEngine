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
	m_Rect.w = 20;   //changed collider //was in 30
	m_Rect.h = 20;
}

dae::ColliderComponent::~ColliderComponent()
{
	
}

void dae::ColliderComponent::Render()
{

	//Renderer::GetInstance().FillSquare(float(m_Rect.x),float(m_Rect.y),float(m_Rect.w),float(m_Rect.h), Renderer::GetInstance().m_White);


	//Renderer::GetInstance().FillSquare(float(x),float(y), float(m_Rect.w), float(m_Rect.h), Renderer::GetInstance().m_White);

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
	Object ghosts4={ Object{SDL_Rect{enemiesArrayX[3],enemiesArrayY[3],30,30},dae::TypeOfObject::Enemy }};
	


	HandleCollisonGhosts(ghosts1, 88, 128, 0);
	HandleCollisonGhosts(ghosts2, 105, 128, 1);
	HandleCollisonGhosts(ghosts3, 88, 140, 2);
	HandleCollisonGhosts(ghosts4, 120, 128, 3);


	

	

	if (m_StartPauseGameTimer)
	{
		//time elasped to reset level
		m_TimeElapsedTillResetting += SceneManager::GetInstance().GetDeltaTime();

		if (m_TimeElapsedTillResetting >= 3.f )
		{
			if (s_Lives > 0)
			{
			Audio::Get().Play(s_GameSoundId);

			}
			m_StartPauseGameTimer = false;
			m_TimeElapsedTillResetting = 0;
			s_PauseGame = 0;

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

		if (m_objectsVector[i].m_collisionPreset == dae::Collision::CanCollide)
		{

			if (Collides(m_Rect, m_objectsVector[i]))
			{

				/// Ownwe->OnCollision(// otro game object ); //poner logica aqui 

				switch (m_objectsVector[i].m_type)
				{
				case dae::TypeOfObject::pellet:

					Audio::Get().Play(s_PickUpPellet);

					//	std::cout << "Is Collidiing\n" << i << "\n";
					m_objectsVector[i].color.a = 0;
					m_objectsVector[i].m_collisionPreset = dae::Collision::NoCollision;

					s_Score+=10;

					
					break;

				case dae::TypeOfObject::powerUp:
					Audio::Get().Play(s_CanEatGhots);

					//Audio::Get().Play(0);

					m_StartTimer = true;
					m_GhostState = int(dae::GhostState::Blue);
					m_objectsVector[i].m_collisionPreset = dae::Collision::NoCollision;
					m_objectsVector[i].color.a = 0;

					break;

				case::dae::TypeOfObject::Enemy:

					break;
				default:
					break;

				}
			}

		}


	}

}



bool dae::ColliderComponent::Collides(SDL_Rect& self, Object& objects)
{
	if (self.x + self.w < objects.shape.x || objects.shape.x + objects.shape.w < self.x)
		return false;

	if (self.x > objects.shape.x + objects.shape.w || objects.shape.x > self.x + self.w)
		return false;

	if (self.y + self.h < objects.shape.y || objects.shape.y + objects.shape.h < self.y)
		return false;

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

void dae::ColliderComponent::HandleCollisonGhosts(Object& ghots, int CenterX, int CenterY, int id)
{

	bool collisionDetected = false;

	// Check collision only if collision preset allows it
	if (ghots.m_collisionPreset == Collision::CanCollide)        //id
	{
		if (Collides(m_Rect, ghots))
		{
			if (!collisionDetected) // Check if collision has already been detected in this frame
			{

				collisionDetected = true; // Set collision detected flag

				if (CheckState() == m_normalState)
				{
					// Deduct life only if lives are greater than 0
					if (s_Lives > 0)
					{

						Audio::Get().Play(s_DeathMusic);

						s_Lives--;

						m_pacmanState = 0; 

						m_Enemies[0]->SetPosition(88, 128);
						m_Enemies[1]->SetPosition(105, 128);
						m_Enemies[2]->SetPosition(88, 140);
						m_Enemies[3]->SetPosition(120, 128);
					
						m_StartPauseGameTimer = true;
						s_PauseGame = 1;



					}

					else
					{

						SceneManager::GetInstance().SetCurrentScene("ScoresScene");
						Audio::Get().Play(s_MenuMusicId);
					}


				}
				else
				{

					s_Score += 100;
					Audio::Get().Play(s_AteGhostSound);

					m_Enemies[id]->SetPosition(float(CenterX),float(CenterY));
				}
			}
		}
		else
		{
			// Reset collision detected flag if no collision detected
			collisionDetected = false;
		}
	}





















}

int dae::ColliderComponent::CheckState()
{
	return m_GhostState;
}

void dae::ColliderComponent::ResetLevel()
{
}
