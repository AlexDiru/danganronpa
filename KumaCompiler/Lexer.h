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
		static constexpr std::string_view separators{ "(){}; ", 6 };
		static constexpr std::string_view operators{ "=+-/*", 5 };

		std::string source{ "" };
		size_t currentChar{ 0 };
		std::vector<Token> tokens;
		LexerState lexerState{ LexerState::NONE };
		std::string currentTokenData{ "" };
		unsigned int currentLineNumber{ 2000 };
		LexerFlags lexerFlags;

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

		inline bool isCurrentCharOperator() const
		{
			return operators.find(source[currentChar]) != std::string::npos;
		}

		inline bool isCurrentTokenDataKeyword() const 
		{
			return (currentTokenData == "character" || currentTokenData == "scene");
		}

		void insertToken()
		{
			if (currentTokenData.size() <= 0)
				return;

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
				if (!lexerFlags.ignoreWhitespaceTokens || currentTokenData != " ")
					tokens.push_back(Token(TokenType::SEPARATOR, currentTokenData, TokenDataType::STRING, currentLineNumber));
			}
			else if (lexerState == LexerState::READING_OPERATOR)
			{
				tokens.push_back(Token(TokenType::OPERATOR, currentTokenData, TokenDataType::STRING, currentLineNumber));
			}
			else if (lexerState == LexerState::READING_STRING_LITERAL)
			{
				tokens.push_back(Token(TokenType::LITERAL, currentTokenData, TokenDataType::STRING, currentLineNumber));
			}
			else
			{
				std::string errorMessage = "";
				errorMessage += "***\n";
				errorMessage += "LEXER ERROR\n";
				errorMessage += "UNKOWN LEXER STATE WHEN INSERTING TOKEN\n";
				errorMessage += "TOKEN DATA: " + currentTokenData + "\n";
				errorMessage += "LINE: " + std::to_string(currentLineNumber) + "\n";
				errorMessage += "***";
				KumaCore::Log::getLog().error(errorMessage);
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

		void setLexerFlags(LexerFlags &_lexerFlags)
		{
			lexerFlags = std::move(_lexerFlags);
		}

		void tokenise(const std::string& inputSource)
		{
			source = inputSource;
			currentChar = 0;
			lexerState = LexerState::NONE;
			currentTokenData = "";
			currentLineNumber = 1;

			for (currentChar; currentChar < source.size(); ++currentChar)
			{
				if (lexerState == LexerState::READING_STRING_LITERAL)
				{
					if (source[currentChar] == '\"')
					{
						// If within string quote
						if (source[currentChar - 1] == '\\')
						{
							//Remove the previously added backslash
							currentTokenData.pop_back();
							currentTokenData += source[currentChar];
						}
						else
						{
							// End of string quote
							insertToken();
						}
					}
					else
					{
						currentTokenData += source[currentChar];
					}
				}
				else if (isCurrentCharAlphabetic())
				{
					if (lexerState != LexerState::READING_ALPHABETIC)
						insertToken();

					lexerState = LexerState::READING_ALPHABETIC;
					currentTokenData += source[currentChar];
				}
				else if (isCurrentCharNumeric())
				{
					//Check current state of lexer
					if (lexerState != LexerState::READING_NUMERIC)
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
				else if (isCurrentCharOperator())
				{
					insertToken();
					currentTokenData = source[currentChar];
					lexerState = LexerState::READING_OPERATOR;
					insertToken();
				}
				else if (source[currentChar] == '\"')
				{
					// Start reading string
					insertToken();
					lexerState = LexerState::READING_STRING_LITERAL;
				}
				else
				{
					if (lexerState != LexerState::READING_STRING_LITERAL)
					{
						if (source[currentChar] == ' ')
						{
							insertToken();
						}
						else if (source[currentChar] == '\n')
						{
							currentLineNumber++;
						}
					}
					else
					{
						//Read stuff normally in a string literal
					}
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