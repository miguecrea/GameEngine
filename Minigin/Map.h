#pragma once

#include <SDL.h>
#include"Singleton.h"
#include<vector>
#include"Component.h"
#include"string"
#include<vector>


namespace dae

{

	class Map : public Singleton<Map>
	{

	public:

		Map();

		std::vector<std::pair<int, int>> m_positions; // Vector to store positions of something in world cordinates exmaple 2 2  where all the 2s ae 
	
	

		

		void DrawMap();
		void UpdateMap();
			
		


		SDL_Color m_Black{ 0,0,0,255 };
		SDL_Color m_White{ 255,255,255,255 };
		SDL_Color m_Red{ 255,0,0,255 };
		SDL_Color m_PowerUpColor{ m_Black };
		void ToogleColor();
		bool m_IsBlack = true;

		float m_TotalTimeElapsed{};

		std::vector<SDL_Rect> m_PelletsShape;   //make a struct with ID to know which one is power Up 




		static int MapArray[36][28];

		void parseMapFile(const std::string& filename);




	};

};