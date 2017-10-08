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

		ParserDatabase& getDatabase() { return parserDatabase;  }

		void parse() 
		{
			while (tokensLeftToParse())
			{
				if (areNextTokensTheStartOfACharacter())
					parseCharacter();
				else if (areNextTokensTheStartOfAScene())
					parseScene();
			}
		}
	private:
		KumaCompiler::ParserDatabase parserDatabase;
		inline const Token& currentToken() const { return tokens[currentTokenIndex]; }
		const std::vector<Token>& tokens;
		size_t currentTokenIndex{ 0 };

		inline void errorExpected(const std::string& expected);

		bool areNextTokensTheStartOfAScene() const;
		bool areNextTokensTheStartOfACharacter() const;
		bool tokensLeftToParse() const { return currentTokenIndex < tokens.size(); }

		bool parseScene();
		bool parseCharacter();
	};
}