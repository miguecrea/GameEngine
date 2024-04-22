#pragma once
#include "Component.h"
#include"functional"
#include <memory>
#include <glm/glm.hpp>



namespace dae
{
	class SceneManager;


	class AIComponent :public Component
	{

	public:

		// this class wil, take an enum class that /describes the personality of each Ghost 


		//gess needs pacman position of pacmans 


		AIComponent(std::shared_ptr<GameObject> SelfGameObject, std::shared_ptr<GameObject> pTargetGameObejct);

		virtual void Render() override;
		virtual void Update() override;

		//remember personalities of the ghosts 

	private:
		std::shared_ptr<GameObject> m_Self = nullptr;
		std::shared_ptr<GameObject> m_Target = nullptr;

		glm::vec3 m_OldPosition;
		glm::vec3 m_Direction;
		glm::vec3 m_TargetPos;
		SceneManager * m_pSceneManager{ nullptr };




	};


};