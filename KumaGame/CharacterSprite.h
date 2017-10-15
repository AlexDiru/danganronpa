#pragma once

#include "Image.h"

#include <string>

#include <SDL.h>

namespace KumaGame
{
	class CharacterSprite : public Image 
	{
	public:
		CharacterSprite(); //Default constructor for map to work
		CharacterSprite(const std::string& _filename);

	};
}