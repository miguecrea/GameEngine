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
#include"Map.h"
#include"NextSceneCommand.h"




void CreateButton(dae::Scene& scene, const std::string& message, float x, float y);
void CreateMap(dae::Scene & scene);
void CreateGhost(dae::Scene& scene, const std::string& ghostTextureName);





void LoadDotComponent()
{


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
	auto& input2 = dae::InputManager::GetInstance();


	auto keyboard2{ input2.GetKeyboard() };

	std::unique_ptr<dae::Command> SetSceneCommand{ std::make_unique<dae::NextSceneCommand>("SinglePlayerScene",GameMode::SinglePlayer) };// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_1, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::NextSceneCommand>("CoOpScene", GameMode::Coop);
	keyboard2->MapCommandToButton(SDL_SCANCODE_2, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::NextSceneCommand>("VersusMode", GameMode::Versus);
	keyboard2->MapCommandToButton(SDL_SCANCODE_3, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::NextSceneCommand>("ScoresScene", GameMode::PlayerScores);
	keyboard2->MapCommandToButton(SDL_SCANCODE_4, std::move(SetSceneCommand), dae::ButtonState::Up);















	auto& MenuScene = dae::SceneManager::GetInstance().CreateScene("MenuScene");

	auto ImGuiGameObject = std::make_shared<dae::GameObject>();
	auto iamguiComponent = std::make_shared<dae::StartInfoComponent>();
	ImGuiGameObject->AddComponent(iamguiComponent);
	ImGuiGameObject->SetPosition(100, 200);
	MenuScene.Add(ImGuiGameObject);



	auto MapGameObject = std::make_shared<dae::GameObject>();
	auto MapRender = std::make_shared<dae::RenderComponent>(-1, false);  //use false so Null
	MapRender->SetTexture("pac.png");
	MapRender->SetDimension(2.f);
	MapGameObject->AddComponent(MapRender);
	MapGameObject->SetPosition(-7, -20);
	MenuScene.Add(MapGameObject);


	float xPos{20};
	float yPos{ 170 };
	float Offset{ 20 };
	CreateButton(MenuScene, "SinglePlayer - Press 1", xPos, yPos);
	yPos += Offset;
	CreateButton(MenuScene, "CoperativeMode - Press 2", xPos, yPos);
	yPos += Offset;
	CreateButton(MenuScene, "VersusMode- Press 3 ", xPos, yPos);
	yPos += Offset;
	CreateButton(MenuScene, "PlayersScore - Press 4 ", xPos, yPos);



}



void LoadCoOpScene()
{


	auto& scene = dae::SceneManager::GetInstance().CreateScene("CoOpScene");  //creaate scene   

	auto& input = dae::InputManager::GetInstance();



	//float scale{2.f}
		  //pacman Map
		//mapa //ventana estan por 2 ,  
		//tambine mis posiciones estan x2 
		//un poco de harcode el el command tambien 
		//check the render aswell 
	////////////////////////////////////////

	//deberia renderizar los puntos   // la imagen todavia no la puse 
	//en caso de joder hacer el mapa estatico otra vez y despues llamarlo en el scene manager 





	CreateMap(scene);







	float setSpeed{ 10.f };
	float updateSpeed{ 100.f };


	

	/////////////////////////////////////////////////////////////
	///mrs pacman


	auto pPlayer1 = std::make_shared<dae::GameObject>();
	auto pPlayer1Renderer = std::make_shared<dae::RenderComponent>(-1, true);
	pPlayer1Renderer->SetTexture("mrspackman.png");
	pPlayer1Renderer->SetDimension(0.35f);
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
	PinkGhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
	PinkGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
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
	RedGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
	RedGhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
	RedGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
	RedGhostGameObject->SetPosition(8, 64);
	RedGhostGameObject->AddComponent(RedGhostRenderer);
	scene.Add(RedGhostGameObject);





	auto YellowGhostGameObject = std::make_shared<dae::GameObject>();
	auto YellowGhostRenderer = std::make_shared<dae::RenderComponent>(3, true);
	YellowGhostRenderer->SetTexture("yellow.png");
	YellowGhostRenderer->SetDimension(1.6f);
	YellowGhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
	YellowGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
	YellowGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
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



void LoadSinglePlayerMode()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("SinglePlayerScene");  //creaate scene   

	CreateMap(scene);

	auto pPlayer2 = std::make_shared<dae::GameObject>();
	auto pPlayer2Renderer = std::make_shared<dae::RenderComponent>(-1, true);
	pPlayer2Renderer->SetTexture("pacman204x85px.png");
	pPlayer2Renderer->SetDimension(1.5f);
	pPlayer2Renderer->AddToVector(5,12,12,7, dae::AnimationComponent::Type::loop, 1,0);   //dead
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);  //right 
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//left 
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 3);//up
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 4);//down
	pPlayer2->AddComponent(pPlayer2Renderer);
	pPlayer2->SetPosition(100, 200);
	scene.Add(pPlayer2);


}

void LoadScoresScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("ScoresScene");  //creaate scene   
	CreateButton(scene, "Players Score",70,30);


}

void LoadVersusMode()
{

	auto & scene = dae::SceneManager::GetInstance().CreateScene("VersusMode");  //creaate scene   


	CreateMap(scene);




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


	
	//CreateGhost(scene, "pink.png");
	CreateGhost(scene, "BlueGhost.png");
	//CreateGhost(scene, "red.png");
	//CreateGhost(scene, "yellow.png");







}
void load()
{
	//auto & manager = dae::PacmanManager::GetInstance();


	//auto GameMode = manager.GetMode();   //this is not a refernce 




	//////////////
	// 
	// 
	// 
	// 
	// IIIIIIMMMMPORTANTEEEEEEEEEEEEEEEEEEEEE
	// 
	// 
	// 
	// 
	// 
	// 
	//maybe remember to clear the controllers 
	// and use game manager to control 
	//use game manager to load this according to 


	//los puntos del mapa simepre se dibujan y ademas 


	// no se si habara problema cuando se anadan mismos personajes  o controles  como teclado etc 


	LoadScoresScene();  //notthinbg here yet 
	LoadVersusMode();   //nothing here 
	LoadCoOpScene();  ////nothing here 
	LoadSinglePlayerMode();  //nothing here yet
	LoadMenuScene();





	





}




// crate player  with bindings


int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}




void CreateButton(dae::Scene& scene,const std::string& message,float x ,float y)
{

	auto TextGameObject = std::make_shared<dae::GameObject>();
	auto RenderComponentforText = std::make_shared<dae::RenderComponent>(-1, false);
	TextGameObject->AddComponent(RenderComponentforText);

	auto TextComponent = std::make_shared<dae::TextComponent>(RenderComponentforText);

	const int size{ 35 };
	TextComponent->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", size));
	TextComponent->SetColor(SDL_Color{ dae::Map::GetInstance().m_White });
	TextComponent->SetTextToTexture(message);
	TextGameObject->AddComponent(TextComponent);
	TextGameObject->SetPosition(x,y);

	scene.Add(TextGameObject);


}


void CreateGhost(dae::Scene & scene,const std::string & ghostTextureName)
{


	//can amke the position a parameter 

	auto GhostGameObject = std::make_shared<dae::GameObject>();
	auto GhostRenderer = std::make_shared<dae::RenderComponent>(3, true);
	GhostRenderer->SetTexture(ghostTextureName);
	GhostRenderer->SetDimension(1.6f);
	GhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
	GhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
	GhostRenderer->AddToVector(3, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
	GhostGameObject->SetPosition(64, 32);
	GhostGameObject->AddComponent(GhostRenderer);
	scene.Add(GhostGameObject);



}

void CreateMap(dae::Scene & scene)
{
	auto MapGameObject = std::make_shared<dae::GameObject>();
	auto MapRender = std::make_shared<dae::RenderComponent>(-1, false);    //this one has tl take my animation class 
	MapRender->SetTexture("Map.png");
	MapRender->SetDimension(2.f);
	MapGameObject->AddComponent(MapRender);
	MapGameObject->SetPosition(0, 0);
	scene.Add(MapGameObject);

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
