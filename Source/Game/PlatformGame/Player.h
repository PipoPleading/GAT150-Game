#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>
namespace kiko
{

	class Player : public Actor
	{
	public:
		CLASS_DECLARATION(Player)

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;
		float maxSpeed = 0;
	/*	float turnRate = 0;
		float m_invincibility = 0;
		Actor bullet;
		int m_health = 10;
		float m_miniTime = 0;
		float m_miniTimer = 0;*/

		class PhysicComponent* m_physicsComponent = nullptr;
		class SpriteAnimRenderComponent* m_spriteAnimComponent = nullptr;
	};

}