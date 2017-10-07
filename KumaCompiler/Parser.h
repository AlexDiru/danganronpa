#pragma once

#include <vector>
#include "Token.h"
#include "Log.h"
#include "Character.h"
#include "ParserDatabase.h"
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
		Parser(const std::vector<Token>& tokens) : tokens(std::move(tokens)) {}

		bool areNextTokensTheStartOfAScene() const;
		bool areNextTokensTheStartOfACharacter() const;

		std::unique_ptr<KumaCore::Scene> parseScene();
		bool parseCharacter();
	private:
		KumaCompiler::ParserDatabase parserDatabase;
		inline const Token& currentToken() const { return tokens[currentTokenIndex]; }
		const std::vector<Token>& tokens;
		size_t currentTokenIndex{ 0 };
		inline void errorExpected(const std::string& expected)
		{
			KumaCore::Log::getLog().error("Expected ", expected, " after ", currentToken().tokenTypeToString(), " on line ", currentToken().getLine());
		}
	};
}