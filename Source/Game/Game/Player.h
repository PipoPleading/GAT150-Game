#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicComponent.h"
#include <Renderer/Model.h>
namespace kiko
{

	class Player : public Actor
	{
	public:
			CLASS_DECLARATION(Player)

			/*Player(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			bullet{ transform },
			turnRate{ turnRate }
		{
			m_miniTime = 10.0f;
		}*/

		bool Initialize() override;

		void OnDestroy() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float speed = 0;
		float turnRate = 0;
		float m_invincibility = 0;
		Actor bullet;
		int m_health = 10;
		float m_miniTime = 0;
		float m_miniTimer = 0;

		kiko::PhysicComponent* m_physicsComponent = nullptr;
	};

}