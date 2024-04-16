#pragma once
#include <SDL.h>
#include "Singleton.h"
#include<vector>

namespace dae
{

	struct Rectf
	{
		float x{};
		float y{};
		float width{};
		float height{};

	};



	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>    //this one is to render 
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render(float framePercentage) const;
		//void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;   //what about this 
		void RenderTexture(const Texture2D& texture, SDL_Rect & destinationRect, SDL_Rect & SourceRect) const;
		void DrawMap();


		static const int Map[36][28];
		
		std::vector<std::pair<int, int>> m_positions; // Vector to store positions



		//if(columns[colun][row]==2
		//set aquare another color y en colision tambine permitirle 


		// vector where the psoitions is to  sthat stores the row and columns 
		//then pas that to a funtion that returns x and y psoition 
		//draw a mini square 

	//	ImVec2 GridToMap();


		mutable SDL_Rect m_destinationRect{};
		

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
		void DrawSquare(float x, float y, float size, const SDL_Color& color) const;
		void FillSquare(float x, float y, float size, const SDL_Color& color) const;


	};
}

