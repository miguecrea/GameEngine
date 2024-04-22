#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Controller.h"
#include "Keyboard.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>   //make it  a singletonm    
	{
	public:
		InputManager();
		void ClearCommands();
		bool ProcessInput();
		Controller * AddController();  //add controller there cna be 2  
		Keyboard * GetKeyboard();  //there is only one keybaord right ?

	private:
		std::vector<std::unique_ptr<Controller>> m_pControllers{};
		Keyboard m_Keyboard;
	};

}
