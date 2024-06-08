


#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace dae
{
	class GameObject;

	class HighScoreComponent final :public Component
	{
	public:

		virtual void Update() override;
		HighScoreComponent(std::shared_ptr<TextComponent> pTextComponent = nullptr, int priority = 0);


		virtual ~HighScoreComponent() = default;
		HighScoreComponent(const HighScoreComponent& other) = default;
		HighScoreComponent(HighScoreComponent&& other) = default;
		HighScoreComponent& operator=(const HighScoreComponent& other) = default;
		HighScoreComponent& operator=(HighScoreComponent&& other) = default;

	private:
		std::shared_ptr<TextComponent> m_pTextComponent;
		bool m_IsScore = false;





	};
}
