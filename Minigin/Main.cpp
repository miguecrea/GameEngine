#include <SDL.h>
#include <iostream>
#include"FPSComponent.h"
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
#include"SceneManager.h"
#include"LivesComponent.h"



static const int mrspacman{ 2 };


void CreateButton(dae::Scene& scene, const std::string& message, float x, float y);
void CreateMap(dae::Scene & scene);
void CreateGhost(dae::Scene& scene, const std::string& ghostTextureName, float x,float y, std::shared_ptr<dae::GameObject> player, dae::GhostType Type, std::vector<std::shared_ptr<dae::GameObject>> & ghosts, bool isPlayer);
void AddKeyBoard(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command> & pMoveCommand, float speed);
void AddKeyBoard2(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command>& pMoveCommand, float speed);
std::shared_ptr<dae::GameObject> CreatePlayer(const std::string& fileName, dae::Scene& scene,float scale, float x, float y, const int & state);   //deleted scene from hefre 
void AddController1(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command>& pMoveCommand, float speed);
void AddController2(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command>& pMoveCommand, float speed);
void CreateHearth(dae::Scene& scene);
void CreateHud(bool IsScore, float x, float y, dae::Scene& scene);
void InitializeColliderComponent(std::shared_ptr<dae::GameObject>& Player, std::vector<std::shared_ptr<dae::GameObject>>& ghosts);






enum class CurrentPlayer
{

	Pacman,
	MrsPacman,
	Ghost

};



void  LoadMenuScene()
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


	//I think Ib why it needs a static because when the vraiable goes out of scope what happen tp that referemce so i KINDa know why 


	auto player = CreatePlayer("pacman204x85px.png", MenuScene, 5.f,50, 60, m_pacmanState);
	auto player2 = CreatePlayer("mrspackman.png", MenuScene, 1.f, 120,60, mrspacman);

	CreateHearth(MenuScene);

}



void LoadCoOpScene()
{
	//clear controlls
	//game mode 



	float setSpeed{ 30.f };

	auto& scene = dae::SceneManager::GetInstance().CreateScene("CoOpScene");  //creaate scene   
	auto& input = dae::InputManager::GetInstance();


	CreateMap(scene);

	std::vector<std::shared_ptr<dae::GameObject>> ghosts{};  //make with size 3


	auto player = CreatePlayer("pacman204x85px.png",scene, 1.5f,100,155,m_pacmanState);     //this does not have last version of pacman with collision component it is under development 


	////Y negative 
	glm::vec3 direction{};                        
	std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::UpdatePositionCommand>(player.get(), direction,int(CurrentPlayer::Pacman))};  //player 1 and direction

	AddKeyBoard(input, player, pMoveCommand, setSpeed);

	AddController1(input, player, pMoveCommand, setSpeed);

	auto player2 = CreatePlayer("mrspackman.png",scene,0.35f,100,200,m_MrsPacmanState);     



	glm::vec3 direction3{};
	pMoveCommand = std::make_unique<dae::UpdatePositionCommand>(player2.get(), direction3, int(CurrentPlayer::MrsPacman));
	AddKeyBoard2(input, player2, pMoveCommand, setSpeed);

	AddController2(input, player2, pMoveCommand, setSpeed);


	CreateGhost(scene, "BlueGhost.png", 88,128,player,dae::GhostType::Blue,ghosts,false); 
	CreateGhost(scene, "pink.png", 105, 128,player2, dae::GhostType::Pink,ghosts,false);
	CreateGhost(scene, "red.png",88,135,player2, dae::GhostType::Red,ghosts,false);
	CreateGhost(scene, "yellow.png",120,128,player, dae::GhostType::Orange,ghosts,false);

	InitializeColliderComponent(player,ghosts);   // gets outta scope remember if it was a reference 
	InitializeColliderComponent(player2, ghosts);   // gets outta scope remember if it was a reference 









}



void LoadSinglePlayerMode()
{

	auto& input = dae::InputManager::GetInstance();
	float  setSpeed = 30;

	
	auto& scene = dae::SceneManager::GetInstance().CreateScene("SinglePlayerScene");  

	CreateMap(scene);

	std::vector<std::shared_ptr<dae::GameObject>> ghosts{};  


	auto player = CreatePlayer("pacman204x85px.png", scene, 1.5f, 100, 160, m_pacmanState);  


	////Y negative 
	glm::vec3 direction{};
	std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::UpdatePositionCommand>(player.get(), direction,int(CurrentPlayer::Pacman)) }; 
	AddKeyBoard(input, player, pMoveCommand, setSpeed);

	AddController1(input, player, pMoveCommand, setSpeed);





	CreateGhost(scene, "BlueGhost.png", 88, 128, player, dae::GhostType::Blue, ghosts,false);
	CreateGhost(scene, "pink.png", 112, 128, player, dae::GhostType::Pink, ghosts,false);
	CreateGhost(scene, "red.png", 88, 135, player, dae::GhostType::Red, ghosts,false);
	CreateGhost(scene, "yellow.png", 120, 128, player, dae::GhostType::Orange, ghosts,false);



	InitializeColliderComponent(player, ghosts);  

	


}

void LoadScoresScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("ScoresScene");  //creaate scene   
	CreateButton(scene, "Players Score",70,30);


	CreateButton(scene, "Maximum Score is : 120",10,80);
	CreateButton(scene, "Maximum Score is : 120",10,100);
	CreateButton(scene, "Maximum Score is : 120",10,120);


}

void LoadVersusMode()
{
	float setSpeed{ 30 };
	auto& input = dae::InputManager::GetInstance();

	auto & scene = dae::SceneManager::GetInstance().CreateScene("VersusMode");  //creaate scene   
	CreateMap(scene);



	auto player = CreatePlayer("pacman204x85px.png", scene, 1.5f, 100, 155, m_pacmanState);

	std::vector<std::shared_ptr<dae::GameObject>> ghosts{};

	glm::vec3 direction{};
	std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::UpdatePositionCommand>(player.get(), direction,int(CurrentPlayer::Pacman)) };
	AddKeyBoard(input, player, pMoveCommand, setSpeed);

	AddController1(input, player, pMoveCommand, setSpeed);


	
	CreateGhost(scene, "red.png", 88, 135, player, dae::GhostType::Red, ghosts, true);


	

	InitializeColliderComponent(player, ghosts);

	//make a collider component that inherits from the other one and calls the function

	// MIssing ghots imput  keyboard and controllers

	//and logo to handle collisio with 2 players I guess the vector idea Is okey wwe will see 



}

void load()
{
#if _DEBUG
	dae::Audio::RegisterService(std::make_unique<dae::SDL_SoundSystem>());
#else
	dae::Audio::RegisterService(std::make_unique<dae::SDL_SoundSystem>());

#endif
	

	dae::SoundSystem& audio{ dae::Audio::Get() };

	audio.AddSound("pac-man-start-of-game-2.mp3",s_MenuMusicId,true);  
	audio.Play(s_GameSoundId, 0.5f,100);

	audio.AddSound("pacman_beginning.mp3",s_GameSoundId,true);  
	audio.Preload(s_CanEatGhots);
	audio.AddSound("pacman_canEatGhostMusic.mp3", s_CanEatGhots,false);   

	audio.Preload(s_PickUpPellet);
	audio.AddSound("pacman_eatfruit.mp3",s_PickUpPellet,false);   
	

	audio.Preload(s_DeathMusic);
	audio.AddSound("death_1.mp3", s_DeathMusic, false);   

	audio.Preload(s_AteGhostSound);
	audio.AddSound("pacman_eatghost.mp3", s_AteGhostSound, false);   


  // C++ a nonstatic member reference must be relative to a specific object
	 
    LoadMenuScene();


	//LoadCoOpScene();
	//LoadVersusMode();
	LoadScoresScene();  
	LoadSinglePlayerMode();  


    dae::SceneManager::GetInstance().SetCurrentScene("MenuScene");

 

}


int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}




void CreateButton(dae::Scene& scene,const std::string & message,float x ,float y)
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


void CreateGhost(dae::Scene & scene,const std::string & ghostTextureName,float x,float y,std::shared_ptr<dae::GameObject> player, dae::GhostType Type, std::vector<std::shared_ptr<dae::GameObject>> & ghosts,bool isPlayer)
{


	float setSpeed{ 30.f };

	auto GhostGameObject = std::make_shared<dae::GameObject>();

	auto GhostRenderer = std::make_shared<dae::RenderComponent>(m_GhostState,3, true);
	GhostRenderer->SetTexture(ghostTextureName);
	GhostRenderer->SetDimension(1.4f);
	GhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 0);  //nromal 
	GhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);//blue 
	GhostRenderer->AddToVector(3, 2, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//white 
	GhostGameObject->SetPosition(x,y);
	GhostGameObject->AddComponent(GhostRenderer);



	glm::vec3 direction{};
	std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::UpdatePositionCommand>(GhostGameObject.get(), direction,int(CurrentPlayer::Pacman))};  //player 1 and direction

	if (isPlayer)
	{
		AddKeyBoard2(dae::InputManager::GetInstance(), GhostGameObject, pMoveCommand, setSpeed);
	

		AddController2(dae::InputManager::GetInstance(), GhostGameObject, pMoveCommand, setSpeed);


	}
	else
	{
	auto AiComponent = std::make_shared<dae::AIComponent>(GhostGameObject, player,Type);  // Puede tomar un game object 
	GhostGameObject->AddComponent(AiComponent);

	}


	scene.Add(GhostGameObject);  //
	ghosts.push_back(GhostGameObject);   

	std::cout << "Number of ghosts: " << ghosts.size() << std::endl;


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

void CreateHearth(dae::Scene& scene)  //make 
{
	auto HearthGameObject = std::make_shared<dae::GameObject>();

	auto HearthRender = std::make_shared<dae::RenderComponent>(0, -1, false);    //this one has tl take my animation class 
	HearthRender->SetTexture("Hearth.png");
	HearthRender->SetDimension(0.07f);
	HearthGameObject->AddComponent(HearthRender);
	HearthGameObject->SetPosition(90,60);
	scene.Add(HearthGameObject);

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




void AddController1(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command>& pMoveCommand, float speed)
{
	float updateSpeed{ speed };
	auto controller{ input.AddController() };

	glm::vec3 direction{ 0.f,-updateSpeed,0 };   //use the z value of it 

	direction = { 0.f,-updateSpeed,3};
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman)) };    //set pacman vraible up
  controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadUp, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,4 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman)) };
    controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadDown, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,2 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman)) };
    controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadLeft, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,1 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman)) };
    controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadRight, std::move(pMoveCommand), dae::ButtonState::Pressed);


}




void AddController2(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command>& pMoveCommand, float speed)
{
	float updateSpeed{ speed };
	auto controller{ input.AddController() };

	glm::vec3 direction{ 0.f,-updateSpeed,0 };   //use the z value of it 

	direction = { 0.f,-updateSpeed,3 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman)) };    //set pacman vraible up
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadUp, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,4 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman)) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadDown, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,2 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman)) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadLeft, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,1 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman)) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadRight, std::move(pMoveCommand), dae::ButtonState::Pressed);



}

void InitializeColliderComponent(std::shared_ptr<dae::GameObject> & Player, std::vector<std::shared_ptr<dae::GameObject>>& ghosts)
{

	auto PlayerCollider = std::make_shared<dae::ColliderComponent>(Player, dae::Map::GetInstance().GetShapes(), ghosts);  //make header here 
	Player->AddComponent(PlayerCollider);


}




std::shared_ptr<dae::GameObject> CreatePlayer(const std::string& fileName,dae::Scene & scene, float scale,float x,float y,const int  & state)   //add parameter 
{



	//to have different id 

	auto pPlayer2 = std::make_shared<dae::GameObject>();
	auto pPlayer2Renderer = std::make_shared<dae::RenderComponent>(state,-1, true);
	pPlayer2Renderer->SetTexture(fileName);
	pPlayer2Renderer->SetDimension(scale);
	pPlayer2Renderer->AddToVector(5, 12, 12,3, dae::AnimationComponent::Type::loop, 1, 0);   //dead
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 1);  //right    //1
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 2);//left   //2
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 3);//up //2
	pPlayer2Renderer->AddToVector(5, 12, 2, 7, dae::AnimationComponent::Type::loop, 1, 4);//down
	pPlayer2->AddComponent(pPlayer2Renderer);



	CreateHud(true, 10, 10, scene);
	CreateHud(false, 100, 10, scene);




	pPlayer2->SetPosition(x,y);

	scene.Add(pPlayer2);


	return  pPlayer2;




}



void CreateHud(bool IsScore, float x, float y, dae::Scene& scene)

{

	auto HudGameObject = std::make_shared<dae::GameObject>();
	auto pFrameRateRenderer = std::make_shared<dae::RenderComponent>(0, -2);
	auto pTextComponent = std::make_shared<dae::TextComponent>(pFrameRateRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	pTextComponent->SetColor({ 200,200,0 });
	HudGameObject->AddComponent(pTextComponent);
	auto pFPSComponent = std::make_shared<dae::LivesConponent>(IsScore, HudGameObject->GetComponent<dae::TextComponent>());
	HudGameObject->AddComponent(pFrameRateRenderer);
	HudGameObject->AddComponent(pFPSComponent);
	HudGameObject->SetPosition(x,y);
	scene.Add(HudGameObject);




}



//std::vector<dae::Object> & shapes = dae::Map::GetInstance().GetShapes();
	//use STL algoritms to add the other part of 
	// 
	// the vector was empty was a copy not a reference of the map that is why it did not modified the other one 

	//auto PlayerCollider = std::make_shared<dae::ColliderComponent>(pPlayer2, dae::Map::GetInstance().GetShapes(),ghosts);  //make header here 
	//pPlayer2->AddComponent(PlayerCollider);