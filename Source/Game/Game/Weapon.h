#pragma once
#include "Framework/Actor.h"
#include "Framework/Emitter.h"
#include "Framework/Scene.h"
#include <Renderer/Model.h>


class Weapon : public kiko::Actor
{
public:
	Weapon(float speed, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		m_lifespan = 2.0f; //how long the thing exists until it's destroyed 
	}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float m_speed = 0;
};