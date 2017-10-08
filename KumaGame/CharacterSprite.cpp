#include "CharacterSprite.h"

#include <string>
#include <iostream>

KumaGame::CharacterSprite::CharacterSprite(const std::string& filename)
{
	std::cout << "Loading character sprite from " << filename << std::endl;
}
