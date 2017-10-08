#pragma once

#include <string>
#include <memory>
#include <map>

#include "Character.h"

namespace KumaGame
{
	class CharacterSprite;

	class GLCharacter
	{
		std::map<std::string, std::unique_ptr<CharacterSprite>> sprites;
		KumaCore::Character character;
	public:
		GLCharacter(KumaCore::Character& character);
		~GLCharacter() {}
	};
}