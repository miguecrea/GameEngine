#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "SceneManager.h"
#include "GameObject.h"
#include"staticHeader.h"



dae::RenderComponent::RenderComponent(const int & state,int priority, bool useAnimation)
	:Component(priority), m_pTexture{ nullptr }, m_useAnimation{ useAnimation },m_state{state}
{
}


//  set texture will load 


dae::RenderComponent::~RenderComponent()
{

}

void dae::RenderComponent::AddToVector(int NrROws, int NRColumns, int MaxNumberFrames, int framesPerSecond, AnimationComponent::Type AnimationType, int currentFrame, int WhichColumn)
{
	m_animationVector.push_back(std::make_unique<AnimationComponent>(m_pTexture,NrROws,NRColumns,MaxNumberFrames,framesPerSecond,AnimationType,currentFrame,WhichColumn));


}
SDL_Rect dae::RenderComponent::ReturnShape()
{
	return SDL_Rect(m_ObjectShape);
}
void dae::RenderComponent::Render()   //animation component  // in thge cosntruvtor it will take eveyrthing it needs 
{
	
	if (m_pTexture)
	{
		 glm::vec3 position{ GetOwner()->GetWorldPosition()}; //get position of the Owner so of game object // calls the puclic function in the game object

		position.x *= 2;
		position.y *= 2;   //change this for a global variable 


		//In add component we set the owner 

		// it is set from the transforwm
		m_LastPosition = position;

		if (m_useAnimation)
		{

		m_animationVector[m_state]->Draw(position.x, position.y,m_scale);

         m_ObjectShape = m_animationVector[m_state]->ReturnShape();


		
		}

		else
		{
		Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y,float(m_pTexture.get()->GetSize().x)*m_scale,float( m_pTexture.get()->GetSize().y)*m_scale);


		m_ObjectShape.x = int(position.x);
		m_ObjectShape.y = int(position.y);
		m_ObjectShape.w = m_pTexture.get()->GetSize().x;
		m_ObjectShape.h = m_pTexture.get()->GetSize().y;
		}

	}
}

void dae::RenderComponent::Update()
{
	if (m_useAnimation)
	{
		
	    m_animationVector[m_state]->Update(SceneManager::GetInstance().GetDeltaTime());

	}

}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}

void dae::RenderComponent::SetDimension(float scale)   //bit using this functuon at the moment 
{
	m_scale = scale;

}

