#include "FPSComponent.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include <string>
#include <iostream>
#include"staticHeader.h"

dae::LivesConponent::LivesConponent(int Lives, std::shared_ptr<TextComponent> pTextComponent, int priority)
	:Component(priority), m_pTextComponent{ pTextComponent },m_Lives{Lives}
{
}
void dae::LivesConponent::Update()
{

			if (m_pTextComponent)
			{
			//	Output to render component
			//	m_pTextComponent->SetTextToTexture(std::to_string(m_Lives));
				m_pTextComponent->SetTextToTexture("Score is "+ std::to_string(s_Score));
			}
	
}

