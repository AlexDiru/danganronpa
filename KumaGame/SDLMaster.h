#pragma once

#include <SDL.h>

namespace KumaGame
{
	struct SDLMaster
	{
		static SDLMaster& get();
		
		SDL_Renderer* renderer{ nullptr };
	};
}