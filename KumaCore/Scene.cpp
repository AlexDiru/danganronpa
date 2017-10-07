#include "Scene.h"

#include <iostream>

using namespace KumaCore;

KumaCore::DialogSceneAction::DialogSceneAction(const std::string& name, const std::string& text) : name(name), text(text)
{

}

void KumaCore::DialogSceneAction::show() const
{
	std::cout << name << ": " << text << std::endl;
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