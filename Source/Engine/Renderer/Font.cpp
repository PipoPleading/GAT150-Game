#include "Font.h"
#include "Core/Logger.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>
namespace kiko
{
	Font::Font(const std::string& filename, int fontSize)
	{
		//<call Load(filename, fontSize) to load and create font>
		Load(filename, fontSize);
	}
	Font::~Font()
	{
		//<if m_ttfFont not null, close font(TTF_CloseFont)>
		if (m_ttfFont) {
			TTF_CloseFont(m_ttfFont);
		}
	}

	bool Font::Create(std::string filename, ...)
	{
		va_list args;

		va_start(args, filename);
		int& fontSize = va_arg(args, int);
		va_end(args);

		return Load(filename, fontSize);
	}

	bool Font::Load(const std::string& filename, int fontSize)
	{
		//<call TTF_OpenFont>
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize );
		if (!m_ttfFont)
		{
			WARNING_LOG("Failed to open log:" << filename);
			return false;
		}
		return true;
			//<use filename.c_str() to get the c - style string>
			
			//<assign the return value of TTF_OpenFont to m_ttfFont>
	}

}