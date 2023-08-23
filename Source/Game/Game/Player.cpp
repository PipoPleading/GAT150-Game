#include "Player.h"
#include "Weapon.h"

#include "Framework/Components/CircleCollisionComponent.h"

#include "Framework/Scene.h"
#include "Framework/Components/Sprite.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/PhysicComponent.h"

#include "PeggleThree.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Framework/Emitter.h"

bool Player::Initialize()
{
	Actor::Initialize();

	m_physicsComponent = GetComponent<kiko::PhysicComponent>();
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

void Player::Update(float dt)
{
	//movement
	Actor::Update(dt);

	
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

	transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

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

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);

	auto physicComponent = GetComponent<kiko::PhysicComponent>(); //passing the components, need to rename to GetComponents
	physicComponent->ApplyForce(forward * m_speed * thrust);

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

	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

	///weapon reference



	//fire weapon

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && 
		!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) 
	{
		auto weapon = INSTANTIATE(Weapon, "Rocket")
		weapon->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1};
		weapon->Initialize();
		m_scene->Add(std::move(weapon));

		//create weapon
		/*kiko::Transform transform1{ transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 400.0f, transform1);
		kiko::g_audioSystem.PlayOneShot("hit", false);
		weapon->tag = "playerBullet";

		std::unique_ptr<kiko::Sprite> component = std::make_unique<kiko::Sprite>();
		component->m_texture = GET_RESOURCE(kiko::Texture, "ship.png", kiko::g_renderer);
		weapon->AddComponent(std::move(component));

		auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		weapon->AddComponent(std::move(collisionComponent));

		weapon->Initialize();
		m_scene->Add(std::move(weapon));*/

		//kiko::Transform transform2{ m_transform.position, m_transform.rotation + kiko::DegreesToRadians(10.0f), 1};
		//std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform2, m_model);
		//weapon->m_tag = "playerBullet";
		//m_scene->Add(std::move(weapon));
	}

	////minigun
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S) && 
		(!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_S))) {
		/*if (m_miniTimer == 0) {
			kiko::g_audioSystem.PlayOneShot("shotgun", false);
			for (int i = 5; i -- ; i <= 0 ){
				kiko::Transform transform1{ transform.position, transform.rotation + kiko::DegreesToRadians(kiko::randomf(1.0f, 30.0f)), 1};
				std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1);
				weapon->tag = "playerBullet";

				std::unique_ptr<kiko::Sprite> component = std::make_unique<kiko::Sprite>();
				component->m_texture = GET_RESOURCE(kiko::Texture, "ship.png", kiko::g_renderer);
				weapon->AddComponent(std::move(component));

				m_scene->Add(std::move(weapon));

				
			}
			m_miniTimer = m_miniTimer + 10.0f;
		}
		else {
			kiko::g_audioSystem.PlayOneShot("thrust", false);
			kiko::g_audioSystem.PlayOneShot("hit", false);
			kiko::g_audioSystem.PlayOneShot("thrust", false);
		}*/
	}

}

void Player::OnCollision(Actor* other)
{
		if (other->tag == "star" && m_invincibility == 1) {
			m_game->SetLives(m_game->GetLives() + 1);
			return;
		}
		if (m_invincibility == 1 && other->tag == "enemyBullet") {
			m_invincibility = 0;
			return;
		}
		if (other->tag=="star") {
			m_invincibility = 1;
			return;
		}

		//kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
	if (other->tag == "enemyBullet")
	{	
		kiko::g_audioSystem.PlayOneShot("death", false);
		//m_game->SetLives(m_game->GetLives() - 1);
		kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		m_destroyed = true;
		dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
	}

}
