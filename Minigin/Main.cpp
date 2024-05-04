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


#include"SoundSystem.h"
#include"Audio.h"
#include"LoggingSystem.h"
#include"SDL_SoundSystem.h"
#include"LoggingSoundSystem.h"
#include"ColliderComponent.h"
#include"TestCommand.h"
#include"staticHeader.h"




void CreateButton(dae::Scene& scene, const std::string& message, float x, float y);
void CreateMap(dae::Scene & scene);
void CreateGhost(dae::Scene& scene, const std::string& ghostTextureName, float x,float y);
void AddKeyBoard(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command> & pMoveCommand, float speed);
void AddKeyBoard2(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command>& pMoveCommand, float speed);
std::shared_ptr<dae::GameObject> CreatePlayer(const std::string& fileName, float scale, dae::Scene& scene, float x, float y, const int & state);

static int s_GameSoundId{};   //id of music
static int s_MenuMusicId{};  //
static int s_EndMusicId{};



enum class CurrentPlayer
{

	Pacman,
	MrsPacman

};


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


	SetSceneCommand = std::make_unique<dae::TestCommand>();
	keyboard2->MapCommandToButton(SDL_SCANCODE_9, std::move(SetSceneCommand), dae::ButtonState::Up);






	//make command to mute 

	auto & MenuScene = dae::SceneManager::GetInstance().CreateScene("MenuScene");

	// intro image 
	auto MapGameObject = std::make_shared<dae::GameObject>();
	auto MapRender = std::make_shared<dae::RenderComponent>(0,-1, false);  //use false so Null
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
	//clear controlls
	//game mode 

	float setSpeed{ 50.f };

	auto& scene = dae::SceneManager::GetInstance().CreateScene("CoOpScene");  //creaate scene   
	auto& input = dae::InputManager::GetInstance();


	CreateMap(scene);


	auto player = CreatePlayer("pacman204x85px.png", 1.5f, scene,100,155,m_pacmanState);     //this does not have last version of pacman with collision component it is under development 


	////Y negative 
	glm::vec3 direction{};                          //gets a game object 
	std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::UpdatePositionCommand>(player.get(), direction,int(CurrentPlayer::Pacman))};  //player 1 and direction

	AddKeyBoard(input, player, pMoveCommand, setSpeed);

	//
	////add Controller1

	//
	auto player2 = CreatePlayer("mrspackman.png",0.35f, scene,100,200,m_MrsPacmanState);     //this does not have last version of pacman with collision component it is under development 

	glm::vec3 direction3{};
	pMoveCommand = std::make_unique<dae::UpdatePositionCommand>(player2.get(), direction3, int(CurrentPlayer::MrsPacman));
	AddKeyBoard2(input, player2, pMoveCommand, setSpeed);

	//AddController2

	//float updateSpeed{ 50.f };

	//auto pPlayer1 = std::make_shared<dae::GameObject>();
	//auto pPlayer1Renderer = std::make_shared<dae::RenderComponent>(-1, true);
	//pPlayer1Renderer->SetTexture("mrspackman.png");
	//pPlayer1Renderer->SetDimension(0.35f);
	//pPlayer1Renderer->AddToVector(5, 12, 12, 7, dae::AnimationComponent::Type::loop, 1, 0);   //dead
	//pPlayer1Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);  //right 
	//pPlayer1Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//left 
	//pPlayer1Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 3);//up
	//pPlayer1Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 4);//down
	//pPlayer1->SetPosition(8, 32);
	//pPlayer1->AddComponent(pPlayer1Renderer);
	//pPlayer1->SetPosition(100, 100);
	//scene.Add(pPlayer1);



	//glm::vec3 direction2{ 0.f,-updateSpeed,0.f };
	//std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction2) };
	//AddKeyBoard2(input, pPlayer1, pMoveCommand);






	/////////////////////////////////////////////


	//auto controller{ input.AddController() };

	//glm::vec3 direction{ 0.f,-updateSpeed,0.f };
	//std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };  //player 1 and direction 

	//direction = { 0.f,-updateSpeed,0.f };
	//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	//controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadUp, std::move(pMoveCommand), dae::ButtonState::Pressed);

	//direction = { 0.f,updateSpeed,0.f };
	//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	//controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadDown, std::move(pMoveCommand), dae::ButtonState::Pressed);

	//direction = { -updateSpeed,0.f,0.f };
	//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	//controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadLeft, std::move(pMoveCommand), dae::ButtonState::Pressed);

	//direction = { updateSpeed,0.f,0.f };
	//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	//controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadRight, std::move(pMoveCommand), dae::ButtonState::Pressed);
	//

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//pacman
	//auto pPlayer2 = std::make_shared<dae::GameObject>();
	//auto pPlayer2Renderer = std::make_shared<dae::RenderComponent>(0,-1, true);
	//pPlayer2Renderer->SetTexture("pacman204x85px.png");
	//pPlayer2Renderer->SetDimension(1.5f);
	//pPlayer2Renderer->AddToVector(5, 12, 12,7, dae::AnimationComponent::Type::loop, 1, 0);   //dead
	//pPlayer2Renderer->AddToVector(5, 12, 2,7, dae::AnimationComponent::Type::loop, 1, 1);  //right 
	//pPlayer2Renderer->AddToVector(5, 12, 2,7, dae::AnimationComponent::Type::loop, 1, 2);//left 
	//pPlayer2Renderer->AddToVector(5, 12, 2,7, dae::AnimationComponent::Type::loop, 1, 3);//up
	//pPlayer2Renderer->AddToVector(5, 12, 2,7, dae::AnimationComponent::Type::loop, 1, 4);//down
	//pPlayer2->AddComponent(pPlayer2Renderer);

	//    

	////add here the pellets ,ghots , 
	//std::vector<dae::Object> shapes = dae::Map::GetInstance().GetShapes();

	////use STL algoritms to add the other part of the vector 

	//auto PlayerCollider = std::make_shared<dae::ColliderComponent>(pPlayer2, shapes);  //make header here 
	//pPlayer2->AddComponent(PlayerCollider);
	//pPlayer2->SetPosition(100, 200);    //thisfrist ?
	//scene.Add(pPlayer2);

	//

	//AddKeyBoard(input, pPlayer2, pMoveCommand);







	////Controller nr 2
	//controller = { input.AddController() };

	////Button pressed
	//direction = { 0.f,-updateSpeed,0.f };
	//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	//controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadUp, std::move(pMoveCommand), dae::ButtonState::Pressed);

	//direction = { 0.f,updateSpeed,0.f };
	//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	//controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadDown, std::move(pMoveCommand), dae::ButtonState::Pressed);

	//direction = { -updateSpeed,0.f,0.f };
	//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	//controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadLeft, std::move(pMoveCommand), dae::ButtonState::Pressed);

	//direction = { updateSpeed,0.f,0.f };
	//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	//controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadRight, std::move(pMoveCommand), dae::ButtonState::Pressed);


	////////////////////////////////////////////////



	auto PinkGhostGameObject = std::make_shared<dae::GameObject>();
	auto PinkGhostRenderer = std::make_shared<dae::RenderComponent>(m_GhostState,-1, true);
	PinkGhostRenderer->SetTexture("pink.png");
	PinkGhostRenderer->SetDimension(1.6f);
	PinkGhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
	PinkGhostRenderer->AddToVector(3,2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
	PinkGhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
	PinkGhostGameObject->SetPosition(8,32);
	PinkGhostGameObject->AddComponent(PinkGhostRenderer);

	auto AiComponent = std::make_shared<dae::AIComponent>(PinkGhostGameObject, player);  // Puede tomar un game object 
	PinkGhostGameObject->AddComponent(AiComponent);
	scene.Add(PinkGhostGameObject);






	////////////////////////////////////////////////////////////////////////////////////////////////////

	//this ones	LACK Ai component and the state machine 

	//function will take the state machine and then the  Ai type


//just ghost no ai 
	CreateGhost(scene, "BlueGhost.png", 32, 64);
	CreateGhost(scene, "red.png",64,32);
	CreateGhost(scene, "yellow.png",160,32);





}



void LoadSinglePlayerMode()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("SinglePlayerScene");  //creaate scene   

	CreateMap(scene);

	auto player = CreatePlayer("pacman204x85px.png", 1.5f, scene,32,87,m_pacmanState);

	//no input yet 


}

void LoadScoresScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("ScoresScene");  //creaate scene   
	CreateButton(scene, "Players Score",70,30);


}

void LoadVersusMode()
{

	// clean input 

	//auto& input = dae::InputManager::GetInstance();

	//input.ClearCommands();

	auto & scene = dae::SceneManager::GetInstance().CreateScene("VersusMode");  //creaate scene   
	CreateMap(scene);



	auto player = CreatePlayer("pacman204x85px.png", 1.5f, scene,32,32,m_pacmanState);     //this does not have last version of pacman with collision component it is under development 



	//uncommn
	//float updateSpeed = 100.f;
//	glm::vec3 direction2{};
	//std::unique_ptr<dae::Command> pMoveCommand2{ std::make_unique<dae::UpdatePositionCommand>(player.get(), direction2)};

	//AddKeyBoard(input, player, pMoveCommand2, updateSpeed);






	//auto player2 = CreatePlayer("pacman204x85px.png", 1.5f, scene,64,64);     //this does not have last version of pacman with collision component it is under development 

	//float updateSpeed2 = 100.f;
	//glm::vec3 direction3{ 0.f,-updateSpeed2,0.f };
	//std::unique_ptr<dae::Command> pMoveCommand3{ std::make_unique<dae::UpdatePositionCommand>(player2.get(), direction3) };

	//AddKeyBoard2(input, player2, pMoveCommand3);



	//AddKeyBoard2()  fro ghost 


	//add keybaoerd and control to apcman and ghost 

	//CreateGhost(scene, "BlueGhost.png",32,64);

}

void load()
{
#if _DEBUG
	dae::Audio::RegisterService(std::make_unique<dae::SDL_SoundSystem>());
#else
	dae::Audio::RegisterService(std::make_unique<dae::SDL_SoundSystem>());

#endif
	

	dae::SoundSystem& audio{ dae::Audio::Get() };

	audio.AddSound("Music/pac-man.mp3", s_GameSoundId, true);


	audio.Play(s_GameSoundId, 1.f,100);

	LoadScoresScene();  //notthinbg here yet 
	LoadVersusMode();   //nothing here 
	LoadCoOpScene();  ////nothing here 
	LoadSinglePlayerMode();  //nothing here yet
	LoadMenuScene();

	//////////////
	// 
	// 
	// 
	// 
	// IIIIIIMMMMPORTANTEEEEEEEEEEEEEEEEEEEEE
	// 
	//maybe remember to clear the controllers 
	// and use game manager to control 
	//use game manager to load this according to d


	//los puntos del mapa simepre se dibujan y ademas 


	// no se si habara problema cuando se anadan mismos personajes  o controles  como teclado etc 


}


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


void CreateGhost(dae::Scene & scene,const std::string & ghostTextureName,float x,float y)
{


	//can amke the position a parameter 

	auto GhostGameObject = std::make_shared<dae::GameObject>();

	auto GhostRenderer = std::make_shared<dae::RenderComponent>(m_GhostState,3, true);
	GhostRenderer->SetTexture(ghostTextureName);
	GhostRenderer->SetDimension(1.6f);
	GhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
	GhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
	GhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
	GhostGameObject->SetPosition(x,y);
	GhostGameObject->AddComponent(GhostRenderer);
	scene.Add(GhostGameObject);



}

void CreateMap(dae::Scene & scene)
{
	auto MapGameObject = std::make_shared<dae::GameObject>();

	auto MapRender = std::make_shared<dae::RenderComponent>(0,-1, false);    //this one has tl take my animation class 
	MapRender->SetTexture("Map.png");
	MapRender->SetDimension(2.f);
	MapGameObject->AddComponent(MapRender);
	MapGameObject->SetPosition(0, 0);
	scene.Add(MapGameObject);

}





void AddKeyBoard(dae::InputManager & input,std::shared_ptr<dae::GameObject> & Player, std::unique_ptr<dae::Command> & pMoveCommand,float speed)
{

	float updateSpeed{speed};
	auto keyboard{ input.GetKeyboard() };

	glm::vec3 direction{ 0.f,-updateSpeed,0.f};   //

	direction = { 0.f,-updateSpeed,3};
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman)) };
	keyboard->MapCommandToButton(SDL_SCANCODE_W, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,4};
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman))};
	keyboard->MapCommandToButton(SDL_SCANCODE_S, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,2};
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman))};
	keyboard->MapCommandToButton(SDL_SCANCODE_A, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,1};
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman))};
	keyboard->MapCommandToButton(SDL_SCANCODE_D, std::move(pMoveCommand), dae::ButtonState::Pressed);


}

void AddKeyBoard2(dae::InputManager & input, std::shared_ptr<dae::GameObject> & Player, std::unique_ptr<dae::Command>& pMoveCommand,float speed)
{


	float updateSpeed{ speed };


	auto keyboard{ input.GetKeyboard() };

	glm::vec3 direction{ 0.f,-updateSpeed,0};   //use the z value of it 


	
	direction = { 0.f,-updateSpeed,3};
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman))};    //set pacman vraible up
	keyboard->MapCommandToButton(SDL_SCANCODE_UP, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,4};
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman))};
	keyboard->MapCommandToButton(SDL_SCANCODE_DOWN, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,2};
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman))};
	keyboard->MapCommandToButton(SDL_SCANCODE_LEFT, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,1};
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman))};
	keyboard->MapCommandToButton(SDL_SCANCODE_RIGHT, std::move(pMoveCommand), dae::ButtonState::Pressed);


}



std::shared_ptr<dae::GameObject> CreatePlayer(const std::string& fileName, float scale,dae::Scene & scene,float x,float y,const int  & state)   //add parameter 
{

	//to have different id 

	auto pPlayer2 = std::make_shared<dae::GameObject>();
	auto pPlayer2Renderer = std::make_shared<dae::RenderComponent>(state,-1, true);
	pPlayer2Renderer->SetTexture(fileName);
	pPlayer2Renderer->SetDimension(scale);
	pPlayer2Renderer->AddToVector(5, 12, 12, 7, dae::AnimationComponent::Type::loop, 1, 0);   //dead
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);  //right    //1
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//left   //2
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 3);//up //2
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 4);//down
	pPlayer2->AddComponent(pPlayer2Renderer);
	//std::vector<dae::Object> & shapes = dae::Map::GetInstance().GetShapes();
	//use STL algoritms to add the other part of 
	// 
	// the vector was empty was a copy not a reference of the map that is why it did not modified the other one 

	auto PlayerCollider = std::make_shared<dae::ColliderComponent>(pPlayer2, dae::Map::GetInstance().GetShapes());  //make header here 
	pPlayer2->AddComponent(PlayerCollider);
	pPlayer2->SetPosition(x,y);
	scene.Add(pPlayer2);


	return  pPlayer2;




}




//std::shared_ptr<dae::GameObject> CreateGhostPlayer(dae::Scene& scene, const std::string& ghostTextureName, float x, float y)
//{
//
//
//	auto GhostGameObject = std::make_shared<dae::GameObject>();
//	auto GhostRenderer = std::make_shared<dae::RenderComponent>(3, true);
//	GhostRenderer->SetTexture(ghostTextureName);
//	GhostRenderer->SetDimension(1.6f);
//	GhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
//	GhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
//	GhostRenderer->AddToVector(3, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
//	GhostGameObject->SetPosition(x, y);
//	GhostGameObject->AddComponent(GhostRenderer);
//	scene.Add(GhostGameObject);
//
//	return GhostGameObject;
//
//}





//pacmn keyboard 


//auto keyboard{ input.GetKeyboard() };

//direction = { 0.f,-updateSpeed,0.f };
//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
//keyboard->MapCommandToButton(SDL_SCANCODE_W, std::move(pMoveCommand), dae::ButtonState::Pressed);

//direction = { 0.f,updateSpeed,0.f };
//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
//keyboard->MapCommandToButton(SDL_SCANCODE_S, std::move(pMoveCommand), dae::ButtonState::Pressed);

//direction = { -updateSpeed,0.f,0.f };
//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
//keyboard->MapCommandToButton(SDL_SCANCODE_A, std::move(pMoveCommand), dae::ButtonState::Pressed);

//direction = { updateSpeed,0.f,0.f };
//pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
//keyboard->MapCommandToButton(SDL_SCANCODE_D, std::move(pMoveCommand), dae::ButtonState::Pressed);


















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
