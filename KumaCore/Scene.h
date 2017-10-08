#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Character.h"

namespace KumaCore
{
	class AbstractSceneAction
	{
	public:
		virtual void show() = 0;
	};

	class DialogSceneAction : public AbstractSceneAction 
	{
	public:
		DialogSceneAction(const Character* character, const std::string& text);
		DialogSceneAction(const Character* character, const std::string& text, const std::string& defaultEmotion);

		void show() override;

	private:
		const Character* character;
		std::string text;
		std::string defaultEmotion;
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

		bool hasActionsLeft() const
		{
			return currentAction < sceneActions.size();
		}

		std::string getIdentifierName() const { return name; }

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