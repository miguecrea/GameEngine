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

struct Point2f
{
	int x, y;
};

struct Cube
{
	Point2f p1;
	Point2f p2;
	Point2f p3;
	Point2f p4;
	
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



		//
		// use the parser to       //make sure I dont set the texture that many times 
		// 
		//        




	}



}


void SetPacmanLeft()
{
	auto & PacmanManager = dae::PacmanManager::GetInstance();   //makie function forthis and just call 

	if (PacmanManager.m_pacmanDirection != PlayerDirection::LEFT)
	{
	PacmanManager.m_pacmanDirection = PlayerDirection::LEFT;   //so we dont spawn the update 

	}
}




void Scene1()
{



	auto& scene = dae::SceneManager::GetInstance().CreateScene("firstScene");  //creaate scene     //reference because is singleton and we only need one 

	auto& input = dae::InputManager::GetInstance();  //gets instace of imput manager 

//	auto& PacmanManager = dae::PacmanManager::GetInstance();

	//auto pacmanDirection = PacmanManager.m_pacmanDirection;    //how you call functions with a 
	 
	//pacmanDirection = PlayerDirection::LEFT;





//float scale{2.f}
//	//pacman Map
//
//

	//mapa //ventana estan por 2 ,  


	auto MapGameObject = std::make_shared<dae::GameObject>();
	auto MapRender = std::make_shared<dae::RenderComponent>(-1,false);    //this one has tl take my animation class 
	MapRender->SetTexture("Map.png");

	MapRender->SetDimension(2.f);
	MapGameObject->AddComponent(MapRender);
	MapGameObject->SetPosition(0, 0);   //use the game object to set the texture 
	scene.Add(MapGameObject);

	///////////

	float setSpeed{ 100.f };
	float updateSpeed{ 300.f };
	auto pPlayer1 = std::make_shared<dae::GameObject>();
	auto pPlayer1Renderer = std::make_shared<dae::RenderComponent>(-2,false);
	pPlayer1Renderer->SetTexture("Balloom.png");
	//pPlayer1Renderer->AddToVector(3,3,3,10,d)
	pPlayer1Renderer->SetDimension(0.7f);  //set texture  scale 


	////



	//Renderer::GetInstance().
	pPlayer1->AddComponent(pPlayer1Renderer);
	pPlayer1->SetPosition(100, 100);
	scene.Add(pPlayer1);

	//Controller
	auto controller{ input.AddController() };  //this is tge manager 

	//Button down (Set position command)


	// A,B,Y,X //BUTTON XBox one tap move position or teleport 

	//Y negative 
	glm::vec3 direction{ 0.f,-setSpeed,0.f };   // y move donw                           //gets a game object 
	std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };  //player 1 and direction

	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonY, std::move(pMoveCommand), dae::ButtonState::Down);
	//takes a command 



//y positive
	direction = { 0.f,setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };  //overwrites it 



	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::move(pMoveCommand), dae::ButtonState::Down);

	//X negative
	direction = { -setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonX, std::move(pMoveCommand), dae::ButtonState::Down);

	//X positive 
	direction = { setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonB, std::move(pMoveCommand), dae::ButtonState::Down);

	//Button pressed (Update position command)   // smoth con las flechitas 
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

	auto pPlayer2 = std::make_shared<dae::GameObject>();  //PLAYER 2  
	auto pPlayer2Renderer = std::make_shared<dae::RenderComponent>(-1,true);   //render component 
	pPlayer2Renderer->SetTexture("pacman204x85px.png");  //set texture
	pPlayer2Renderer->SetDimension(1.f);  //set texture  scale
	//pPlayer2Renderer->AddToVector(5,12,12,7, dae::AnimationComponent::Type::loop, 1,0);
	pPlayer2Renderer->AddToVector(5,12,2,7, dae::AnimationComponent::Type::loop, 1,1);


	pPlayer2->AddComponent(pPlayer2Renderer); //add redner to game object  //here is when it 
	pPlayer2->SetPosition(8,32);  //set    //renderer takes the game object world Pos
	scene.Add(pPlayer2);  //add to scene 

	//auto PlayerCollider = std::make_shared<dae::ColliderComponent>();


	for (size_t i = 0; i < 38; i++)
	{
		for (size_t j = 0; j < 28; j++)
		{
			std::cout << "[" << j << ", " << i << ":" << dae::Renderer::GetInstance().Map[i][j] << "]";
		}
		std::cout << "\n";
	}




	//Keyboard
	auto keyboard{ input.GetKeyboard() };   //second uses keyboard 

	//Key down   // UP,DOWN, RIGHT ,LEFT ONE TAP
	direction = { 0.f,-setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_UP, std::move(pMoveCommand), dae::ButtonState::Up);  //changed it here 

	direction = { 0.f,setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_DOWN, std::move(pMoveCommand), dae::ButtonState::Up);

	direction = { -setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_LEFT, std::move(pMoveCommand), dae::ButtonState::Up);

	direction = { setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_RIGHT, std::move(pMoveCommand), dae::ButtonState::Up);
	//Key pressed SMOOTH A W S D 

	direction = { 0.f,-updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };

	// std::move so it does not copy it 
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
	controller = { input.AddController() };  //add second controller 

	//Button down
	direction = { 0.f,-setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonY, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { 0.f,setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { -setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonX, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonB, std::move(pMoveCommand), dae::ButtonState::Down);

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

	//that is it folks 

	auto Hero = std::make_shared<dae::GameObject>();
	auto HeroRender = std::make_shared<dae::RenderComponent>(-2,true);  //enum class 
	HeroRender->SetTexture("Hero.png");
	HeroRender->SetDimension(1.f);   ///not used for now 
	//void AddVector , enum class 
	HeroRender->AddToVector(6,5,4, 7, dae::AnimationComponent::Type::loop, 0,3);







	Hero->AddComponent(HeroRender);
	Hero->SetPosition(210, 100);  //keep this  game objects sets pos
	scene.Add(Hero);

	auto ImGuiGameObject = std::make_shared<dae::GameObject>();
	auto iamguiComponent = std::make_shared<dae::StartInfoComponent>();
	ImGuiGameObject->AddComponent(iamguiComponent);
	scene.Add(ImGuiGameObject);

	

	


}



void Scene2()
{

	//auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Scene2");  //creaate scene 

	//auto sherkGameObject = std::make_shared<dae::GameObject>();
	//auto shrekRender = std::make_shared<dae::RenderComponent>(-2, false);
	//shrekRender->SetTexture("R.png");
	//shrekRender->SetDimension(0.2f);
	//sherkGameObject->AddComponent(shrekRender);
	//sherkGameObject->SetPosition(210, 200);  //keep this  game objects sets pos
	//scene2.Add(sherkGameObject);


}

	void load()
	{
	


		
		Scene1();

		
		
			Scene2();
		


		





		


	}

	int main(int, char* []) {
		dae::Minigin engine("../Data/");
		engine.Run(load);
		return 0;
	}















































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
