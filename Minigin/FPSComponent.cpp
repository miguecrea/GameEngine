#include "FPSComponent.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include <string>
#include <iostream>
#include"staticHeader.h"

dae::LivesConponent::LivesConponent(bool isScore,std::shared_ptr<TextComponent> pTextComponent, int priority)
	:Component(priority), m_pTextComponent{ pTextComponent},m_IsScore{isScore}
{
}
void dae::LivesConponent::Update()
{

			if (m_pTextComponent)
			{


				if (m_IsScore)
				{

				m_pTextComponent->SetTextToTexture("Score is "+ std::to_string(s_Score));
				}
				else
				{
					m_pTextComponent->SetTextToTexture("Lives Remanining " + std::to_string(s_Lives));

				}
			

			//		m_pTextComponent->SetTextToTexture("Lives Remanining " + std::to_string(s_Lives));


			}
	
}

