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
		LivesConponent(int Lives,std::shared_ptr<TextComponent> pTextComponent = nullptr, int priority = 0);


		virtual ~LivesConponent() = default;
		LivesConponent(const LivesConponent& other) = default;
		LivesConponent(LivesConponent&& other) = default;
		LivesConponent& operator=(const LivesConponent& other) = default;
		LivesConponent& operator=(LivesConponent&& other) = default;

	private:
		std::shared_ptr<TextComponent> m_pTextComponent;

		void SetText()
		{
			if (m_pTextComponent)
			{
				//Output to render component
				m_pTextComponent->SetTextToTexture(std::to_string(m_Lives));
			}

		}
		
		int  m_Lives;


	};
}
