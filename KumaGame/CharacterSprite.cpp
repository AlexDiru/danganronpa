#include "CharacterSprite.h"

#include "FileIO.h"
#include "Log.h"

#include <string>
#include <iostream>

KumaGame::CharacterSprite::CharacterSprite(const std::string& _filename) : Image(KumaCore::FileIO::getContent(_filename))
{
	LOG_ERROR("Character constructor filename: " + filename);
	load();
}

KumaGame::CharacterSprite::CharacterSprite() : CharacterSprite("")
{

}
