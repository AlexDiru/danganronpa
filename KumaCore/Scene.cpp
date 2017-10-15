#include "Scene.h"

#include <iostream>

#include "ContainerUtils.h"

using namespace KumaCore;

KumaCore::DialogSceneAction::DialogSceneAction(const Character* character, const std::string& text) : DialogSceneAction(character, text, "")
{
	
}

KumaCore::DialogSceneAction::DialogSceneAction(const Character* character, const std::string& text, const std::string& defaultEmotion) : character(character), text(text), defaultEmotion(defaultEmotion)
{

}

void KumaCore::DialogSceneAction::show()
{
	if (defaultEmotion == "")
		std::cout << character->getDisplayName() << ": " << text << " [emotion_img: " << character->getDefaultSpriteFilename() << "]" << std::endl;
	else
		std::cout << character->getDisplayName() << ": " << text << " [emotion_img: " << character->getSpriteMap().at(defaultEmotion) << "]" << std::endl;

}

const KumaCore::Character* KumaCore::DialogSceneAction::getCharacter() const
{
	return character;
}

void Scene::show()
{
	if (currentAction == 0)
		std::cout << "Scene: " << name << std::endl;

	if (currentAction < sceneActions.size())
	{
		sceneActions[currentAction]->show();
		currentAction++;
	}
}

KumaCore::Scene::Scene(const std::string& name) : name(name), currentAction(0)
{
}

void KumaCore::Scene::addAction(SceneAction sceneAction)
{
	if (DialogSceneAction *dialogSceneAction = dynamic_cast<DialogSceneAction*>(sceneAction.get()); dialogSceneAction != nullptr)
		push_back_unique(charactersInvolvedInScene, dialogSceneAction->getCharacter());

	sceneActions.push_back(std::move(sceneAction));
}

bool KumaCore::Scene::hasActionsLeft() const
{
	return currentAction < sceneActions.size();
}

const std::vector<const Character*>& KumaCore::Scene::getCharactersInvolvedInScene() const
{
	return charactersInvolvedInScene;
}

void KumaCore::Scene::addAction(const DialogSceneAction& sceneAction)
{
	addAction(std::make_unique<DialogSceneAction>(sceneAction));
}
