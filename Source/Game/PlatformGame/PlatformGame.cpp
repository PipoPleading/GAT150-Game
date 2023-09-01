#include "PlatformGame.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
//#include "PowerUp.h"

//should use framework.h
#include "Framework/Framework.h"

//#include "Framework/Scene.h"
//#include "Framework/Resource/ResourceManager.h"
//#include "Framework/Emitter.h"
//#include "Framework/Components/SpriteComponent.h"
//#include "Framework/Components/EnginePhysicsComponent.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
//#include "Renderer/Text.h"
//#include <Instance.h>


bool PlatformGame::Initialize()
{



    //load scene
    m_scene = std::make_unique<kiko::Scene>();
    kiko::g_audioSystem.AddAudio("music", "spaceSong.wav");
    kiko::g_audioSystem.PlayOneShot("music", true);
    m_scene->Load("Scenes/PlatformScene.json");
    m_scene->Load("Scenes/tilemap.json");
    m_scene->Initialize();

    //add events
    EVENT_SUBSCRIBE("AddPoints", PlatformGame::AddPoints)
    EVENT_SUBSCRIBE("PlayerDead", PlatformGame::OnPlayerDead)

    //kiko::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&PlatformGame::AddPoints, this, std::placeholders::_1));
    //kiko::EventManager::Instance().Subscribe("PlayerDead", this, std::bind(&PlatformGame::OnPlayerDead, this, std::placeholders::_1));


    
        auto actor = INSTANTIATE(Actor, "Crate");
        actor->transform.position = { 572, 0 };
        actor->Initialize();
        m_scene->Add(std::move(actor));
    
    return true;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{
    switch (m_state)
    {
    case eState::Title:

    
        break;
    case eState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_state = eState::MusicStart;


        break;
    case eState::MusicStart:
        if (m_music = true) {
            m_music = false;


        }

        m_state = eState::StartLevel;
        break;
    case eState::StartLevel:
        m_scene->RemoveAll();
        {
            
            //player creation
            //auto player = std::make_unique<Player>(70.0f, 0, kiko::Transform{ {400, 300 }, 0, 6 });
            //player->tag = "player"; 
            //player->m_game = this;
            //
            ////create components
            //auto renderComponent = CREATE_CLASS(SpriteComponent)//std::make_unique<kiko::SpriteComponent>();
            //renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "ship.png", kiko::g_renderer);
            //player->AddComponent(std::move(renderComponent));

            //auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent)
            //physicsComponent->m_damping = 0.9f;
            //player->AddComponent(std::move(physicsComponent));

            //auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
            //collisionComponent->m_radius = 30.0f;
            //player->AddComponent(std::move(collisionComponent));

            //player->Initialize();
            //m_scene->Add(std::move(player));
            //auto player = INSTANTIATE(Player, "Player");
            //player->transform = kiko::Transform{ { 400, 300 }, 0, 1 };
            //player->Initialize();
            //m_scene->Add(std::move(player));




        }
        m_state = eState::Game;
        break;
    case eState::Game:
        m_spawnTimer += dt;
        if (m_spawnTimer >= m_spawnTime)
        {
            //m_random = kiko::randomf(256.0f);

            //auto enemy = INSTANTIATE(Enemy, "Enemy");
            //enemy->transform = kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 1 };
            //enemy->Initialize();
            //m_scene->Add(std::move(enemy));

            //if (m_random <= 128) {
            //    //enemy
            //std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(150.0f, 275.0f), kiko::Pi, kiko::Transform{{kiko::random(800), kiko::random(600)}
            //, kiko::randomf(kiko::TwoPi), 3});
            //enemy->tag = "enemy";
            //enemy->m_game = this;
            ////create components
            ////m_scene->Add(std::move(enemy));

            //auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
            //collisionComponent->m_radius = 30.0f;
            //enemy->AddComponent(std::move(collisionComponent));

            //enemy->Initialize();
            //m_scene->Add(std::move(enemy));

            //    //powerup
            ///*std::unique_ptr<PowerUp> powerup = std::make_unique<PowerUp>(kiko::randomf(300.0f, 500.0f), kiko::Transform{{kiko::random(800), kiko::random(600)}
            //, kiko::randomf(kiko::TwoPi), 3}, kiko::g_manager.Get("Star.txt"));
            //powerup->m_tag = "star";
            //powerup->m_game = this;
            //m_scene->Add(std::move(powerup));*/



            //}

            //m_spawnTimer = 0.0f;
            //std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(150.0f, 275.0f), kiko::Pi, kiko::Transform{{kiko::random(800), kiko::random(600)}
            //, kiko::randomf(kiko::TwoPi), 3}, kiko::g_manager.Get("enemy.txt"));
            //enemy->m_tag = "enemy";
            //enemy->m_game = this;
            //m_scene->Add(std::move(enemy));


        }
        {
            int r = kiko::random(256);
            int g = kiko::random(256);
            int b = kiko::random(256);

            //can be used for a variety of effects
            //kiko::EmitterData data;
            //data.burst = true;
            //data.burstCount = 100;
            //data.spawnRate = 200;
            //data.angle = 0;
            //data.angleRange = kiko::Pi;
            //data.lifetimeMin = 0.5f;
            //data.lifetimeMin = 1.0f;
            //data.speedMin = 50;
            //data.speedMax = 500;
            //data.damping = 0.5f;
            //data.color = kiko::Color{ 0, 1, 0, 1 };

            //kiko::Transform transform{ { kiko::g_inputSystem.GetMousePosition() }, 0, 1 };
            //auto emitter = std::make_unique<kiko::Emitter>(transform, data);
            //emitter->m_lifespan = 1.0f; //from framework
            //m_scene->Add(std::move(emitter));


            r = kiko::random(256);  //this got restated and is randomizing all the colors each
            g = kiko::random(256);
            b = kiko::random(256);

        }
        break;
    case eState::PlayerDeadStart:
        m_stateTimer = 3;
        if (m_lives == 0) m_state = eState::GameOver;
        else m_state = eState::PlayerDead; //restarts level instantly on gameOver

        break;

    case eState::PlayerDead:

        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {

            m_state = eState::StartLevel;
        }

        break;
    case eState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {

            m_scene->RemoveAll();
            m_state = eState::Title;
        }
        break;
    default:
        break;
    }

    //m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
    //m_livesText->Create(kiko::g_renderer, std::to_string(m_lives), { 1, 0, 0, 1 });

    //m_shootText->Create(kiko::g_renderer, std::to_string(m_miniTimer), { 1, 0, 0, 1 });

    ///m_livesText->Create(kiko::g_renderer, std::to_string(m_lives), { 1, 1, 1, 1 }); health display
    //m_timerText->Create(kiko::g_renderer, std::to_string((int)m_gameTimer), { 1, 1, 1, 1 }); timer...?

    m_scene->Update(dt);
}

void PlatformGame::Draw(kiko::Renderer& renderer)
{
    //if (m_state == eState::Title)
    //{
    //    //m_titleText->Draw(renderer, 600, 450);

    //}
    //if (m_state == eState::GameOver)
    //{
    //    //m_gameoverText->Draw(renderer, 600, 450);
    //}
    ///* if (m_state == eState::Game) {
    //     m_timerText->Draw(renderer, 200, 40);
    // }*/

    // // m_shootText->Draw(renderer, 1150, 40);

    // // m_scoreText->Draw(renderer, 1100, 20);
    //  //m_livesText->Draw(renderer, 1100, 80);
    m_scene->Draw(renderer);
}


void PlatformGame::AddPoints(const kiko::Event& event)
{
    m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const kiko::Event& event)
{
    
    m_lives--;
    m_state = eState::PlayerDeadStart;
}
