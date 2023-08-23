#pragma once
#include "PhysicComponent.h"

namespace kiko
{
	class EnginePhysicsComponent : public PhysicComponent
	{
	public:
		CLASS_DECLARATION(EnginePhysicsComponent)
			
		virtual void Update(float dt) override;

		virtual void ApplyForce(const vec2& force) override;

		void ApplyTorque(float torque) override;

	};
}