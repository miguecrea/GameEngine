#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include<vector>
#include"AnimationComponent.h"

namespace dae
{
	class GameObject;
	class Texture2D;
	class Font;
	class AnimationComponent;
	

	class RenderComponent final: public Component
	{
	public:

		RenderComponent(const int & state,int priority = -2,bool useAnimation = false);

		virtual void Render() override;
		virtual void Update() override;
		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> pTexture);
		void SetDimension(float scale);
		void AddToVector(int NrROws, int NRColumns, int MaxNumberFrames, int framesPerSecond,AnimationComponent::Type AnimationType, int currentFrame, int WhichColumn);
		SDL_Rect ReturnShape();

		//rule of 5 
		virtual ~RenderComponent() override;
		RenderComponent(const RenderComponent& other) = default;
		RenderComponent(RenderComponent&& other) = default;
		RenderComponent& operator=(const RenderComponent& other) = default;
		RenderComponent& operator=(RenderComponent&& other) = default;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};   //pointer to texture 

		std::vector < std::unique_ptr<AnimationComponent>> m_animationVector;
		glm::vec3 m_LastPosition{};
		
		 SDL_Rect  m_ObjectShape;
		const int & m_state;  //male this a refermnce ?

		  
		float m_scale = 1 ;
		bool m_useAnimation = false;
	};
}

