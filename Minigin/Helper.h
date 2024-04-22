#pragma once

#include <memory>
#include <string>
#include "Scene.h"
#include <functional>
#include <glm/glm.hpp>
#include"SDL.h"


namespace dae
{
	



	void CreateButton(Scene& scene, const glm::vec2& position, const std::string& text, int fontSize);

	SDL_Color m_Color2{255,0,0,255};

	// load level from file 

	
}