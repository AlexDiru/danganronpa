#pragma once

#include <string>

namespace KumaCore
{
	class Character
	{
	public:

		Character(const std::string& identifierName) : identifierName(identifierName) {}

		bool addProperty(const std::string& propertyName, const std::string& propertyValue)
		{
			if (propertyName == "name") { displayName = propertyValue; return true; }

			return false;
		}

		std::string getIdentifierName() const { return identifierName; }
		std::string getDisplayName() const { return displayName; }
	private:
		std::string identifierName;
		std::string displayName{ "UndefinedDisplayName" };

	};
}