#pragma once
#include "Framework/Components/Components.h"
namespace kiko
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;

		virtual float GetRadius() { return 0; }
	};
}