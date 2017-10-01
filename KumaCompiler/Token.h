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
	};
}