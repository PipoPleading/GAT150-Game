#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModeManager.h"
#include "Audio/AudioSystem.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"

#include "PeggleThree.h"

#include "Input/InputSystem.h"
#include <iostream>
#include <vector>
#include <thread>
#include <memory>


using namespace std;

using namespace kiko;//vec2 = kiko::Vector2;

class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::Vector2 m_pos;
	kiko::Vector2 m_vel;

};


int main(int argc, char* argv[])
{
	kiko::MemoryTracker::Initialize();
	kiko::seed_random((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	//kiko::Renderer renderer;
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 1200, 900);

	kiko::g_inputSystem.Initialize();
	g_audioSystem.Initialize();

	unique_ptr<SpaceGame> peggle = make_unique<SpaceGame>();
	peggle->Initialize();

	kiko::vec2 v{5, 5};
	v.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kiko::Vector2 pos(Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(randomf(100, 1000), 0.0f);

		stars.push_back(Star(pos, vel));
	}
	//Color randos
	int r = kiko::random(256);
	int g = kiko::random(256);
	int b = kiko::random(256);

	//main game loop
	bool quit = false;
	while (!quit) 
	{
		// update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		g_audioSystem.Update();
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		//In the Game main() call the Update() function of the Particle System to update the particles.

		//update game
		peggle->Update(kiko::g_time.GetDeltaTime());

		//player.Update(kiko::g_time.GetDeltaTime());
		//for (auto& enemy : enemies) enemy.Update(kiko::g_time.GetDeltaTime());

		kiko::vec2 direction;

		//if (kiko::g_inputSystem.GetMouseButtonDown(0) || kiko::g_inputSystem.GetMouseButtonDown(1) || kiko::g_inputSystem.GetMouseButtonDown(2))
		//{
		//	cout << "mouse pressed" << endl;
		//	cout << "mouse located at: " << kiko::g_inputSystem.GetMousePosition().x << "," << kiko::g_inputSystem.GetMousePosition().y << endl;
		//	//For testing purposes, create an Emitter where the mouse position is when the mouse is pressed.
		//}

		//position += direction * speed * g_time.GetDeltaTime();
		kiko::g_particleSystem.Update(g_time.GetDeltaTime());

		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		//draw
		kiko::Vector2 vel(1.0f, 0.3f);

		for (auto& star : stars) {
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());

			kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);

			star.Draw(kiko::g_renderer);
		}
		kiko::g_particleSystem.Draw(kiko::g_renderer);
		peggle->Draw(kiko::g_renderer);


		
		kiko::g_renderer.EndFrame();
	}

	return 0;
}
