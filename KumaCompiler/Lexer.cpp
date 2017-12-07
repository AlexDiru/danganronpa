#include "Lexer.h"

void KumaCompiler::Lexer::tokenise(const std::string& inputSource)
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

void KumaCompiler::Lexer::setLexerFlags(LexerFlags& lexerFlags)
{
	mLexerFlags = std::move(lexerFlags);
}

const std::vector<KumaCompiler::Token>& KumaCompiler::Lexer::getTokens() const
{
	return tokens;
}

void KumaCompiler::Lexer::tokenise(std::string&& inputSource)
{
	tokenise(inputSource);
}

bool KumaCompiler::Lexer::isCurrentCharAlphabetic() const
{
	return isalpha(source[currentChar]) != 0;
}

bool KumaCompiler::Lexer::isCurrentCharNumeric() const
{
	return isdigit(source[currentChar]) != 0;
}

bool KumaCompiler::Lexer::isCurrentCharSeparator() const
{
	return separators.find(source[currentChar]) != std::string::npos;
}

bool KumaCompiler::Lexer::isCurrentCharOperator() const
{
	return operators.find(source[currentChar]) != std::string::npos;
}

bool KumaCompiler::Lexer::isCurrentTokenDataKeyword() const
{
	return (currentTokenData == "character" || currentTokenData == "scene");
}

void KumaCompiler::Lexer::insertToken()
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
		if (!mLexerFlags.ignoreWhitespaceTokens || currentTokenData != " ")
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
