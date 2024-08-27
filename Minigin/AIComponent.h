#pragma once
#include "Component.h"
#include"functional"
#include <memory>
#include <glm/glm.hpp>
#include"Helper.h"
#include"ObjectHeader.h"
#include"Node.h"



namespace dae
{

	struct SharedKnowledge {
		bool pacmanSpotted;
		Node pacmanPosition;
		std::vector<Node> strategicPoints;
	};

	// Global shared knowledge that all ghosts can access
	

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


		SharedKnowledge sharedKnowledge;
		AIComponent(std::shared_ptr<GameObject> SelfGameObject, std::shared_ptr<GameObject> pTargetGameObejct, dae::GhostType Type);
		//fantasma enum class y adentro dependiedo del typo cambio la velocidad 

		virtual void Render() override;
		virtual void Update() override;


		void MoveAlongPath(const std::vector<Node>& path);
		void AdjustPosition(float deltaX, float deltaY);


		std::vector<Node> path{};

	private:
		std::shared_ptr<GameObject> m_Self = nullptr;
		std::shared_ptr<GameObject> m_Target = nullptr;


		void CheckGhost(Node & ghotsPos,Node & targetpos);

		void RunAway(Node & TargetNode);

		glm::vec3 m_OldPosition;
		glm::vec3 m_Direction;

		glm::vec3 newPosition{};
		SceneManager * m_pSceneManager{ nullptr };

		GhostType m_TypeOfGhost;

		float m_Speed{};
		float m_copy{};

		static const int Ghosts{3};
		float m_ghotsTimersArray[Ghosts]{};

		GhostAiState m_GhotsAiState{ GhostAiState::Waiting};   
		int m_firstValue;
		int m_secondValue;

		std::vector <std::tuple<int, int>>m_Pos{};

		std::vector<std::tuple<int, int>>m_OrangeGhosts{};

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