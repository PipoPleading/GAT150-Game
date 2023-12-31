#pragma once

#include "Font.h"
#include "Model.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Text.h"
#include "Texture.h"

#include <SDL2-2.28.0/include/SDL.h>
#include <string>

namespace kiko
{
	//void CreateWindow(const std::string& title, int width, int height);
	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		bool Initialize();
		void Shutdown();

		void CreateWindow(const std::string& title, int width, int height);
		void BeginFrame();
		void EndFrame();

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a); //data type limited to 256, good for colors and whatnot
		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(float x1, float y1, float x2, float y2);//
		void DrawPoint(int x, int y);
		void DrawPoint(float x, float y);//

		void DrawTexture(class Texture* texture, float x, float y, float angle = 0.0f);
		void DrawTexture(class Texture* texture, const kiko::Transform& transform);
		void DrawTexture(class Texture* texture, const Rect& source, const kiko::Transform& transform);
		void DrawTexture(class Texture* texture, const Rect& source, const kiko::Transform& transform, const vec2& origin, bool flipH);

		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }

		friend class Text;
		friend class Texture;

	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;
	};

	extern Renderer g_renderer;
}