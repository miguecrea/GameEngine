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

	private:
		std::shared_ptr<GameObject> m_Self = nullptr;
		std::shared_ptr<GameObject> m_Target = nullptr;


		void CheckGhost(Node & ghotsPos,Node & targetpos);

		void RunAway(Node & TargetNode);

		glm::vec3 m_OldPosition;
		glm::vec3 m_Direction;

		glm::vec3 newPosition{};
		SceneManager* m_pSceneManager{ nullptr };

		GhostType m_TypeOfGhost;

		float m_Speed{};
		float m_copy{};

		static const int Ghosts{3};
		float m_ghotsTimersArray[Ghosts]{};

		GhostAiState m_GhotsAiState{ GhostAiState::Waiting};   //since red starts can set it is state to patrolling 
		int m_firstValue;
		int m_secondValue;

		std::vector < std::tuple<int, int>>m_Pos{};

		std::vector<  std::tuple<int, int>>m_OrangeGhosts{};

		float m_GhostWaitingTime{0};

		float m_timertest{0};



		int m_rowTest{0};
		int m_Column{0};
		int m_index{ 0 };


		std::vector<std::tuple<int, int>> m_GridpositionsToPatrol;

		void Patrol(const std::vector<std::tuple<int, int>> & patrolPoints, Node& currentPos,Node & targetPos);
		void Chase(Node & target);

		void GoTo(int  row, int  column, Node& TargetNode);

		bool HasArrived(Node& ghosts, Node& TargetNode);
	
		float distanceBetweenPoints();
	};


};