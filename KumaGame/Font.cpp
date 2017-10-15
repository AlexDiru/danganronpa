#include "Font.h"

KumaGame::Font::Font(const std::string &filename, int size) : size(size)
{
	font = TTF_OpenFont(filename.c_str(), size);
	if (font == nullptr)
	{
		LOG_ERROR("Failed to load font: ", filename, " | Size = ", size);
		return;
	}
}

KumaGame::Font::~Font()
{
	TTF_CloseFont(font);
	font = nullptr;
}

KumaGame::Font::Font(const std::string& filename, int size, SDL_Color colour) : Font(filename, size)
{
	this->colour = colour;
}

KumaGame::Font::Font(const std::string& filename, int size, SDL_Color colour, FontRenderMode fontRenderMode) : Font(filename, size, colour)
{
	this->fontRenderMode = fontRenderMode;
}

void KumaGame::Font::setColour(const SDL_Color& _colour)
{
	colour = _colour;
}

void KumaGame::Font::setFontRenderMode(FontRenderMode _fontRenderMode)
{
	fontRenderMode = _fontRenderMode;
}

void KumaGame::Font::render(const std::string& text, int x, int y, unsigned int wrapLength) const
{
	if (wrapLength == std::numeric_limits<unsigned int>::max())
		wrapLength = SDLMaster::get().screenSurface->w;

	auto const surfaceMessage = [this, &text, wrapLength]() {
		switch (fontRenderMode)
		{
		case FontRenderMode::BLENDED_WRAPPED:
			return TTF_RenderText_Blended_Wrapped(font, text.c_str(), colour, wrapLength);
		default:
			nullptr;
		}
	}();

	auto const texture = SDL_CreateTextureFromSurface(SDLMaster::get().renderer, surfaceMessage);
	SDL_Rect destRect{ x, y, surfaceMessage->w, surfaceMessage->h };
	SDL_RenderCopy(SDLMaster::get().renderer, texture, nullptr, &destRect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(texture);
}

int KumaGame::Font::getSize() const
{
	return size;
}
