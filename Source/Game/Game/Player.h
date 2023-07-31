#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model, std::shared_ptr<kiko::Model> bulletModel) :
		Actor{ transform, model },
		m_speed{ speed },
		bullet{ transform, bulletModel },
		m_turnRate{ turnRate}
	{
		m_miniTime = 10.0f;
	}

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
};