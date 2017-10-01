#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <string_view>

#include "Token.h"
#include "LexerState.h"

namespace KumaCompiler
{
	class Lexer
	{
		static constexpr std::string_view separators{ "(){};", 5 };

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

		inline bool isCurrentCharSeparator() const
		{
			return separators.find(source[currentChar]) != std::string::npos;
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
			}
			else if (lexerState == LexerState::READING_NUMERIC)
			{
				tokens.push_back(Token(TokenType::LITERAL, currentTokenData, TokenDataType::INT, currentLineNumber));
			}
			else if (lexerState == LexerState::READING_SEPARATOR)
			{
				tokens.push_back(Token(TokenType::SEPARATOR, currentTokenData, TokenDataType::STRING, currentLineNumber));
			}

			currentTokenData = "";
			lexerState = LexerState::NONE;
		}

	public:
		Lexer() = default;


		void tokenise(std::string&& inputSource)
		{
			tokenise(inputSource);
		}

		void tokenise(std::string& inputSource)
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
				else if (isCurrentCharSeparator())
				{
					insertToken();
					currentTokenData = source[currentChar];
					lexerState = LexerState::READING_SEPARATOR;
					insertToken();
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