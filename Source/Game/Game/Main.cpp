#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"

#include "Player.h"
#include "Enemy.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Texture.h"


#include "PeggleThree.h"

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

//void print(int i) 
//{
//	cout << i << endl;
//}
//
//int add(int i1, int i2)
//{
//	return i1 + i2;
//}
//
//int sub(int i1, int i2)
//{
//	return i1 - i2;
//}
//
//class A
//{
//public:
//	int add(int i1, int i2)
//	{
//		return i1 + i2;
//	}
//};
//
//union Data
//{
//	int i;
//	bool b;
//	char c[6];
//};

int main(int argc, char* argv[])
{		
	//Data data;
	//data.i = 0;
	//cout << data.i << endl;



	////kiko::Factory::Instance().Register<kiko::Sprite>("Sprite");
	////kiko::Factory::Instance().Register<kiko::CircleCollisionComponent>("CircleCollisionComponent");

	//void (*func_ptr)(int) = &print;
	//func_ptr(3);
	////goes to the address of the function 

	//int (*op_ptr)(int i1, int i2);
	//op_ptr = add;

	//cout << op_ptr(4, 4) << endl;

	//std::function<int(int, int)> op; //template so <>
	//op = add;
	//cout << op(5, 6) << endl; //adds the two values to 11

	//A a;
	//op = std::bind(&A::add, &a, std::placeholders::_1, std::placeholders::_2);
	//cout << op(6, 6) << endl;
	////function pointers point to code NOT data, at run time


	//...
	//rapidjson::Document document;
	//kiko::Json::Load("Scene.json", document);

	//int i1;
	//kiko::Json::Read(document, "integer1", i1);
	//std::cout << i1 << std::endl;
	//int i2;
	//kiko::Json::Read(document, "integer2", i2);
	//std::cout << i2 << std::endl;

	//std::string str;
	//kiko::Json::Read(document, "string", str);
	//std::cout << str << std::endl;
	//bool b;
	//kiko::Json::Read(document, "boolean", b);
	//std::cout << b << std::endl;

	//float f;
	//kiko::Json::Read(document, "float", f);
	//std::cout << f << std::endl;
	//kiko::vec2 v2;
	//kiko::Json::Read(document, "vector2", v2);
	//std::cout << v2 << std::endl;

	//kiko::Renderer renderer;

	INFO_LOG("Initializing Main...");

	kiko::MemoryTracker::Initialize();
	kiko::seed_random((unsigned int)time(nullptr));

	kiko::setFilePath("assets");
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 1200, 900);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	/////CHase Quote - physics init

	unique_ptr<SpaceGame> peggle = make_unique<SpaceGame>();
	peggle->Initialize();

	// create texture

	//kiko::res_t<kiko::Texture> texture = GET_RESOURCE(kiko::Texture, "ship.png", kiko::g_renderer);
	
	//<pass in the renderer and the image filename>

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

		kiko::g_audioSystem.Update();
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());
		
		//In the Game main() call the Update() function of the Particle System to update the particles.

		//update game
		peggle->Update(kiko::g_time.GetDeltaTime());

		//player.Update(kiko::g_time.GetDeltaTime());
		//for (auto& enemy : enemies) enemy.Update(kiko::g_time.GetDeltaTime());

		//kiko::vec2 direction;

		//position += direction * speed * g_time.GetDeltaTime();
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());

		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		//draw
		//kiko::Vector2 vel(1.0f, 0.3f);

		//kiko::g_renderer.DrawTexture(texture.get(), 50.0f, 50.0f, 0.0f);

		peggle->Draw(kiko::g_renderer);
		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}

	return 0;
}
