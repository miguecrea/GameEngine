#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Scene.h"

#include "UpdatePositionCommand.h"
#include "SetPositionCommand.h"
#include <memory>
#include "RenderComponent.h"
#include "GameObject.h"
#include "Controller.h"
#include "Keyboard.h"
#include"RotatorComponent.h"
#include"AnimationComponent.h"
#include"StartInfoComponent.h"
#include"PacmanManager.h"
#include<iostream>
#include"Renderer.h"
#include"ColliderComponent.h"
#include"Renderer.h"
#include"TextComponent.h"
#include"ResourceManager.h"
#include"Renderer.h"
#include"AIComponent.h"

struct Point2f
{
	int x, y;
};

struct Rectf
{

	int x, y, widtgh, height;

};

namespace Exercises
{
	void Drawing(dae::Scene& scene);
	void Rotating(dae::Scene& scene);
	void TrashTheCache(dae::Scene& scene);
}


void LoadDotComponent()
{





	for (size_t i = 0; i < 100; i++)
	{


	}



}


void SetPacmanLeft()
{
	//auto & PacmanManager = dae::PacmanManager::GetInstance();   //makie function forthis and just call 

	//if (PacmanManager.m_pacmanDirection != PlayerDirection::LEFT)
	//{
	//PacmanManager.m_pacmanDirection = PlayerDirection::LEFT;   //so we dont spawn the update 

	//}



	//	auto& PacmanManager = dae::PacmanManager::GetInstance();

			//auto pacmanDirection = PacmanManager.m_pacmanDirection;    //how you call functions with a 

			//pacmanDirection = PlayerDirection::LEFT;


	//auto pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };\






}




void LoadMenuScene()
{

	auto& MenuScene = dae::SceneManager::GetInstance().CreateScene("MenuScene");

	auto ImGuiGameObject = std::make_shared<dae::GameObject>();
	auto iamguiComponent = std::make_shared<dae::StartInfoComponent>();
	ImGuiGameObject->AddComponent(iamguiComponent);
	ImGuiGameObject->SetPosition(100, 200);
	MenuScene.Add(ImGuiGameObject);



	auto MapGameObject = std::make_shared<dae::GameObject>();
	auto MapRender = std::make_shared<dae::RenderComponent>(-1, false);    //this one has tl take my animation class 
	MapRender->SetTexture("pac.png");
	MapRender->SetDimension(2.f);
	MapGameObject->AddComponent(MapRender);
	MapGameObject->SetPosition(-7, -20);
	MenuScene.Add(MapGameObject);



	//
	auto TextGameObject = std::make_shared<dae::GameObject>();
	auto RenderComponentforText = std::make_shared<dae::RenderComponent>(-1, false);
	TextGameObject->AddComponent(RenderComponentforText);

	auto TextComponent = std::make_shared<dae::TextComponent>(RenderComponentforText);

	const int size{ 30 };
	TextComponent->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", size));
	TextComponent->SetTextToTexture("Play - PRESS 1");
	TextGameObject->AddComponent(TextComponent);
	TextGameObject->SetPosition(100, 200);

	MenuScene.Add(TextGameObject);
	//
	//dae::Renderer::GetInstance().FillSquare(100,200, 40,60, SDL_Color{255,0,0,255});






















}






void load()
{
	//WWWauto & scene2 = dae::SceneManager::GetInstance().CreateScene("SecondSceneScene");  //creaate scene    
	//auto & ScoresScene = dae::SceneManager::GetInstance().CreateScene("ScoresScene");  //creaate scene     

	LoadMenuScene();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("PlayerScene");  //creaate scene   
	auto& input = dae::InputManager::GetInstance();



	//float scale{2.f}
		  //pacman Map
		//mapa //ventana estan por 2 ,  
		//tambine mis posiciones estan x2 
		//un poco de harcode el el command tambien 
		//check the render aswell 
	////////////////////////////////////////


	//MAPA 

	auto MapGameObject = std::make_shared<dae::GameObject>();
	auto MapRender = std::make_shared<dae::RenderComponent>(-1, false);    //this one has tl take my animation class 
	MapRender->SetTexture("Map.png");
	MapRender->SetDimension(2.f);
	MapGameObject->AddComponent(MapRender);
	MapGameObject->SetPosition(0, 0);
	scene.Add(MapGameObject);
	float setSpeed{ 10.f };
	float updateSpeed{ 100.f };




	/////////////////////////////////////////////////////////////
	///mrs pacman


	auto pPlayer1 = std::make_shared<dae::GameObject>();
	auto pPlayer1Renderer = std::make_shared<dae::RenderComponent>(-1, true);
	pPlayer1Renderer->SetTexture("pacman204x85px.png");
	pPlayer1Renderer->SetDimension(1.2f);
	//	pPlayer1Renderer->AddToVector(5, 12, 12, 7, dae::AnimationComponent::Type::loop, 1, 0);   //dead
	pPlayer1Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);  //right 
	pPlayer1Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//left 
	pPlayer1Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 3);//up
	pPlayer1Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 4);//down
	pPlayer1->SetPosition(8, 32);
	pPlayer1->AddComponent(pPlayer1Renderer);
	pPlayer1->SetPosition(100, 100);
	scene.Add(pPlayer1);


	auto controller{ input.AddController() };

	glm::vec3 direction{ 0.f,-setSpeed,0.f };
	std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };  //player 1 and direction

	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonY, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { 0.f,setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };  //overwrites it 

	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::move(pMoveCommand), dae::ButtonState::Down);


	direction = { -setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonX, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonB, std::move(pMoveCommand), dae::ButtonState::Down);


	direction = { 0.f,-updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadUp, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadDown, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadLeft, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadRight, std::move(pMoveCommand), dae::ButtonState::Pressed);
	setSpeed *= 0.5f;
	updateSpeed *= 0.5f;




	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//pacman
	auto pPlayer2 = std::make_shared<dae::GameObject>();
	auto pPlayer2Renderer = std::make_shared<dae::RenderComponent>(-1, true);
	pPlayer2Renderer->SetTexture("pacman204x85px.png");
	pPlayer2Renderer->SetDimension(1.5f);
	//pPlayer2Renderer->AddToVector(5,12,12,7, dae::AnimationComponent::Type::loop, 1,0);   //dead
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);  //right 
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//left 
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 3);//up
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 4);//down
	pPlayer2->AddComponent(pPlayer2Renderer);
	pPlayer2->SetPosition(100, 200);
	scene.Add(pPlayer2);

	//auto PlayerCollider = std::make_shared<dae::ColliderComponent>();

	auto keyboard{ input.GetKeyboard() };


	direction = { 0.f,-updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_W, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_S, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_A, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_D, std::move(pMoveCommand), dae::ButtonState::Pressed);



	//Controller nr 2
	controller = { input.AddController() };     //overwrites the old one

	//Button pressed
	direction = { 0.f,-updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadUp, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadDown, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadLeft, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadRight, std::move(pMoveCommand), dae::ButtonState::Pressed);









	////////////////////////////////////////////////




	auto PinkGhostGameObject = std::make_shared<dae::GameObject>();
	auto PinkGhostRenderer = std::make_shared<dae::RenderComponent>(-1, true);
	PinkGhostRenderer->SetTexture("pink.png");
	PinkGhostRenderer->SetDimension(1.6f);
	//PinkGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
//	PinkGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
	PinkGhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
	PinkGhostGameObject->SetPosition(8, 32);
	PinkGhostGameObject->AddComponent(PinkGhostRenderer);

	auto AiComponent = std::make_shared<dae::AIComponent>(PinkGhostGameObject, pPlayer2);  // Puede tomar un game object 
	PinkGhostGameObject->AddComponent(AiComponent);   
	scene.Add(PinkGhostGameObject);





	auto RedGhostGameObject = std::make_shared<dae::GameObject>();
	auto RedGhostRenderer = std::make_shared<dae::RenderComponent>(3, true);
	RedGhostRenderer->SetTexture("red.png");
	RedGhostRenderer->SetDimension(1.6f);
	//RedGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
	RedGhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
	//RedGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
	RedGhostGameObject->SetPosition(8, 64);
	RedGhostGameObject->AddComponent(RedGhostRenderer);
	scene.Add(RedGhostGameObject);





	auto YellowGhostGameObject = std::make_shared<dae::GameObject>();
	auto YellowGhostRenderer = std::make_shared<dae::RenderComponent>(3, true);
	YellowGhostRenderer->SetTexture("yellow.png");
	YellowGhostRenderer->SetDimension(1.6f);
	YellowGhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
	//	YellowGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
		//YellowGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
	YellowGhostGameObject->SetPosition(32, 32);
	YellowGhostGameObject->AddComponent(YellowGhostRenderer);
	scene.Add(YellowGhostGameObject);





	auto BlueGhostGameObject = std::make_shared<dae::GameObject>();
	auto BlueGhostRenderer = std::make_shared<dae::RenderComponent>(3, true);
	BlueGhostRenderer->SetTexture("BlueGhost.png");
	BlueGhostRenderer->SetDimension(1.6f);
	BlueGhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
	BlueGhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
	BlueGhostRenderer->AddToVector(3, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
	BlueGhostGameObject->SetPosition(64, 32);
	BlueGhostGameObject->AddComponent(BlueGhostRenderer);
	scene.Add(BlueGhostGameObject);






















}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}


















//auto Hero = std::make_shared<dae::GameObject>();
//auto HeroRender = std::make_shared<dae::RenderComponent>(-2, true);  //enum class 
//HeroRender->SetTexture("Hero.png");
//HeroRender->SetDimension(1.f);   ///not used for now 
////void AddVector , enum class 
//HeroRender->AddToVector(6, 5, 4, 7, dae::AnimationComponent::Type::loop, 0, 3);

//Hero->AddComponent(HeroRender);
//Hero->SetPosition(210, 100);  //keep this  game objects sets pos
//scene.Add(Hero);
































//I can have a spriteAniamtion Component that allows me to set the amnimation thingy settings 

//and also a manager to see the direction of the 


////Foreground -- Text
//auto pTextImage = std::make_shared<dae::GameObject>();

//auto pTextRenderer = std::make_shared<dae::RenderComponent>();
//auto pProgTextComponent = std::make_shared<dae::TextComponent>(pTextRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
//pProgTextComponent->SetTextToTexture("Programming 4 Assignment"); //set the actual text of it 
//pTextImage->AddComponent(pTextRenderer);
//pTextImage->SetPosition(80, 50);
//scene.Add(pTextImage);

////Background
//auto pBackgroundImage = std::make_shared<dae::GameObject>(100);
//auto pBackgroundRender = std::make_shared<dae::RenderComponent>(0);
//pBackgroundRender->SetTexture("background.tga");
//pBackgroundImage->AddComponent(pBackgroundRender);
//scene.Add(pBackgroundImage);

////Make fps-counter
//auto pCounterFPS = std::make_shared<dae::GameObject>();

////Text rendendering
//auto pFrameRateRenderer = std::make_shared<dae::RenderComponent>();
//auto pTextComponent = std::make_shared<dae::TextComponent>(pFrameRateRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
//pTextComponent->SetColor({ 200,200,0 });

////FPS component
//pCounterFPS->AddComponent(pTextComponent);

//auto pFPSComponent = std::make_shared<dae::FPSComponent>(pCounterFPS->GetComponent<dae::TextComponent>(), 0.5f);
////auto pFPSComponent = std::make_shared<dae::FPSComponent>(pTextComponent, 0.5f); //-- The same result as above

//pCounterFPS->AddComponent(pFrameRateRenderer);
//pCounterFPS->AddComponent(pFPSComponent);

////Add to scene
//pCounterFPS->SetPosition(10.f, 10.f);
//scene.Add(pCounterFPS);

////Rotating balls
//auto pRotatingBallParent = std::make_shared<dae::GameObject>();  //make a game object

//auto pParentRenderer = std::make_shared<dae::RenderComponent>();
//pParentRenderer->SetTexture("Balloom.png");
//pRotatingBallParent->AddComponent(pParentRenderer);  //add renderer to r
//pRotatingBallParent->SetPosition(100, 100);




//const glm::vec3 origin{ 300.f,320.f,0.f };
//constexpr float length{ 50.f }, cycleTime{ 5.f };

//auto sineMovementParent = std::make_shared<dae::Rotatt>(origin, length, cycleTime);
//pRotatingBallParent->AddComponent(sineMovementParent);

//auto pRotatingBallChild = std::make_shared<dae::GameObject>();

//auto pChildRenderer = std::make_shared<dae::RenderComponent>();
//pChildRenderer->SetTexture("Oneal.png");
//pRotatingBallChild->AddComponent(pChildRenderer);

//auto sineMovementChild = std::make_shared<dae::SineMovementComponent>(glm::vec3{ 0.f,0.f,0.f }, length * 2.f, cycleTime);
//pRotatingBallChild->AddComponent(sineMovementChild);

//pRotatingBallParent->AddChild(pRotatingBallChild.get()); //set as child 

//scene.Add(pRotatingBallChild);
//scene.Add(pRotatingBallParent);
