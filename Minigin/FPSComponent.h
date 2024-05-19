#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace dae
{
	class GameObject;

	class LivesConponent final :public Component
	{
	public:

		virtual void Update() override;
		LivesConponent(bool isScore,std::shared_ptr<TextComponent> pTextComponent = nullptr, int priority = 0);


		virtual ~LivesConponent() = default;
		LivesConponent(const LivesConponent& other) = default;
		LivesConponent(LivesConponent&& other) = default;
		LivesConponent& operator=(const LivesConponent& other) = default;
		LivesConponent& operator=(LivesConponent&& other) = default;

	private:
		std::shared_ptr<TextComponent> m_pTextComponent;



		bool m_IsScore = false;
		


	};
}
