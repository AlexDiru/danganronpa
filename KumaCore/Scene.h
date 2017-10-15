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
		const Character* getCharacter() const;
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

		void addAction(const DialogSceneAction& sceneAction);

		void show();

		bool hasActionsLeft() const;

		std::string getIdentifierName() const { return name; }
		const std::vector<const Character*>& getCharactersInvolvedInScene() const;

	private:
		std::string name;
		std::vector<SceneAction> sceneActions;
		std::vector<const Character*> charactersInvolvedInScene;
		size_t currentAction{ 0 };

		//Note: sceneAction is moved
		void addAction(SceneAction sceneAction);
	};
}