#include "SDLMaster.h"

KumaGame::SDLMaster& KumaGame::SDLMaster::get()
{
	static SDLMaster s;
	return s;
}