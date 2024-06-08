#pragma once

#include"InputManager.h"
#include"GameObject.h"
#include"UpdatePositionCommand.h"
#include <memory>







enum class CurrentPlayer
{

	Pacman,
	MrsPacman,
	Ghost

};





void AddKeyBoard(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command>& pMoveCommand, float speed)
{

	float updateSpeed{ speed };
	auto keyboard{ input.GetKeyboard() };

	glm::vec3 direction{ 0.f,-updateSpeed,0.f };   //

	direction = { 0.f,-updateSpeed,3 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman)) };
	keyboard->MapCommandToButton(SDL_SCANCODE_W, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,4 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman)) };
	keyboard->MapCommandToButton(SDL_SCANCODE_S, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,2 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman)) };
	keyboard->MapCommandToButton(SDL_SCANCODE_A, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,1 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::Pacman)) };
	keyboard->MapCommandToButton(SDL_SCANCODE_D, std::move(pMoveCommand), dae::ButtonState::Pressed);


}

void AddKeyBoard2(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command>& pMoveCommand, float speed)
{
	float updateSpeed{ speed };
	auto keyboard{ input.GetKeyboard() };

	glm::vec3 direction{ 0.f,-updateSpeed,0 };   //use the z value of it 

	direction = { 0.f,-updateSpeed,3 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman)) };    //set pacman vraible up
	keyboard->MapCommandToButton(SDL_SCANCODE_UP, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,4 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman)) };
	keyboard->MapCommandToButton(SDL_SCANCODE_DOWN, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,2 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman)) };
	keyboard->MapCommandToButton(SDL_SCANCODE_LEFT, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,1 };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(Player.get(), direction,int(CurrentPlayer::MrsPacman)) };
	keyboard->MapCommandToButton(SDL_SCANCODE_RIGHT, std::move(pMoveCommand), dae::ButtonState::Pressed);


}




void AddController1(dae::InputManager& input, std::shared_ptr<dae::GameObject>& Player, std::unique_ptr<dae::Command>& pMoveCommand, float speed)
{
	float updateSpeed{ speed };
	auto controller{ input.AddController() };

	glm::vec3 direction{ 0.f,-updateSpeed,0 };   //use the z value of it 

	direction = { 0.f,-updateSpeed,3 };
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