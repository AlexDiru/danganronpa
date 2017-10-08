#pragma once

#include <vector>
#include <memory>

#include "Character.h"
#include "Scene.h"

namespace KumaCompiler
{
	//Stores all the parsed items
	class ParserDatabase
	{
	public:
		void addCharacter(std::unique_ptr<KumaCore::Character>& character)
		{
			characters.push_back(std::move(character));
		}

		void addScene(std::unique_ptr<KumaCore::Scene>& scene)
		{
			scenes.push_back(std::move(scene));
		}

		KumaCore::Scene* lookupScene(const std::string& identifierName)
		{
			for (auto const& scene : scenes)
				if (scene->getIdentifierName() == identifierName)
					return scene.get();

			return nullptr;
		}

		KumaCore::Character* lookupCharacter(const std::string& identifierName)
		{
			for (auto const& character : characters)
				if (character->getIdentifierName() == identifierName)
					return character.get();

			return nullptr;
		}


	private:
		std::vector<std::unique_ptr<KumaCore::Character>> characters;
		std::vector<std::unique_ptr<KumaCore::Scene>> scenes;
	};
}