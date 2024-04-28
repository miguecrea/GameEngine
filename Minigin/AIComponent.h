#pragma once
#include "Component.h"
#include"functional"
#include <memory>
#include <glm/glm.hpp>
#include"Helper.h"



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


		Point2f pos(int row, int column)
		{
			return Point2f(16 * row, 16 * column);
		}

		Point2f WorldToGrid(float posx, float posy)
		{

			int column = static_cast<int>((posy) / 16);
			int row = static_cast<int>((posx) / 16);


			return Point2f{ row,column };



		}


		//remember personalities of the ghosts 

	private:
		std::shared_ptr<GameObject> m_Self = nullptr;
		std::shared_ptr<GameObject> m_Target = nullptr;

		glm::vec3 m_OldPosition;
		glm::vec3 m_Direction;

		glm::vec3 newPosition{};
		SceneManager* m_pSceneManager{ nullptr };




	};


};