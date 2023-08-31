#include "PowerUp.h"
#include "Renderer/Renderer.h"
#include "Game/Player.h"
#include "PeggleThree.h"
#include "Framework/Scene.h"

void PowerUp::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
	kiko::Player* player = m_scene->GetActor<kiko::Player>(); //-> = . in pointer notation
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
			// runs away
			turnAngle += kiko::Pi;

		}
	}

	transform.position += forward * speed * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

}

void PowerUp::OnCollisionEnter(Actor* other)
{
	//Player p = dynamic_cast<Player*>(other);

	if (other->tag == "player")
	{
		m_game->AddPoints(500);
		//maybe put drops here
		m_destroyed = true;
	}
}
