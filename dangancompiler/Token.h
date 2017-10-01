#pragma once

#include <string>

namespace Dangancompiler
{
	enum class TokenType
	{
		IDENTIFIER,
		KEYWORD,
		SEPARATOR,
		OPERATOR,
		LITERAL,
		COMMENT
	};

	enum class TokenDataType
	{
		STRING,
		INT,
		FLOAT
	};

	class Token
	{
		TokenType tokenType;
		TokenDataType tokenDataType;
		std::string data;
		unsigned int line;

	public:
		Token(TokenType tokenType, const std::string& data, TokenDataType tokenDataType, unsigned int line) :
			tokenType(tokenType), data(data), tokenDataType(tokenDataType), line(line) {}

		std::string toString() const
		{
			std::string out = "";
			if (tokenType == TokenType::COMMENT)
				out += "Comment";
			else if (tokenType == TokenType::IDENTIFIER)
				out += "Identifier";
			else if (tokenType == TokenType::KEYWORD)
				out += "Keyword";
			else if (tokenType == TokenType::LITERAL)
				out += "Literal";
			else if (tokenType == TokenType::OPERATOR)
				out += "Operator";
			else if (tokenType == TokenType::SEPARATOR)
				out += "Separator";
			else
				out += "<UNKNOWN_TOKEN_TYPE>";

			out += ": " + data;

			if (tokenType == TokenType::LITERAL)
			{
				out += " (";
				if (tokenDataType == TokenDataType::FLOAT)
					out += "float";
				else if (tokenDataType == TokenDataType::INT)
					out += "int";
				else if (tokenDataType == TokenDataType::STRING)
					out += "string";
				else
					out += "<UNKNOWN_TOKEN_DATA_TYPE>";
				out += ")";
			}

			return out;
		}
	};
}