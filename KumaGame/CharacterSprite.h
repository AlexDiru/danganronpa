#pragma once

#include "Sprite.h"

#include <string>

namespace KumaGame
{
	class CharacterSprite : public Sprite 
	{
	public:
		CharacterSprite(const std::string& filename);

	};
}