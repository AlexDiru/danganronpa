#pragma once

#include <string>
#include <map>

namespace KumaCore
{
	class Character
	{
	public:

		Character(const std::string& identifierName) : identifierName(identifierName) {}

		bool addProperty(const std::string& propertyName, const std::string& propertyValue)
		{
			if (propertyName == "name") { displayName = propertyValue; return true; }
			if (propertyName == "baseFolder") { baseFolder = propertyValue; return true; }
			if (propertyName == "defaultSprite") { defaultSprite = propertyValue; return true; }
			return false;
		}

		bool addPropertySubtype(const std::string& propertyName, const std::string& propertySubtypeName, const std::string& propertyValue)
		{
			if (propertyName == "sprite")
			{
				spriteMap[propertySubtypeName] = propertyValue;
				return true;
			}

			return false;
		}

		std::string getIdentifierName() const { return identifierName; }
		std::string getDisplayName() const { return displayName; }
		const std::map<std::string, std::string>& getSpriteMap() const { return spriteMap; }
		std::string getBaseFolder() const { return baseFolder; }
		std::string getDefaultSpriteFilename() const { return spriteMap.at(defaultSprite); }
	private:
		std::string identifierName;
		std::string displayName{ "UndefinedDisplayName" };
		std::string baseFolder{ "UndefinedBaseFolder" };
		std::string defaultSprite{ "UndefinedDefaultSprite" };
		std::map<std::string, std::string> spriteMap;
	};
}