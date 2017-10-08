#include "Scene.h"

#include <iostream>

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