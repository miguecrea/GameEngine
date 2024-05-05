#pragma once
#include"Component.h"
#include"Renderer.h"
#include<memory>
#include"ObjectHeader.h"


namespace dae
{
	

	class ColliderComponent : public Component
	{

	public:
	
		ColliderComponent(std::shared_ptr<GameObject> owner, std::vector<Object> & collideswidth);  //make collider width dimensions

		virtual ~ColliderComponent();
		ColliderComponent(const ColliderComponent& other) = default;
		ColliderComponent(ColliderComponent&& other) = default;
		ColliderComponent& operator=(const ColliderComponent& other) = default;
		ColliderComponent& operator=(ColliderComponent&& other) = default;

		virtual void Render() override;
		virtual void Update() override;

		void ExeceuteCollisionLogic();


		float m_totalTimeElapsed{};
		SDL_Rect m_Rect = {};

	private:
		bool CheckCollision(SDL_Rect & self,Object & objects);     //put this in constructor 
		SDL_Rect m_Collider{};

		std::shared_ptr<GameObject> m_Owner =nullptr;
		//std::vector<std::shared_ptr<GameObject>> m_Enemies;
		std::vector<Object> & m_objectsVector;
		bool m_HaveAllBeenPicked = false;

		bool m_StartTimer = false;
		float m_ToogleSpriteTimer{};
		void ToogleSprite();

		bool HasAllBeenPicked();


		// get the sahpe of other we can have a get shape compnent or add the function the the oesn we alredy have 


		//void BlockCollion();








	};


}