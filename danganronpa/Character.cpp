#include "CharacterSprite.h"
#include "Character.h"

#include <iostream>

using namespace Danganronpa;

Character::Character(const std::string &name) : name(name)
{

}

Character::~Character()
{

}

void Character::speak(const std::string& text)
{
	std::cout << name << ": " << text << std::endl;
}
