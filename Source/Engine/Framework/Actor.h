#pragma once
#include "Object.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Components.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include <memory>

namespace kiko
{
	class Actor : public Object
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default; // This automatically exists without typing
		Actor(const kiko::Transform& transform) :
			transform{ transform }
		{}
		Actor(const Actor& other);
		virtual ~Actor() {
			OnDestroy();
		}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);
		//virtual void Draw(kiko::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetActor();
	
		//float GetRadius() { return 30.0f; }//(m_model) ? m_model->GetRadius() * m_transform.scale : 0;
		virtual void OnCollisionEnter(Actor* other) {}
		virtual void OnCollisionExit(Actor* other) {}

		//void AddForce(const vec2& force) { m_velocty += force; }
		//void SetDamping(float damping) { m_damping = damping; } //lerp 

		class Scene* m_scene = nullptr; //temporary public; this sucks also 
		friend class Scene;

		class Game* m_game = nullptr;
		
		kiko::Transform transform;
		std::string tag;

		float lifespan = -1.0f;
		bool m_destroyed = false;
		bool persistent = false;
		bool prototype = false;

	protected:
		std::vector<std::unique_ptr<Component>> components;


	};

	template<typename T>
	inline T* Actor::GetActor()
	{
		for (auto& actor : components) 
		{
			T* result = dynamic_cast<T*>(actor.get()); //dynamic cast casts to a provided type, such as T*
			if (result) return result; //needs to point to something
		}

		return nullptr;
	}

}