#include "Weapon.h"

void Weapon::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

}

void Weapon::OnCollision(Actor* other)
{
	if (other->m_tag == m_tag) {

        kiko::EmitterData data;
        data.burst = true;
        data.burstCount = 50;
        data.spawnRate = 10;
        data.angle = 1;
        data.angleRange = kiko::Pi;
        data.lifetimeMin = 20.0f;
        data.lifetimeMax = 50.0f;
        data.speedMin = 1;
        data.speedMax = 100;
        data.damping = 0.75f;
        data.color = kiko::Color{ 0.5, 0.5, 0, 1 };

        kiko::Transform transform{ { kiko::g_inputSystem.GetMousePosition() }, 0, 1 };
        //need to get position of bullet before destroying it
        auto emitter = std::make_unique<kiko::Emitter>(transform, data);
        emitter->m_lifespan = 1.0f; //from framework
        m_scene->Add(std::move(emitter));

		m_destroyed = true;
	}
}
