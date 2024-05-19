#pragma once
#include"Component.h"
#include"Renderer.h"
#include<memory>
#include"ObjectHeader.h"
#include"FPSComponent.h"


namespace dae
{
	

	class ColliderComponent : public Component
	{

	public:
	
		ColliderComponent(std::shared_ptr<GameObject> owner, std::vector<Object> & collideswidth, std::vector<std::shared_ptr<GameObject>> & ghosts);  //make collider width dimensions

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
		bool Collides(SDL_Rect & self,Object & objects);     //put this in constructor 
		SDL_Rect m_Collider{};

		std::shared_ptr<GameObject> m_Owner =nullptr;
		std::vector<std::shared_ptr<GameObject>> m_Enemies;  //this was the error was a refernce to other pointer and was going 
		//out of scope 
		std::vector<Object> & m_objectsVector;
		bool m_HaveAllBeenPicked = false;

		bool m_StartTimer = false;
		float m_ToogleSpriteTimer{};
		void ToogleSprite();

		bool HasAllBeenPicked();
		std::shared_ptr<GameObject> firstGhost =nullptr;
	

		static const int m_EnemiesPos{4};
		int enemiesArrayX[m_EnemiesPos]{};
		int enemiesArrayY[m_EnemiesPos]{};

		void HandleCollisonGhosts(Object& ghots, int x, int y, int id);
		

		int x = 0;
		int y = 0;
		int& Xpos =x;
		int& Ypos = y;

		bool m_CanPush = true;
		
		std::vector<Object> m_ghotsObject{};

		int CheckState();

		void ResetLevel();


		int m_normalState = int(dae::GhostState::Normal);



		bool m_StartPauseGameTimer = false;

		float m_TimeElapsedTillResetting{ 0 };



		// get the sahpe of other we can have a get shape compnent or add the function the the oesn we alredy have 


		//void BlockCollion();








	};


}