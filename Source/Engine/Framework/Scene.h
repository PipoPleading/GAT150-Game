#pragma once
#include "Actor.h"
#include "Renderer/Renderer.h"
#include <list>

namespace kiko
{
	class Renderer; //alternate to include


	class Scene
	{
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		template<typename T>
		T* GetActor();

		friend class Actor;

	private:
		std::list<std::unique_ptr<Actor>> m_actors;

	};

	template<typename T>
	inline T* Scene::GetActor() //inline does a code substitution, often useful in headers in substitution of tags
	{
		for (auto& actor : m_actors) 
		{
			T* result = dynamic_cast<T*>(actor.get()); //dynamic cast casts to a provided type, such as T*
			if (result) return result; //needs to point to something
		}

		return nullptr;
	}
}