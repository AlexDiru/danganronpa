#pragma once

#include <SDL.h>

#include <string>

namespace KumaGame
{
	class Image
	{
	public:
		Image(const std::string& filename);
		bool isLoaded() const;
		bool load();
		void render();
		void render(const SDL_Rect& sourceRect, const SDL_Rect& destRect);
	protected:
		SDL_Texture* texture;
		const std::string& filename;
	};
}