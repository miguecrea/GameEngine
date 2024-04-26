#pragma once

#include <memory>
#include <string>
#include "Scene.h"
#include <functional>
#include <glm/glm.hpp>
#include"SDL.h"


namespace dae
{
	

	struct Point2f

	{
		int x, y;
	};



	void CreateButton(Scene& scene, const glm::vec2& position, const std::string& text, int fontSize);


	// load level from file 

	
}