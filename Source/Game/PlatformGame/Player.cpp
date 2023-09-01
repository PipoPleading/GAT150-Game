#include "Player.h"

#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

namespace kiko
{

	CLASS_DEFINITION(Player)

	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetActor<kiko::PhysicComponent>();
		m_spriteAnimComponent = GetActor<kiko::SpriteAnimRenderComponent>();
		
		return true;
	}

	void Player::Update(float dt)
	{
		//movement
		Actor::Update(dt);

		//kiko::vec2 velocity = kiko::vec2{ 1, 0 }; // need to double check this
		vec2 velocity = m_physicsComponent->m_velocity;
		bool onGround = (groundCount > 0);

		float horiz = 0;
		float ver = 0;

		//left and right
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A) && (!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_A))) horiz = -1;

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D) && (!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_D))) horiz = 1;

		//up
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) && (!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_W))) ver = -1;

		//horizontal velocity
		if (horiz)
		{	
			velocity.x += speed * horiz * ((onGround) ? 1 : 0.25f) * dt;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);
		}

		//
		if (ver)
		{
			velocity.y += speed * ver * ((onGround) ? 1 : 1.25f) * dt;
			velocity.y = Clamp(velocity.y, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);
		}


		//Jump
		if (/*onGround &&*/(
			kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			(!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))))
		{
			kiko::vec2 up = kiko::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity( velocity + (up * jump));
		}

		m_physicsComponent->SetGravityScale((velocity.y > 0) ? 5.0f : 3.0f);//need to find the code for SetGravityScale


		//animation
		if (std::fabs(velocity.x) > 0.2f)
		{
			if(horiz != 0) m_spriteAnimComponent->flipH = (horiz < 0);
			m_spriteAnimComponent->SetSequence("jump");
		}
		else
		{
			m_spriteAnimComponent->SetSequence("idle");
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		//if (other->tag == "Enemy")
		//{
		//	m_destroyed = true;
		//	//EVENT_DISPATCH("OnPlayerDead", 0); missing this
		//}

		if (other->tag == "Ground") groundCount++;
	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, maxSpeed);
		READ_DATA(value, jump);
	}
}