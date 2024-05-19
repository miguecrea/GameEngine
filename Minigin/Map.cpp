#include "Map.h"
#include"Renderer.h"
#include"SceneManager.h"
#include <fstream>
#include <sstream>
#include <iostream> // For std::cerr
#include <stdexcept>
#include<filesystem>



 int dae::Map::MapArray[36][28] = {
    1, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
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
	1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 1, 1, 1, 4, 4, 1, 1, 1, 4, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 1, 4, 4, 4, 4, 4, 4, 1, 4, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 4, 4, 4, 4, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 1, 4, 4, 4, 4, 4, 4, 1, 4, 1, 1, 0, 1, 1, 1, 1, 1, 1,
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

 int dae::Map::MapArray2[36][28] = {};

dae::Map::Map()
{
	std::cout<<std::filesystem::current_path()<<"\n";


	parseMapFile("Map.txt");


	for (int colums = 0; colums < 36; colums++)
	{
		for (int rows = 0; rows < 28; rows++)                     
		{
			std::cout << MapArray[colums][rows] << ",";

		}

		std::cout << "\n";
	}




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





	///// BORAR ESTO DESPUES

	float PosX{}, PosY{}, width{ 16 };
	for (int colums = 0; colums < 36; colums++)
	{
		for (int rows = 0; rows < 28; rows++)                     //code rusn first 
		{
			SDL_Color color{255,0,0,80};
		

				Renderer::GetInstance().DrawSquare(PosX + width * rows, PosY + width * colums, width, color);

		}


	}

	auto test = Map::GetInstance().GridToPos(Column,rowTest);     //column //then row 
	auto orange1 = Map::GetInstance().GridToPos(20,26);     //column //then row 
	auto orange2 = Map::GetInstance().GridToPos(26,30);     //column //then row 


	auto orange3 = Map::GetInstance().GridToPos(15,32);     //column //then row 

	auto orange4 = Map::GetInstance().GridToPos(12,12);     //column //then row 






	int roww  = std::get<0>(test);
	int column  = std::get<1>(test);

	Renderer::GetInstance().FillSquare(float(roww)*2,float(column)*2, 16, 16, SDL_Color{0,0,0,255});   //renderizo mal 

	Renderer::GetInstance().FillSquare(float(std::get<0>(orange1))*2,float(std::get<1>(orange1))*2, 16, 16, SDL_Color{0,0,255,255});   
	Renderer::GetInstance().FillSquare(float(std::get<0>(orange2))*2,float(std::get<1>(orange2))*2, 16, 16, SDL_Color{0,0,255,255});   
	Renderer::GetInstance().FillSquare(float(std::get<0>(orange3))*2,float(std::get<1>(orange3))*2, 16, 16, SDL_Color{255,0,255,255});   
	Renderer::GetInstance().FillSquare(float(std::get<0>(orange4))*2,float(std::get<1>(orange4))*2, 16, 16, SDL_Color{255,0,255,255});   









}

void dae::Map::UpdateMap()
{

	for (size_t i = 0; i < m_PelletsAndPowerUp.size(); i++)
	{
		m_PelletsAndPowerUp[i].Update();  //color was just getting spawmned here 

	}

}

void dae::Map::ResetMap()
{

	for (size_t i = 0; i < m_PelletsAndPowerUp.size(); i++)
	{
		m_PelletsAndPowerUp[i].m_collisionPreset = dae::Collision::CanCollide;
		m_PelletsAndPowerUp[i].color.a = 255;
	}
}

std::tuple<int, int> dae::Map::GridToPos(int  row, int  col)
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
	std::string line;
	int row = 0;

	while (std::getline(file, line) && row < 36) { // Read each line of the file
		std::istringstream iss(line);
		std::string token;
		int col = 0;

		while (std::getline(iss, token, ',')) { // Tokenize each line by comma
			MapArray2[row][col++] = std::stoi(token); // Convert token to int and fill MapArray2
		}

		row++;
	}











}

