#include "GLCharacter.h"

#include "Character.h"
#include "FileIO.h"

#include <iostream>
#include <map>
#include <string>

using namespace KumaGame;

KumaGame::GLCharacter::GLCharacter(const KumaCore::Character& character) : character(character)
{
	for (auto const& sprite : character.getSpriteMap())
	{
		auto const fullFilename = character.getBaseFolder() + "/" + sprite.second;
		sprites.insert(std::make_pair(sprite.first, CharacterSprite(fullFilename)));
	}
}

void KumaGame::GLCharacter::render(const std::string& emotion)
{
	auto const& toRender = emotion == "" ? sprites[character.getDefaultEmotion()] : sprites[emotion];
	toRender.render();
}