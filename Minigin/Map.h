#pragma once

#include <SDL.h>
#include"Singleton.h"
#include<vector>
#include"Component.h"
#include"string"
#include<vector>
#include"ObjectHeader.h"


namespace dae

{

	class Map : public Singleton<Map>
	{

	public:

		Map();

	
		void DrawMap();
		void UpdateMap();
			
	
		SDL_Color m_Black{ 0,0,0,255 };
		SDL_Color m_White{ 255,255,255,255 };
		SDL_Color m_Red{ 255,0,0,255 };
		SDL_Color m_PowerUpColor{ m_Black };
		SDL_Color m_PelletColor{ SDL_Color{ 255,192,203,255}};


		std::vector<Object> m_PelletsAndPowerUp;   //make a struct with ID to know which one is power Up 
		std::vector<Object> & GetShapes();

		static int MapArray[36][28];
		void parseMapFile(const std::string& filename);



	};

};