#include "HighScoreComponent.h"
#include"staticHeader.h"


dae::HighScoreComponent::HighScoreComponent(std::shared_ptr<TextComponent> pTextComponent, int priority)
	: Component(priority), m_pTextComponent{ pTextComponent }
{
}

void dae::HighScoreComponent::Update()
{

	if (m_pTextComponent)
	{
			m_pTextComponent->SetTextToTexture("Player Score is : " + std::to_string(s_HighScore));

	}
}