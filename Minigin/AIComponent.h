#pragma once
#include "Component.h"
#include"functional"
#include <memory>
#include <glm/glm.hpp>
#include"Helper.h"
#include"ObjectHeader.h"


	struct Node
	{
		int y;
		int x;
		int parentX;
		int parentY;
		float gCost;
		float hCost;
		float fCost;
	};


namespace dae
{

	enum class GhostAiState
	{

		Waiting,
		Patrolling,
		Chasing
	};


	class SceneManager;


	class AIComponent :public Component
	{

	public:

		// this class wil, take an enum class that /describes the personality of each Ghost 


		//gess needs pacman position of pacmans 


		AIComponent(std::shared_ptr<GameObject> SelfGameObject, std::shared_ptr<GameObject> pTargetGameObejct, dae::GhostType Type);
		//fantasma enum class y adentro dependiedo del typo cambio la velocidad 

		virtual void Render() override;
		virtual void Update() override;


		//remember personalities of the ghosts 
		void CheckState();

	private:
		std::shared_ptr<GameObject> m_Self = nullptr;
		std::shared_ptr<GameObject> m_Target = nullptr;


		void CheckGhost(GhostType WhichGhost);

		void RunAway(const int & ghotsPosX, const int& ghotsPosY,Node & TargetNode);

		glm::vec3 m_OldPosition;
		glm::vec3 m_Direction;

		glm::vec3 newPosition{};
		SceneManager* m_pSceneManager{ nullptr };

		GhostType m_TypeOfGhost;

		float m_Speed{};

		static const int Ghosts{3};
		float m_ghotsTimersArray[Ghosts]{};

		GhostAiState m_GhotsAiState{ GhostAiState::Waiting};   //since red starts can set it is state to patrolling 


		std::vector < std::tuple<int, int>>m_Pos{};

		std::vector<  std::tuple<int, int>>m_OrangeGhosts{};



		int rowTest{};
		int Column{};





	};


};