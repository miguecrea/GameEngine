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

	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const   
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	SceneManager::GetInstance().Render();   
	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}


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
	SDL_Rect SourceRectangle{};


	SourceRectangle.x = static_cast<int>(width);
	SourceRectangle.y = static_cast<int>(height);


	SourceRectangle.w = static_cast<int>(width);  
	SourceRectangle.h = static_cast<int>(height); 



	m_destinationRect.x = static_cast<int>(x); 
	m_destinationRect.y = static_cast<int>(y); 
	m_destinationRect.w = SourceRectangle.w;  
	m_destinationRect.h = SourceRectangle.y;  

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &m_destinationRect);


}

void dae::Renderer::RenderTexture(const Texture2D& texture, SDL_Rect& destinationRect, SDL_Rect& SourceRect) const
{

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &SourceRect, &destinationRect);
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

