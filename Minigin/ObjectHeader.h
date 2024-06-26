#pragma once
#include"SDL.h"
#include"Renderer.h"
#include"SceneManager.h"
namespace dae
{

	enum class GhostState
	{
		Normal,
		Blue,
		White

	};


	enum class GhostType
	{
		Blue,
		Red,
		Pink,
		Orange

	};




enum class TypeOfObject
{
	Enemy,
	pellet,
	cherry,
	powerUp


};

enum class Visibility
{
	visible,
	Invisible

};



enum class Collision
{
	CanCollide,
	NoCollision            //wgen reseting game reset this as well 

};

struct Object
{
	Object(SDL_Rect rect, TypeOfObject type)
	{
		shape = rect;
		m_type = type;

		if (m_type == dae::TypeOfObject::pellet)
		{
			color = SDL_Color{ 255,255,255,255 };
		}

		else if (m_type == dae::TypeOfObject::powerUp)
		{
			color = SDL_Color{ 255,0,0,255 };
		}

	}





	float m_TotalTimeElapsed{};
	SDL_Rect shape;
	SDL_Color color{};
	TypeOfObject m_type;
	bool m_SetColorBlack = false;
	Visibility m_visibility{ Visibility::visible };
	bool m_IsBlack=false;
	Collision m_collisionPreset{ Collision::CanCollide };

	//add can colide enum or bool 


	void Draw()
	{

		//should I draw if type if enemy ? 
		Renderer::GetInstance().FillSquare(float(shape.x),float(shape.y),float(shape.w),float(shape.h), color);

	}



	void SetColorBlack()
	{
		color =  Renderer::GetInstance().m_Black ;
	}

	void ToogleColor()
	{

		m_IsBlack = !m_IsBlack;
	}


	void Update()
	{


		if (m_collisionPreset != Collision::NoCollision)
		{


			if (m_type == dae::TypeOfObject::powerUp)
			{
				m_TotalTimeElapsed += SceneManager::GetInstance().GetDeltaTime();

				if (m_TotalTimeElapsed >= 0.16f)
				{
					m_TotalTimeElapsed = 0;
					ToogleColor();

					if (m_IsBlack)
					{
						color = Renderer::GetInstance().m_White;
					}

					else
					{
						color = Renderer::GetInstance().m_Black;

					}

				}

			}

		}

	}

	

};

};