#pragma once

#include "Image.h"

#include <string>

#include <SDL.h>

namespace KumaGame
{
	class CharacterSprite : public Image 
	{
	public:
		CharacterSprite(const std::string& filename);

	};
}