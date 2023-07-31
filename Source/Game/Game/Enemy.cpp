#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "PeggleThree.h"
#include "Framework/Scene.h"
#include "Weapon.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>(); //-> = . in pointer notation
	if (player) 
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;

		float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
		//turn towards player
		m_transform.rotation += turnAngle * dt; 
		float angle = kiko::vec2::Angle(forward, direction.Normalized());
		//check if player is in front
		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
		{
			//i see u

		}
	}

	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	//fire timer, decrement, if timer is expired then reset fire timer to fire rate and spawn weapon
	if (m_fireTimer <= 0) 
	{
		kiko::Transform transform{ m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
		weapon->m_tag = "enemyBullet";
		m_scene->Add(std::move(weapon));
		m_fireTimer = m_fireRate;
	}
	else
	{
		m_fireTimer -= kiko::g_time.GetDeltaTime();
	}



}

void Enemy::OnCollision(Actor* other)
{
	//Player p = dynamic_cast<Player*>(other);

	if (other->m_tag == "playerBullet") 
	{
		m_game->AddPoints(100);
		//maybe put drops here

		m_destroyed = true;
	}
}
