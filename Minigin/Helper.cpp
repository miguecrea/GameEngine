#include "Helper.h"
#include "ResourceManager.h"
#include"RenderComponent.h"
#include"TextComponent.h"
#include "GameObject.h"
#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include<iostream>




//void dae::CreateButton(Scene& scene, const glm::vec2& position, const std::string& text, int fontSize)
//{
//
//	//const auto pButtonObject{ scene.Add(std::make_shared<GameObject>()) };
//	//pButtonObject->SetPosition(position);
//
//	
//		//const auto pTextObject{ std::make_shared<GameObject>() };
//	//	pButtonObject->AddChild(pTextObject, false);
//
//	//const auto pTextRenderer{ std::make_shared<RenderComponent>(-2,false)};
//
//
//	//	pTextObject->AddComponent(pTextRenderer);
//
//		//const auto pText{ std::make_shared<TextComponent>(pTextRenderer) };
//	//	pText->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize));
//	//	pText->SetTextToTexture(text);
//
//	//	pTextObject->AddComponent(pText);
//	//	pTextObject->SetPosition({ 10.f, -fontSize * 0.5f + 2.f });
//
//	///*	const auto pButton{ std::make_shared<ButtonComponent>(callBack, 100,fontSize) };
//	//	pTextObject->AddComponent(pButton);*/
//
//	//SDL_Color color sd{};
//	//	Renderer::GetInstance().FillSquare(200, 100);
//	
//
//
//}
