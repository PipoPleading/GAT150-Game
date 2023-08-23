#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{

    bool Weapon::Initialize()
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

    void Weapon::Update(float dt)
    {
        Actor::Update(dt);

        kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
        transform.position += forward * speed * kiko::g_time.GetDeltaTime();
        transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
        transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

    }

    void Weapon::OnCollision(Actor* other)
    {
        if (other->tag == tag) {

            //kiko::EmitterData data;
            //data.burst = true;
            //data.burstCount = 50;
            //data.spawnRate = 10;
            //data.angle = 1;
            //data.angleRange = kiko::Pi;
            //data.lifetimeMin = 20.0f;
            //data.lifetimeMax = 50.0f;
            //data.speedMin = 1;
            //data.speedMax = 100;
            //data.damping = 0.75f;
            //data.color = kiko::Color{ 0.5, 0.5, 0, 1 };

            //kiko::Transform transform{ { kiko::g_inputSystem.GetMousePosition() }, 0, 1 };
            ////need to get position of bullet before destroying it
            //auto emitter = std::make_unique<kiko::Emitter>(transform, data);
            //emitter->lifespan = 1.0f; //from framework
            //m_scene->Add(std::move(emitter));

            m_destroyed = true;
        }
    }
    void Weapon::Read(const json_t& value)
    {
        Actor::Read(value);

        READ_DATA(value, speed);
    }
}