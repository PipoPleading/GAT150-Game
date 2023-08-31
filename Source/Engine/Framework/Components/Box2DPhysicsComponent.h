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
		virtual void SetVelocity(const vec2& velocity) override;
		virtual void SetGravityScale(float scale) override;//missing what i need here 


		friend class Box2DCollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body = nullptr;
	};
}