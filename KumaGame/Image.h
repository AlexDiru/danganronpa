#pragma once

#include <SDL.h>

#include <string>

namespace KumaGame
{
	class Image
	{
	public:
		Image(const std::string& _filename);
		bool isLoaded() const;
		bool load();
		void render() const;
		void render(const SDL_Rect& sourceRect, const SDL_Rect& destRect) const;
	protected:
		SDL_Texture* texture;
		const std::string filename;
	};
}