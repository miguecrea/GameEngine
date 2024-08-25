#pragma once


#include "Component.h"
#include<memory>
#include<vector>
#include"Node.h"
namespace dae
{
	class GameObject;

	class BrainComponent final :public Component
	{
	public:

		virtual void Update() override;
		BrainComponent(std::vector<std::shared_ptr<GameObject>> & ghosts);

		virtual ~BrainComponent() = default;
		BrainComponent(const BrainComponent& other) = default;
		BrainComponent(BrainComponent&& other) = default;
		BrainComponent& operator=(const BrainComponent& other) = default;
		BrainComponent& operator=(BrainComponent&& other) = default;

	private:

		std::vector<std::shared_ptr<GameObject>> m_Enemies;
		std::vector<Node> path{};

		const float m_speed = 30.f;



	};
}
