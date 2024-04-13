#pragma once

#include "Component.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Texture2D.h"
#include <memory>
#include "AnimationComponent.h"



namespace dae
{
	class GameObject;

	class AnimationComponent final :public Component
	{
	public:

		virtual ~AnimationComponent() = default;
		AnimationComponent(const AnimationComponent& other) = default;
		AnimationComponent(AnimationComponent&& other) = default;
		AnimationComponent& operator=(const AnimationComponent& other) = default;
		AnimationComponent& operator=(AnimationComponent&& other) = default;


		enum class Type
		{

			loop,
			onlyOnce,
			StartAtNoZero,
			OnlyOnceandEndAtLast

		};
		                                                   //
		AnimationComponent(std::shared_ptr<Texture2D> Texture,int NrROws, int NRColumns, int MaxNumberFrames, int framesPerSecond, Type AnimationType, int currentFrame, int WhichColumn);

	//	void Draw(Rectf& Avatar, float scale);

	  virtual void Draw(float x, float y, float scale);
		void Update(float elapsedSec);
	//	void SetAnimationPlaying(bool play);
	//	virtual void Update() override;
	//	int GetCurrentFrame();
	//	int GetMaxNumberOfFrames();
		int GetFrameWidth();
		int GetFrameHeight();
	//	void SetCurrentFrame(const int NrFrame);
	//	void SetTotalTimeElapsed(const float Time);


		 SDL_Rect  & ReturnShape();

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		int m_Rows;
		int m_Columns;
		int m_MaxNumberFrames;
		int  m_FramesPerSecond;
		Type m_TypeOfAnimation;
		int m_CurrentFrame;
		float m_TotalTimeElapsed;
		int m_copy;
		int m_WhichColumns;
		bool m_IsAnimationPlaying;
		SDL_Rect m_destinationRect{};

	};
}
