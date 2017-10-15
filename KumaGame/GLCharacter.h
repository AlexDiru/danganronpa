#pragma once

#include <string>
#include <memory>
#include <map>

#include "CharacterSprite.h"

namespace KumaCore
{
	class Character;
}

namespace KumaGame
{
	class GLCharacter
	{
	public:
		GLCharacter(const KumaCore::Character& character);
		~GLCharacter() {}
		void render(const std::string& emotion);
	private:
		std::map<std::string, CharacterSprite> sprites;
		const KumaCore::Character& character;
	};
}