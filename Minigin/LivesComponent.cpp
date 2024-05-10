#include "LivesComponent.h"


#include "TextComponent.h"
#include <iostream>
#include "EventManager.h"

dae::LivesComponent::LivesComponent(std::shared_ptr<TextComponent> pTextComponent, int priority)
	:Component(priority), m_pTextComponent(pTextComponent),m_lives{3}
{
}

dae::LivesComponent::~LivesComponent()
{
}

void dae::LivesComponent::Update()
{


	std::string text{ "Lives: " + std::to_string(m_lives) };

	if (m_pTextComponent)
	{

		m_pTextComponent->SetColor(SDL_Color{});
		m_pTextComponent->SetTextToTexture(text);
	}
}


