#include "Player.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "PeggleThree.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Emitter.h"

void Player::Update(float dt)
{
	//movement
	Actor::Update(dt);

	
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W ) && 
		!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_W)) {
		thrust = 1;
		kiko::g_audioSystem.PlayOneShot("thrust", false);
		if (m_miniTimer > 0.0f) {
			m_miniTimer -= 2.0f;
			kiko::g_audioSystem.PlayOneShot("reload", false);
		}
	}

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	AddForce(forward * m_speed * thrust);

	kiko::EmitterData data;
	data.burst = true;
	data.burstCount = 100;
	data.spawnRate = 200;
	data.angle = 0;
	data.angleRange = kiko::Pi;
	data.lifetimeMin = 0.5f;
	data.lifetimeMin = 3.5f;
	data.speedMin = 50;
	data.speedMax = 500;
	data.damping = 0.5f;
	data.color = kiko::Color{ 1, 0, 0, 1 };

	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	///weapon reference



	//fire weapon

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && 
		!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) 
	{
		//create weapon
		kiko::Transform transform1{ m_transform.position, m_transform.rotation + kiko::DegreesToRadians(10.0f), 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 400.0f, transform1, m_model);
		kiko::g_audioSystem.PlayOneShot("hit", false);
		weapon->m_tag = "playerBullet";
		m_scene->Add(std::move(weapon));

		//kiko::Transform transform2{ m_transform.position, m_transform.rotation + kiko::DegreesToRadians(10.0f), 1};
		//std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform2, m_model);
		//weapon->m_tag = "playerBullet";
		//m_scene->Add(std::move(weapon));
	}

	////minigun
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S) && 
		(!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_S))) {
		if (m_miniTimer == 0) {
			kiko::g_audioSystem.PlayOneShot("shotgun", false);
			for (int i = 5; i <= 0 ; i -- ) {
				kiko::Transform transform1{ m_transform.position, m_transform.rotation + kiko::DegreesToRadians(kiko::randomf(1.0f, 30.0f)), 1};
				std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1, m_model);
				weapon->m_tag = "playerBullet";
				m_scene->Add(std::move(weapon));

				
			}
			m_miniTimer = m_miniTimer + 10.0f;
		}
		else {
			kiko::g_audioSystem.PlayOneShot("thrust", false);
			kiko::g_audioSystem.PlayOneShot("hit", false);
			kiko::g_audioSystem.PlayOneShot("thrust", false);
		}
	}

}

void Player::OnCollision(Actor* other)
{
		if (other->m_tag == "star" && m_invincibility == 1) {
			m_game->SetLives(m_game->GetLives() + 1);
			return;
		}
		if (m_invincibility == 1 && other->m_tag == "enemyBullet") {
			m_invincibility = 0;
			return;
		}
		if (other->m_tag=="star") {
			m_invincibility = 1;
			return;
		}
	if (other->m_tag == "enemyBullet")
	{	
		kiko::g_audioSystem.PlayOneShot("death", false);
		m_game->SetLives(m_game->GetLives() - 1);
		m_destroyed = true;
		dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
	}

}
