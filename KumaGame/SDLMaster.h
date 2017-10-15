#pragma once

#include <SDL.h>

namespace KumaGame
{
	struct SDLMaster
	{
		static SDLMaster& get();
		
		SDL_Renderer* renderer{ nullptr };
		SDL_Window *mainWindow{ nullptr };
		SDL_GLContext mainContext{ nullptr };
		SDL_Surface *screenSurface{ nullptr };

		int mainWindowWidth{ 0 };
		int mainWindowHeight{ 0 };
	};
}