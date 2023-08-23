#pragma once
#include "Framework/Singleton.h"
#include "box2d/include/box2d/b2_world.h"
#include <memory>
namespace kiko
{
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:
		bool Initialize();
		void Update(float dt);
		//<make singleton a friend class to access private constructor>
		friend class Singleton;
	private:
		///<declare default constructor>
			
	private:
		std::unique_ptr<b2World> m_world;
		//<unique pointer of b2World> m_world;
	};
}