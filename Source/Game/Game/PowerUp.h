#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>

class PowerUp : public kiko::Actor
{
public:
	PowerUp(float speed, const kiko::Transform& transform) :
		Actor{ transform},
		speed{ speed }
	{}

	void Update(float dt) override;
	void OnCollisionEnter(Actor* actor) override;

private:
	float speed = 0;

	float fireRate = 0;
	float m_fireTimer = 0;
};