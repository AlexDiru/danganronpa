#include "GLCharacter.h"
#include "CharacterSprite.h"

#include <iostream>

using namespace KumaGame;

KumaGame::GLCharacter::GLCharacter(KumaCore::Character& character) : character(std::move(character))
{
	for (auto const& sprite : character.getSpriteMap())
	{
		sprites[sprite.first] = std::make_unique<CharacterSprite>(character.getBaseFolder() + sprite.second);
	}
}