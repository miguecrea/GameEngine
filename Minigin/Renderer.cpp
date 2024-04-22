#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include<iostream>

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}




void dae::Renderer::Init(SDL_Window* window)
{

	m_window = window;

	// Create SDL renderer with OpenGL support
	m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	// Set blend mode for SDL renderer
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const    //maybe change lets see 
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	SceneManager::GetInstance().Render();   
	//SceneManager::GetInstance().Render(framePercentage);  old version 
	//ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

//void dae::Renderer::Render() const
//{
//	const auto& color = GetBackgroundColor();
//	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
//	SDL_RenderClear(m_renderer);
//
//	ImGui_ImplOpenGL2_NewFrame();
//	ImGui_ImplSDL2_NewFrame(m_window);
//	ImGui::NewFrame();
//
//	SceneManager::GetInstance().Render();
//
//	ImGui::Render();
//	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
//
//	SDL_RenderPresent(m_renderer);
//}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);

}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const

//
{
	//SDL_Rect DestiantionRectangle{};
	SDL_Rect SourceRectangle{};

	// if somethibg goes worng just  use the commented rectanglemon top 

	SourceRectangle.x = static_cast<int>(width);
	SourceRectangle.y = static_cast<int>(height);


	SourceRectangle.w = static_cast<int>(width);  //width texture 
	SourceRectangle.h = static_cast<int>(height);  //height of texture




	m_destinationRect.x = static_cast<int>(x);  //pos x
	m_destinationRect.y = static_cast<int>(y);  //pos y 
	m_destinationRect.w = SourceRectangle.w;  //source width * scale
	m_destinationRect.h = SourceRectangle.y;  //source height times scale





	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &m_destinationRect);





}

void dae::Renderer::RenderTexture(const Texture2D& texture, SDL_Rect& destinationRect, SDL_Rect& SourceRect) const
{

	//SDL_Rect DestiantionRectangle{};
	/*SDL_Rect SourceRectSDL{};



	m_destinationRect.x = static_cast<int>(destinationRect.x);
	m_destinationRect.y = static_cast<int>(destinationRect.y);
	m_destinationRect.w = static_cast<int>(destinationRect.w);
	m_destinationRect.h = static_cast<int>(destinationRect.h);

	SourceRectSDL.x = static_cast<int>(SourceRect.x);
	SourceRectSDL.y = static_cast<int>(SourceRect.y);
	SourceRectSDL.w = static_cast<int>(SourceRect.w);
	SourceRectSDL.h = static_cast<int>(SourceRect.h);*/

	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(),&SourceRectSDL, &m_destinationRect);


	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &SourceRect, &destinationRect);


}

const int dae::Renderer::Map[36][28] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
   ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void dae::Renderer::DrawMap()
{

	//224 * 2,   
	//288 * 2,
	//8 * 2 
	//28 //rows
	//36 //columns 
	// 
	//float PosX{}, PosY{}, width{ 16 };
	//for (int rows = 0; rows < 28; rows++)
	//{
	//	for (int columns = 0; columns < 36; columns++)
	//	{
	//		SDL_Color Color{};
	//		SDL_Color Color2{ SDL_Color{ 255,255,255,100}};

	//		if (Map[rows][columns] == 1)
	//		{
	//			Color = SDL_Color{ 255,255,255,40 };

	//		}
	//		else
	//		{
	//			Color = SDL_Color{ 255,0,0,40 };   //0
	//		}

	//		//if(Renderer::)
	//	
	//		FillSquare(PosX+width*rows,PosY+width*columns,width,Color);
	//		DrawSquare(PosX+width*rows,PosY+width*columns,width,Color2);


	//		// int index 0 
	//	}
	//}


	//order depends on how you fill it 

	float PosX{}, PosY{}, width{ 16 }, height{16};
	for (int colums = 0; colums < 36; colums++)
	{
		for (int rows = 0; rows < 28; rows++)                     //code rusn first 
		{
			SDL_Color Color{};
			SDL_Color Color2{ SDL_Color{ 255,255,255,100} };

			if (Map[colums][rows] == 1)
			{
				Color = SDL_Color{ 255,255,255,40 };

			}
			else if(Map[colums][rows] == 0)
			{
				Color = SDL_Color{ 255,0,0,40 };   


			}

			if (Map[colums][rows] == 2)
			{
				
				m_positions.push_back(std::make_pair(int(PosX + width * rows),int(PosY + height * colums)));


			}


			if (Map[colums][rows] == 0)   //where to put points 
			{

				FillSquare(PosX + width * rows+8, PosY + width * colums+8, 6,SDL_Color{255,192,203,255});

			}	
			if (Map[colums][rows] == 3)  //power ups 
			{

				FillSquare(PosX + width * rows+6, PosY + width * colums+6, 12,m_PowerUpColor);

			}


		





		// Degub Grid

		//	FillSquare(PosX + width * rows, PosY + width * colums, width, Color);
			//DrawSquare(PosX + width * rows, PosY + width * colums, width, Color2);


			// int index 0 
		}
	}


	//std::cout << m_positions[0].first << m_positions[0].second << "\n";
				


}

void dae::Renderer::UpdateMap()
{



	m_TotalTimeElapsed += SceneManager::GetInstance().GetDeltaTime();


	if (m_TotalTimeElapsed >= 0.16f)
	{
		m_TotalTimeElapsed = 0;
		ToogleColor();

		if (m_IsBlack)
		{
			m_PowerUpColor = m_White;
		}

		else
		{
			m_PowerUpColor = m_Black;
			
		}



	

	}

}

void dae::Renderer::ToogleColor()
{

	m_IsBlack = !m_IsBlack;

}


inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }

void dae::Renderer::DrawSquare(float x, float y, float size, const SDL_Color& color) const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(x);
	rect.y = static_cast<int>(y);
	rect.w = static_cast<int>(size);
	rect.h = static_cast<int>(size);

	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(m_renderer, &rect);
}

void dae::Renderer::FillSquare(float x, float y, float size, const SDL_Color& color) const
{

	SDL_Rect rect;
	rect.x = static_cast<int>(x);
	rect.y = static_cast<int>(y);
	rect.w = static_cast<int>(size);
	rect.h = static_cast<int>(size);

	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(m_renderer, &rect);
}

void dae::Renderer::FillSquare(float x, float y, float width, float height, const SDL_Color& color) const
{

	SDL_Rect rect;
	rect.x = static_cast<int>(x);
	rect.y = static_cast<int>(y);
	rect.w = static_cast<int>(width);
	rect.h = static_cast<int>(height);

	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(m_renderer, &rect);
}
