#include "GLScene.h"
#include "Scene.h"
#include "GLCharacter.h"

KumaGame::GLScene::GLScene(KumaCore::Scene& scene) : mScene(std::make_unique<KumaCore::Scene>(std::move(scene)))
{
	for (const auto& character : mScene->getCharactersInvolvedInScene())
		mCharacters.push_back(std::make_shared<KumaGame::GLCharacter>(*character));
}

const std::vector<std::shared_ptr<KumaGame::GLCharacter>>& KumaGame::GLScene::getCharacters() const
{
	return mCharacters;
}

