#pragma once
#include "PhysicComponent.h"
#include "Physics/Physics.h"
#

class b2Body;

namespace kiko
{
	class Box2DPhysicsComponent : public PhysicComponent
	{
	public:
		CLASS_DECLARATION(Box2DPhysicsComponent)

		bool Initialize() override;
		void OnDestroy() override;

		void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;
		virtual void ApplyTorque(float torque) override;

		friend class Box2DCollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body = nullptr;
	};
}