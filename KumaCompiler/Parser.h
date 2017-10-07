#pragma once

#include <vector>
#include "Token.h"
#include "Log.h"
#include <memory>

namespace KumaCore
{
	class Scene;
}

namespace KumaCompiler
{
	class Parser
	{
	public:
		std::unique_ptr<KumaCore::Scene> parseScene(const std::vector<Token>& tokens);
	};
}