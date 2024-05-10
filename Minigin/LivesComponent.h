#pragma once
#include "Component.h"
#include <string>
#include"memory"

namespace dae
{
	class GameObject;
	class TextComponent;
	class PlayerComponent;

	class LivesComponent final : public Component
	{
	public:
		LivesComponent(std::shared_ptr<TextComponent> pTextComponent = nullptr, int priority = 0);
		virtual ~LivesComponent();
		LivesComponent(const LivesComponent& other) = default;
		LivesComponent(LivesComponent&& other) = default;
		LivesComponent& operator=(const LivesComponent& other) = default;
		LivesComponent& operator=(LivesComponent&& other) = default;

		virtual void Update() override;
		

		int m_lives{};

		int GetLives() const;

		//set Lives 


	private:
		std::shared_ptr<TextComponent> m_pTextComponent;
	};
}

