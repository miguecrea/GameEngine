#pragma once
#include"Component.h"
#include"Renderer.h"


namespace dae
{

	class ColliderComponent : public Component
	{

	public:
	
		ColliderComponent();

		virtual ~ColliderComponent();
		ColliderComponent(const ColliderComponent& other) = default;
		ColliderComponent(ColliderComponent&& other) = default;
		ColliderComponent& operator=(const ColliderComponent& other) = default;
		ColliderComponent& operator=(ColliderComponent&& other) = default;

		virtual void Update() override;

		SDL_Rect m_Rect;



	

      

	private:
		//bool CheckCollision();         //remember to check scale
		//void BlockCollion();




	};


}