#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicComponent.h"

namespace kiko {
	class Enemy : public Actor
	{
	public:

		CLASS_DECLARATION(Enemy)

		bool Initialize() override;
		void OnDestroy() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* actor) override;

	private:
		float speed = 0;
		float turnRate = 0;

		float fireRate = 0;
		float m_fireTimer = 0;

		kiko::PhysicComponent* m_physics = nullptr;
	};
}