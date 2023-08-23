#pragma once
#include "RenderComponents.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace kiko
{
	class Sprite : public RenderComponent
	{
	public:
		CLASS_DECLARATION(Sprite)

		bool Initialize() override;

		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_texture->GetSize().length() * 0.5f; }



	public:
		std::string textureName;
		res_t<Texture> m_texture;
	};

}