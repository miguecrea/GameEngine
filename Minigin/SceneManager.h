#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include <queue>
#include"functional"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene & CreateScene(const std::string& name);

		void Update(float deltaTime);
		void Render(float framePercentage);

		// CleanUp()

		float GetDeltaTime() const;
		Scene * GetCurrentScene() const;

		Scene* GetScene(const std::string& name) const;
		void SetCurrentScene(const std::string& name);

		//forceRemoveAllObjects();




		void FixedUpdate(float fixedTimeStep);
		float GetFixedTimeStep() const;
		float GetFramePercentage() const;

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::shared_ptr<Scene>> m_pScenes;

		Scene * m_CurrentScene{};

		float m_DeltaTime{};
		float m_FixedTimeStep{};
		float m_FramePercentage{};
	};
}
