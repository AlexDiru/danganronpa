#pragma once

#include <map>

#include <SDL_ttf.h>

#include <string>
#include <limits>

#include "Log.h"
#include "SDLMaster.h"

namespace KumaGame
{
	enum class FontRenderMode
	{
		BLENDED_WRAPPED
	};

	class Font
	{
	public:
		Font(const std::string& filename, int size);
		Font(const std::string& filename, int size, SDL_Color colour);
		Font(const std::string& filename, int size, SDL_Color colour, FontRenderMode fontRenderMode);
		~Font();
		void setColour(const SDL_Color& _colour);
		void setFontRenderMode(FontRenderMode _fontRenderMode);
		void render(const std::string& text, int x, int y, unsigned int wrapLength = std::numeric_limits<unsigned int>::max()) const;
		int getSize() const;
		const TTF_Font* getFont() const { return font; }
	private:
		TTF_Font* font{ nullptr };
		int size{ 0 };
		SDL_Color colour{ 0, 0, 0 };
		FontRenderMode fontRenderMode;
	};
}