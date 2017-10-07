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
		TokenType getTokenType() const { return tokenType; }
		TokenDataType getTokenDataType() const { return tokenDataType; }
		const std::string& getData() const { return data; }
		int getLine() const { return line;}
		bool isKeyword(const std::string& keywordName) const { return tokenType == TokenType::KEYWORD && data == keywordName; }
		bool isSeparator(const std::string& separatorName) const { return tokenType == TokenType::SEPARATOR && data == separatorName; }
	};
}