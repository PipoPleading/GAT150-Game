#include "Actor.h"

namespace kiko
{
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		m_transform.position += m_velocty * dt;
		m_velocty *= std::pow(1.0f - m_damping, dt);
	}
	void Actor::Draw(kiko::Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}

	//void Actor::Particles(float spawnRate, bool burst, size_t burstCount, float spawnRateTimer,
	//	float angle, float angleRange, float lifetimeMin, float lifetimeMax,
	//	float speedMin, float speedMax, float damping,
	//	float red,float green,float blue,
	//	float alpha)
	//{
	//	data.spawnRate = spawnRate;
	//	data.burst = burst;
	//	data.burstCount = burstCount;
	//	data.angle = angle;
	//	data.angleRange = angleRange; //pi, two pi, or half pi
	//	data.lifetimeMin = lifetimeMin;
	//	data.lifetimeMax = lifetimeMax;
	//	data.speedMin = speedMin;
	//	data.speedMax = speedMax;
	//	data.damping = damping;
	//	data.color = kiko::Color{ red, green, blue, alpha };

	//	kiko::Transform transform{ {  }, 0, 1 };
	//	auto emitter = std::make_unique<kiko::Emitter>(transform, data);
	//	emitter->m_lifespan = 1.0f; //from framework
	//	//m_scene->Add(std::move(emitter));
	//}

	//void Actor::() {

	//	kiko::Transform transform{ { kiko::g_inputSystem.GetMousePosition() }, 0, 1 };
	//	auto emitter = std::make_unique<kiko::Emitter>(transform, data);
	//	emitter->m_lifespan = 1.0f; //from framework
	//	m_scene->Add(std::move(emitter));
	//}
}