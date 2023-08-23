#pragma once
#include "Font.h"
#include "Core/Color.h"
#include <string>
#include <memory>

struct SDL_Texture;

namespace kiko
{	
	class Renderer;

	class Text
	{
	public:
		//<create a default constructor>
		Text() = default;
		Text(std::shared_ptr<Font> font) : m_font{ font } { }
		~Text();
		
			//Text(<a shared pointer of Font type> font) : m_font{ font } { }
		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, int x, int y);
		void Draw(Renderer& renderer, const class Transform& transform);

		friend class Font;
		friend class Renderer;

	private:
		std::shared_ptr<Font> m_font;
		SDL_Texture* m_texture = nullptr;
	};
}

//Make the Text class a friend of the Font class.This will give the Text class access to the private m_ttfFont
//member.
//Make the Text class a friend of the Renderer class.This will give the Text class access to the private
//m_renderer member

