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

		static int MapArray[36][28];
	
		void DrawMap();
		void UpdateMap();
		void ResetMap();
			
	
		SDL_Color m_Black{ 0,0,0,255 };
		SDL_Color m_White{ 255,255,255,255 };
		SDL_Color m_Red{ 255,0,0,255 };
		SDL_Color m_PowerUpColor{ m_Black };
		SDL_Color m_PelletColor{ SDL_Color{ 255,192,203,255}};
		std::tuple<int, int> GridToPos(int row, int col);

		std::vector<std::tuple<int, int>> m_ValidIndexes{};
		std::vector<std::tuple<int, int>> & ReturnValidIndexes();
		std::vector<Object> m_PelletsAndPowerUp;   
		std::vector<Object> & GetShapes();

		static int MapArray2[36][28];
		void parseMapFile(const std::string& filename);


		int rowTest{};
		int Column{};


	};

};