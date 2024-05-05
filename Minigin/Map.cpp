#include "Map.h"
#include"Renderer.h"
#include"SceneManager.h"
#include <fstream>
#include <sstream>
#include <iostream> // For std::cerr
#include <stdexcept>



 int dae::Map::MapArray[36][28] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
   ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
   ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
	1, 3, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 3, 1,
	1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1,
	1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 3, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 3, 1,
	1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
	1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1,
	1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
	1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };


                     //rows //columns
// int dae::Map::MapArray[36][28] = {};

dae::Map::Map()
{

	//parseMapFile("Map.txt");



	for (int colums = 0; colums < 36; colums++)
	{
		for (int rows = 0; rows < 28; rows++)                     //code rusn first 
		{

	        float  width{ 16 };
			float Posx = width * rows + 8;
			float PosY = width * colums + 8;

			int pelletSize{6};
			int powerUpSize{12};


		if (MapArray[colums][rows] == 0)   //where to put points 
		{

			m_PelletsAndPowerUp.push_back(Object{ SDL_Rect{int(Posx),int(PosY),pelletSize,pelletSize},dae::TypeOfObject::pellet}); //picked or not    //le haria falata el color 
			m_ValidIndexes.push_back(std::make_tuple(colums,rows)); 

			//maybe this is flipped rows and columns 
			
		}
		if (MapArray[colums][rows] == 3)  
		{

				m_PelletsAndPowerUp.push_back(Object{ SDL_Rect{int(Posx),int(PosY),powerUpSize,powerUpSize},dae::TypeOfObject::powerUp});  //unpicked state 
				
		}

		}
	}















}




void dae::Map::DrawMap()
{


	//ake them dissapear 

	//when all cleared win the game 

	//order depends on how you fill it      si es primero rows o columns llena la grid diferente 


	//for (int colums = 0; colums < 36; colums++)
	//{
	//	for (int rows = 0; rows < 28; rows++)                     //code rusn first 
	//	{
	//		
	//	//int currentIndex = colums * MAX_ROWS + rows;   //thislines will be different depending on what you put first columns or rows 

	//	}
	//}



	for (size_t i = 0; i < m_PelletsAndPowerUp.size(); i++)
	{
		m_PelletsAndPowerUp[i].Draw();
		
	}







	//float PosX{}, PosY{}, width{ 16 };
	//for (int colums = 0; colums < 36; colums++)
	//{
	//	for (int rows = 0; rows < 28; rows++)                     //code rusn first 
	//	{

	//		if (MapArray[colums][rows] == 0)   //where to put points 
	//		{

	//			//rows column to index 

	//		//	m_PelletsAndPowerUp[]

	//			//p object[de columnas y rows a index ].draw

	//			//Renderer::GetInstance().FillSquare(PosX + width * rows + 8, PosY + width * colums + 8, 6, m_PelletColor);

	//		}
	//		if (MapArray[colums][rows] == 3)  //power ups 

	//		{
	//			//Renderer::GetInstance().FillSquare(PosX + width * rows + 6, PosY + width * colums + 6, 12, m_PowerUpColor);

	//		}


	//		SDL_Color color{255,0,0,80};
	//		SDL_Color color2{255,255,255,80};
	//			Renderer::GetInstance().FillSquare(PosX + width * rows, PosY + width * colums, width, color);
	//			Renderer::GetInstance().DrawSquare(PosX + width * rows, PosY + width * colums, width, color2);


	//	}
	//}













}

void dae::Map::UpdateMap()
{

	for (size_t i = 0; i < m_PelletsAndPowerUp.size(); i++)
	{
		m_PelletsAndPowerUp[i].Update();  //color was just getting spawmned here 

	}

}

std::tuple<int, int> dae::Map::GridToPos(int row, int col)
{
	int Xpos = row * 8;
	int Ypos = col * 8;

	return std::make_tuple(Xpos, Ypos);
}
std::vector<std::tuple<int, int>> & dae::Map::ReturnValidIndexes()
{
	return m_ValidIndexes;
}
std::vector<dae::Object>& dae::Map::GetShapes()
{
	return m_PelletsAndPowerUp;
}

void dae::Map::parseMapFile(const std::string& filename)
{

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	// put in a vector of ints and then 

	//put each number om it 


	file.close(); 

}

