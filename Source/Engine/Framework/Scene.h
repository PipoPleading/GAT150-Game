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

		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll(bool force = false);

		bool Load(const std::string& filename);
		void Read(const json_t& value);

		template<typename T>
		T* GetActor();
		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

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

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (actor->name == name) {
				T* result = dynamic_cast<T*>(actor.get()); //dynamic cast casts to a provided type, such as T*
				if (result) return result; //needs to point to something
			}
		}

		return nullptr;
	}
}