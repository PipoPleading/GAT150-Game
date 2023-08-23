#include "Enemy.h"
#include "Weapon.h"

#include "Framework/Components/CircleCollisionComponent.h"

#include "Framework/Scene.h"
#include "Framework/Components/Sprite.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/PhysicComponent.h"

#include "PeggleThree.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Player.h"

bool Enemy::Initialize()
{
	Actor::Initialize();

	auto collisionComponent = GetComponent<kiko::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if (renderComponent)
		{
			float scale = transform.scale;
			collisionComponent->m_radius = renderComponent->GetRadius() * scale;
		}
	}

	return true;

}

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
	Player* player = m_scene->GetComponent<Player>(); //-> = . in pointer notation
	if (player) 
	{
		kiko::Vector2 direction = player->transform.position - transform.position;

		float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
		//turn towards player
		transform.rotation += turnAngle * dt; 
		float angle = kiko::vec2::Angle(forward, direction.Normalized());
		//check if player is in front
		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
		{
			//i see u

		}
	}

	transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

	//fire timer, decrement, if timer is expired then reset fire timer to fire rate and spawn weapon
	if (m_fireTimer <= 0) 
	{
		//kiko::Transform transform{ transform.position, transform.rotation, 1};
		//std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform);
		//weapon->tag = "enemyBullet";
		//m_scene->Add(std::move(weapon));
		//m_fireTimer = m_fireRate;
	}
	else
	{
		m_fireTimer -= kiko::g_time.GetDeltaTime();
	}



}

void Enemy::OnCollision(Actor* other)
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
