#include "Image.h"

#include <SDL_image.h>

#include "SDLMaster.h"
#include "Log.h"

using namespace KumaGame;

Image::Image(const std::string& _filename) : filename(_filename)
{
	LOG_ERROR("Image constructor filename: " + filename);
}

bool Image::isLoaded() const
{
	return texture != nullptr;
}

bool Image::load()
{
	SDL_Surface* image = IMG_Load(filename.c_str());

	if (image == nullptr)
	{
		LOG_ERROR("Failed to load image (creation of SDL_Surface): ", filename);
		return false;
	}

	texture = SDL_CreateTextureFromSurface(SDLMaster::get().renderer, image);

	if (texture == nullptr)
	{
		LOG_ERROR("Failed to load image (creation of SDL_Texture): ", filename);
		return false;
	}

	return true;
}

void KumaGame::Image::render() const
{
	SDL_RenderCopy(KumaGame::SDLMaster::get().renderer, texture, nullptr, nullptr);
}

void KumaGame::Image::render(const SDL_Rect& sourceRect, const SDL_Rect& destRect) const
{
	SDL_RenderCopy(KumaGame::SDLMaster::get().renderer, texture, &sourceRect, &destRect);
}