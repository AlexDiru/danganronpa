#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <string_view>
#include <iostream>

#include "Log.h"
#include "Token.h"
#include "LexerState.h"
#include "LexerFlags.h"

namespace KumaCompiler
{
	class Lexer
	{
	public:
		Lexer() = default;

		void tokenise(const std::string& inputSource);
		void tokenise(std::string&& inputSource);

		void setLexerFlags(LexerFlags& lexerFlags);

		const std::vector<Token>& getTokens() const;

	private:
		static constexpr std::string_view separators{ "(){}; .,", 8 };
		static constexpr std::string_view operators{ "=+-/*", 5 };

		std::string source{ "" };
		size_t currentChar{ 0 };
		std::vector<Token> tokens;
		LexerState lexerState{ LexerState::NONE };
		std::string currentTokenData{ "" };
		unsigned int currentLineNumber{ 2000 };
		LexerFlags mLexerFlags;

		bool isCurrentCharAlphabetic() const;
		bool isCurrentCharNumeric() const;
		bool isCurrentCharSeparator() const;
		bool isCurrentCharOperator() const;

		bool isCurrentTokenDataKeyword() const;

		void insertToken();
	};
}