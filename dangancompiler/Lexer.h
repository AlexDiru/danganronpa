#pragma once
#include <string>
#include <vector>
#include <cctype>

#include "Token.h"

namespace Dangancompiler
{
	class Lexer
	{
		enum class LexerState
		{
			NONE,
			READING_ALPHABETIC,
			READING_NUMERIC,
		};

		std::string source{ "" };
		size_t currentChar{ 0 };
		std::vector<Token> tokens;
		LexerState lexerState{ LexerState::NONE };
		std::string currentTokenData{ "" };
		unsigned int currentLineNumber{ 2000 };

		inline bool isCurrentCharAlphabetic() const
		{
			return isalpha(source[currentChar]) != 0;
		}

		inline bool isCurrentCharNumeric() const
		{
			return isdigit(source[currentChar]) != 0;
		}

		inline bool isCurrentTokenDataKeyword() const 
		{
			return (currentTokenData == "character");
		}

		void insertToken()
		{
			if (lexerState == LexerState::READING_ALPHABETIC)
			{
				if (isCurrentTokenDataKeyword())
					tokens.push_back(Token(TokenType::KEYWORD, currentTokenData, TokenDataType::STRING, currentLineNumber));
				else
					tokens.push_back(Token(TokenType::IDENTIFIER, currentTokenData, TokenDataType::STRING, currentLineNumber));

				currentTokenData = "";
				lexerState = LexerState::NONE;
			}
			else if (lexerState == LexerState::READING_NUMERIC)
			{
				tokens.push_back(Token(TokenType::LITERAL, currentTokenData, TokenDataType::INT, currentLineNumber));

				currentTokenData = "";
				lexerState = LexerState::NONE;
			}
		}

	public:
		Lexer() = default;

		void tokenise(std::string&& inputSource)
		{
			this->source = std::move(inputSource);
			currentChar = 0;
			lexerState = LexerState::NONE;
			currentTokenData = "";

			for (currentChar; currentChar < source.size(); ++currentChar)
			{
				if (isCurrentCharAlphabetic())
				{
					if (lexerState == LexerState::READING_NUMERIC)
						insertToken();

					lexerState = LexerState::READING_ALPHABETIC;
					currentTokenData += source[currentChar];
				}
				else if (isCurrentCharNumeric())
				{
					//Check current state of lexer
					if (lexerState == LexerState::READING_ALPHABETIC)
						insertToken();

					lexerState = LexerState::READING_NUMERIC;
					currentTokenData += source[currentChar];
				}
			}
			insertToken();
		}

		const std::vector<Token> &getTokens() const
		{
			return tokens;
		}
	};
}