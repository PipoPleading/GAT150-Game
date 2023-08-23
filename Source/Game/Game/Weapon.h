#pragma once
//#include "Framework/Actor.h"
//#include "Framework/Components/CollisionComponent.h"
//#include "Framework/Components/RenderComponents.h"
//#include "Framework/Emitter.h"
//#include "Framework/Scene.h"
//#include <Renderer/Model.h>
#include "Framework/Actor.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon)

		//Weapon(float speed, const kiko::Transform& transform) :
		//	Actor{ transform},
		//	m_speed{ speed }
		//{
		//	lifespan = 2.0f; //how long the thing exists until it's destroyed 
		//}

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollision(Actor* actor);
		//void Read(const json_t& value);

	private:
		float speed = 0;
	};

}