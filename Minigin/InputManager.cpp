#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"

using namespace dae;

InputManager::InputManager()
	:m_Keyboard{ SDL_GetKeyboardState(nullptr) }
{
}

void dae::InputManager::ClearCommands()
{
	m_Keyboard.ClearCommands();

	m_pControllers.clear();
}

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}

		//Key went up/down this frame
		if (e.key.repeat == 0)
		{
			m_Keyboard.Update(e);
		}

		//process event for ImGui
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	//Pressed keys
	m_Keyboard.UpdatePressed();

	//Update controllers
	for (auto& pController : m_pControllers)
	{
		pController->Update();
	}

	return true;
}

Controller * dae::InputManager::AddController()
{
	const int index{ static_cast<int>(m_pControllers.size()) };
	m_pControllers.push_back(std::make_unique<Controller>(index));

	return m_pControllers.back().get();
}

Keyboard* dae::InputManager::GetKeyboard()
{
	return &m_Keyboard;
}