#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; } //guess this is the component position
		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }  //this is the game object one 

		void UpdateWorldPosition(const glm::vec3& position);
		void SetPosition(float x, float y, float z);

	private:
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
	};
}
