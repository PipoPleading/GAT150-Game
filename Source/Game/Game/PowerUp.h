#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>

class PowerUp : public kiko::Actor
{
public:
	PowerUp(float speed, const kiko::Transform& transform) :
		Actor{ transform},
		m_speed{ speed }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float m_speed = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
};