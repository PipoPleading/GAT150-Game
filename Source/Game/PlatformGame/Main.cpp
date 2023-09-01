#include "PlatformGame.h"

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"

#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Texture.h"

#include <iostream>
#include <vector>
#include <thread>
//#include <memory>
#include <thread>
#include <array>
#include <map>
#include <functional>

using namespace std;

using vec2 = kiko::Vector2;

int main(int argc, char* argv[])
{

	INFO_LOG("Initializing Main...");

	kiko::MemoryTracker::Initialize();
	kiko::seed_random((unsigned int)time(nullptr));

	kiko::setFilePath("assets");

	//Initializes engine
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize();

	// create game
	unique_ptr<PlatformGame> peggle = make_unique<PlatformGame>();
	peggle->Initialize();

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

		//misc updates
		kiko::g_audioSystem.Update();
		
		peggle->Update(kiko::g_time.GetDeltaTime());
		
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());

		//draw

		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		peggle->Draw(kiko::g_renderer);

		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}

	return 0;
}
