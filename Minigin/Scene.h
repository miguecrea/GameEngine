#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene & SceneManager::CreateScene(const std::string& name);


	public:
		void Add(std::shared_ptr<GameObject> object);

		void ForceRemove(std::shared_ptr<GameObject> pObject);
		void ForceRemoveAll();
		void DestroyAll();


		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();
		void CheckParentException(std::shared_ptr<GameObject> object) const;

		void Update();
		void Render() const;
		void CleanUp();

		void FixedUpdate();
		std::string GetName() const;

		void Load();
		bool NeedsCleanUp() const;



		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector <std::shared_ptr<GameObject>> m_pObjects{};

	
		static unsigned int m_idCounter; 
	};

}
