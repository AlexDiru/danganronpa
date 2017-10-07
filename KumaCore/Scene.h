#pragma once

#include <vector>
#include <string>
#include <memory>

namespace KumaCore
{
	class AbstractSceneAction
	{
	public:
		virtual void show() const = 0;
	};

	class DialogSceneAction : public AbstractSceneAction 
	{
	public:
		DialogSceneAction(const std::string& name, const std::string& text);

		void show() const override;

	private:
		std::string name;
		std::string text;
	};

	class Scene
	{
		using SceneAction = std::unique_ptr<AbstractSceneAction>;
	public:
		Scene(const std::string& name);

		void addAction(const DialogSceneAction& sceneAction)
		{
			addAction(std::make_unique<DialogSceneAction>(sceneAction));
		}

		void show();

	private:
		std::string name;
		std::vector<SceneAction> sceneActions;
		size_t currentAction{ 0 };

		//Note: sceneAction is moved
		void addAction(SceneAction sceneAction)
		{
			sceneActions.push_back(std::move(sceneAction));
		}
	};
}