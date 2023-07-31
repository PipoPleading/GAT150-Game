#include "PeggleThree.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"

#include "Framework/Scene.h"
#include "Framework/Emitter.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModeManager.h"


bool SpaceGame::Initialize()
{
    //create font/ text objects
    m_font = std::make_shared<kiko::Font>("KarmaFuture.ttf", 24);
    m_titleFont = std::make_shared<kiko::Font>("KarmaFuture.ttf", 48);
    m_scoreText = std::make_unique<kiko::Text>(m_font);
    m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1.0f, 1.0f, 1.0f, 1.0f });

    m_titleText = std::make_unique<kiko::Text>(m_font);
    m_titleText->Create(kiko::g_renderer, "Flak Cannon", kiko::Color{ 1.0f, 1.0f, 1.0f, 1.0f });

    m_gameoverText = std::make_unique<kiko::Text>(m_font);
    m_gameoverText->Create(kiko::g_renderer, "Game_Over", kiko::Color{ 1.0f, 1.0f, 1.0f, 1.0f });

    m_timerText = std::make_unique<kiko::Text>(m_font);
    m_timerText->Create(kiko::g_renderer, "TIMER", kiko::Color{ 1.0f, 1.0f, 1.0f, 1.0f });

    m_livesText = std::make_unique<kiko::Text>(m_font);
    m_livesText->Create(kiko::g_renderer, "LIVES 0", kiko::Color{ 1.0f, 0.0f, 0.0f, 1.0f });

    m_shootText = std::make_unique<kiko::Text>(m_font);
    m_shootText->Create(kiko::g_renderer, "SHOOT 0", kiko::Color{ 0.0f, 1.0f, 1.0f, 1.0f });

    //load audio
    kiko::g_audioSystem.AddAudio("death", "piphit.wav");
    kiko::g_audioSystem.AddAudio("hit", "laser.wav");
    kiko::g_audioSystem.AddAudio("shotgun", "shotgun.wav");
    kiko::g_audioSystem.AddAudio("music", "spaceSong.wav");
    kiko::g_audioSystem.AddAudio("thrust", "thrust.wav");
    kiko::g_audioSystem.AddAudio("reload", "reload.wav");

    m_scene = std::make_unique<kiko::Scene>();

    kiko::g_audioSystem.PlayOneShot("music", true);

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{

    
    switch (m_state)
    {
    case eState::Title:
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
            m_state = eState::StartGame;
        }

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
        std::unique_ptr<Player> player = std::make_unique<Player>(70.0f, kiko::TwoPi, kiko::Transform{ {400, 300 }, 0, 6 }
        , kiko::g_manager.Get("ship.txt"), kiko::g_manager.Get("bullet.txt"));
        player->m_tag = "player"; 
        player->m_game = this;
        player->SetDamping(0.5f);
        m_scene->Add(move(player));



    }
    m_state = eState::Game;
    break;
    case eState::Game:
        m_spawnTimer += dt;
        if (m_spawnTimer >= m_spawnTime)
        {
            m_random = kiko::randomf(256.0f);

            if (m_random <= 128) {
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(150.0f, 275.0f), kiko::Pi, kiko::Transform{{kiko::random(800), kiko::random(600)}
            , kiko::randomf(kiko::TwoPi), 3}, kiko::g_manager.Get("enemy.txt"));
            enemy->m_tag = "enemy";
            enemy->m_game = this;
            m_scene->Add(std::move(enemy));

            std::unique_ptr<PowerUp> powerup = std::make_unique<PowerUp>(kiko::randomf(300.0f, 500.0f), kiko::Transform{{kiko::random(800), kiko::random(600)}
            , kiko::randomf(kiko::TwoPi), 3}, kiko::g_manager.Get("Star.txt"));
            powerup->m_tag = "star";
            powerup->m_game = this;
            m_scene->Add(std::move(powerup));



            }

            m_spawnTimer = 0.0f;
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(150.0f, 275.0f), kiko::Pi, kiko::Transform{{kiko::random(800), kiko::random(600)}
            , kiko::randomf(kiko::TwoPi), 3}, kiko::g_manager.Get("enemy.txt"));
            enemy->m_tag = "enemy";
            enemy->m_game = this;
            m_scene->Add(std::move(enemy));


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

    m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
    m_livesText->Create(kiko::g_renderer, std::to_string(m_lives), { 1, 0, 0, 1 });

    //m_shootText->Create(kiko::g_renderer, std::to_string(m_miniTimer), { 1, 0, 0, 1 });

    ///m_livesText->Create(kiko::g_renderer, std::to_string(m_lives), { 1, 1, 1, 1 }); health display
    //m_timerText->Create(kiko::g_renderer, std::to_string((int)m_gameTimer), { 1, 1, 1, 1 }); timer...?

    m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
    if (m_state ==  eState::Title)
    {
        m_titleText->Draw(renderer, 600, 450);

    }
    if (m_state == eState::GameOver)
    {
        m_gameoverText->Draw(renderer, 600, 450);
    }
   /* if (m_state == eState::Game) {
        m_timerText->Draw(renderer, 200, 40);
    }*/

   // m_shootText->Draw(renderer, 1150, 40);

    m_scoreText->Draw(renderer, 1100, 20);
    m_livesText->Draw(renderer, 1100, 80);
    m_scene->Draw(renderer);
}


