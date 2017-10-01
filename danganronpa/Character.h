#pragma once

#include <string>
#include <memory>
#include <map>

namespace Danganronpa
{
	class CharacterSprite;

	class Character
	{
		std::string name;
		std::string baseFolder;

		std::map<std::string, std::unique_ptr<CharacterSprite>> sprites;
		
	public:
		Character(const std::string& name);
		~Character();
		void speak(const std::string& text);
	};
}