#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicComponent.h"
#include <Renderer/Model.h>

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, const kiko::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		bullet{ transform },
		m_turnRate{ turnRate}
	{
		m_miniTime = 10.0f;
	}

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_invincibility = 0;
	Actor bullet;
	int m_health = 10;
	float m_miniTime = 0;
	float m_miniTimer = 0;

	kiko::PhysicComponent* m_physicsComponent = nullptr;
};