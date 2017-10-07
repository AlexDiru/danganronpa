#pragma once

#include <string>

#include "TokenType.h"
#include "TokenDataType.h"

namespace KumaCompiler
{
	class Token
	{
		TokenType tokenType;
		TokenDataType tokenDataType;
		std::string data;
		unsigned int line;

	public:
		Token(TokenType tokenType, const std::string& data, TokenDataType tokenDataType, unsigned int line);

		std::string toString() const;
		std::string tokenTypeToString() const;
		TokenType getTokenType() const { return tokenType; }
		TokenDataType getTokenDataType() const { return tokenDataType; }
		const std::string& getData() const { return data; }
		int getLine() const { return line;}
		bool isKeyword(const std::string& keywordName) const { return tokenType == TokenType::KEYWORD && data == keywordName; }
		bool isSeparator(const std::string& separatorName) const { return tokenType == TokenType::SEPARATOR && data == separatorName; }
		bool isIdentifier() const { return tokenType == TokenType::IDENTIFIER; }
		bool isOperator(const std::string& operatorName) const { return tokenType == TokenType::OPERATOR && data == operatorName; }
		bool isStringLiteral() const { return tokenType == TokenType::LITERAL && tokenDataType == TokenDataType::STRING; }
	};
}