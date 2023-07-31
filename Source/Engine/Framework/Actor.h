#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include <memory>

namespace kiko
{
	class Actor
	{
	public:
		Actor() = default; // This automatically exists without typing

		Actor(const kiko::Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}
		Actor(const kiko::Transform& transform, std::shared_ptr<Model> model, std::shared_ptr<Model> bulletModel) :
			m_transform{ transform },
			m_model{ model },
			m_bulletModel{ bulletModel }
		{}
		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);
		//virtual void Draw(kiko::Renderer& renderer);
	
		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }
		virtual void OnCollision(Actor* other) {}

		void AddForce(const vec2& force) { m_velocty += force; }
		void SetDamping(float damping) { m_damping = damping; } //lerp 

		class Scene* m_scene = nullptr; //temporary public; this sucks also 
		friend class Scene;

		class Game* m_game = nullptr;
		
		Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;

		//virtual void Particles(float spawnRate,
		//	bool burst,
		//	size_t burstCount,
		//	float spawnRateTimer,
		//	float angle,
		//	float angleRange,
		//	// particle parameters
		//	float lifetimeMin,
		//	float lifetimeMax,
		//	float speedMin,
		//	float speedMax,
		//	float damping,
		//	float red,
		//	float green,
		//	float blue,
		//	float alpha
		//);

	protected:
		bool m_destroyed = false;
		std::shared_ptr<Model> m_model;
		std::shared_ptr<Model> m_bulletModel;

		vec2 m_velocty;
		float m_damping = 0;
	};

}