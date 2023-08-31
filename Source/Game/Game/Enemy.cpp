#include "Enemy.h"
#include "Weapon.h"

#include "Framework/Components/CircleCollisionComponent.h"

#include "Framework/Scene.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/PhysicComponent.h"

#include "PeggleThree.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Player.h"

namespace kiko {

	CLASS_DEFINITION(Enemy)

	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physics = GetActor<kiko::PhysicComponent>();
		
		return true;

	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
		READ_DATA(value, fireRate);
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		// movement
		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::vec2 direction = player->transform.position - transform.position;
			m_physics->ApplyForce(direction.Normalized() * speed);
		}


	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		//Player p = dynamic_cast<Player*>(other);

		if (other->tag == "playerBullet")
		{
			kiko::EventManager::Instance().DispatchEvent("AddPoints", 100);

			//m_game->AddPoints(100);
			// 
			//maybe put drops here

			m_destroyed = true;
		}
	}
}