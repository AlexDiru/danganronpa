#pragma once

#include <memory>
#include <vector>

namespace KumaCore
{
	class Scene;
}

namespace KumaGame
{
	class GLCharacter;

	class GLScene
	{
	public:
		GLScene(KumaCore::Scene& scene);
		const std::vector<std::shared_ptr<GLCharacter>>& getCharacters() const;

	private:
		const std::unique_ptr<KumaCore::Scene> mScene;
		std::vector<std::shared_ptr<GLCharacter>> mCharacters;
	};
}