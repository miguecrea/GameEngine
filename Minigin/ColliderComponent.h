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

		SDL_Rect m_Rect = {};

	private:
		bool CheckCollision(SDL_Rect & self,Object & objects);     //put this in constructor 
		SDL_Rect m_Collider;

		std::vector<Object> & m_objectsVector;

		// get the sahpe of other we can have a get shape compnent or add the function the the oesn we alredy have 


		//void BlockCollion();

		std::shared_ptr<GameObject> m_Owner =nullptr;






	};


}