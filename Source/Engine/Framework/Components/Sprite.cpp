#include "Sprite.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace kiko
{
	CLASS_DEFINITION(Sprite)

	bool Sprite::Initialize()
	{

		if (!textureName.empty())
		m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		return true;
	}

	void kiko::Sprite::Update(float dt)
	{

	}

	void kiko::Sprite::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(),m_owner->transform); //this brokey, rotation bad, not good >:(n
	}

	void Sprite::Read(const json_t& value)
	{
		READ_DATA(value, textureName);
	}
}